#include "tim.h"
TIM_HandleTypeDef htim2;

void MX_TIM2_Init()
{
  //The initialize structure
  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  //
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;

  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  //start TIM2 with polling mode (To be used in FreeOS)
  //HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  //using interrupt mode of encoder
  HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
  
}

//Init the low level hardware
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  //TIM2 clock enable
  __HAL_RCC_TIM2_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();
  /**TIM2 GPIO Configuration
  PA0-WKUP     ------> TIM2_CH1
  PA1     ------> TIM2_CH2
  */

  GPIO_InitStruct.Pin = ENCODER_PHASE_A_PIN|ENCODER_PHASE_B_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(ENCODER_PHASE_A_PORT,&GPIO_InitStruct);


  HAL_NVIC_SetPriority(TIM2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

