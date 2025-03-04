#include "uart.h"
#include <string.h>
UART_HandleTypeDef huart1;
/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_Init()
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = USART_WORDLENGTH_8B;
  huart1.Init.StopBits = USART_STOPBITS_1;
  huart1.Init.Parity = USART_PARITY_NONE;
  huart1.Init.Mode = USART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance==USART1)
     {
/* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**UART5 GPIO Configuration
        PC12     ------> UART5_TX
        PD2     ------> UART5_RX
        */
    //PA9:TX PA10:RX
    GPIO_InitStruct.Pin = UART1_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(UART1_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = UART1_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(UART1_RX_PORT, &GPIO_InitStruct);

    /*Interrupt mode enable*/
    /* USER CODE BEGIN UART5_MspInit 1 */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE END UART5_MspInit 1 */
}

}

void Uart_Send(char *string)
{
	uint8_t len = strlen (string);
  HAL_UART_Transmit_IT(&huart1, (uint8_t *) string, len);
	//HAL_UART_Transmit(&huart5, (uint8_t *) string, len, HAL_MAX_DELAY);  // transmit in blocking mode
}