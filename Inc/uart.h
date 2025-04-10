#include "stm32f4xx_hal.h"
//#include "stm32f407xx.h"
extern UART_HandleTypeDef huart1;
#define UART1_TX_PIN GPIO_PIN_9
#define UART1_TX_PORT GPIOA

#define UART1_RX_PIN GPIO_PIN_10
#define UART1_RX_PORT GPIOA
void MX_USART1_Init();
void Uart_Send(char *string);
void BufferInit(uint8_t* pBuffer1, uint8_t* pBuffer2, char *string ,uint16_t BufferLength);
void BufferCopy(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
int32_t BufferParse(uint8_t* posBuffer);
uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint32_t usrPow(uint8_t base, uint8_t exponent);
