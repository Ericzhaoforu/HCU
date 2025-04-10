#include "stm32f4xx_hal.h"
#define ADC1_PORT GPIOB
#define ADC1_PIN GPIO_PIN_0
#define ADC2_PORT GPIOB
#define ADC2_PIN GPIO_PIN_1
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;