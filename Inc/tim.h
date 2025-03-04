#include "stm32f4xx_hal.h"
#define ENCODER_PHASE_A_PIN GPIO_PIN_1
#define ENCODER_PHASE_A_PORT GPIOA
#define ENCODER_PHASE_B_PIN GPIO_PIN_15
#define ENCODER_PHASE_B_PORT GPIOA
extern TIM_HandleTypeDef htim2;

void MX_TIM2_Init();