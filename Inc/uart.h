#include "stm32f4xx_hal.h"
//#include "stm32f407xx.h"
extern UART_HandleTypeDef huart1;
#define UART1_TX_PIN GPIO_PIN_9
#define UART1_TX_PORT GPIOA

#define UART1_RX_PIN GPIO_PIN_10
#define UART1_RX_PORT GPIOA
void MX_USART1_Init();
void Uart_Send(char *string);