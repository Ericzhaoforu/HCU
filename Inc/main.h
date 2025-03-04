/**
  ******************************************************************************
  * @file    Multi/Examples/MotionControl/IHM03A1_ExampleFor1Motor/Inc/main.h 
  * @author  IPC Rennes
  * @version V1.6.0
  * @date    June 4th, 2018
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
//Select which motor driver to use
 //#define USE_POWERSTEP
#define USE_L6470
//#define MOTOR_BSP
#if ((defined (USE_L6470)) && (defined (USE_POWERSTEP)))
  #error "please select only one motor driver!"
#elif ((!defined (USE_L6470)) && (!defined (USE_POWERSTEP)))
  #error "please select a motor driver to use"
#endif


/* Includes ------------------------------------------------------------------*/
#ifdef USE_POWERSTEP
#include "x_nucleo_ihmxx.h"
#include "powerstep01.h"
#endif
#ifdef USE_L6470
#include "xnucleoihm02a1.h"
#include "xnucleoihm02a1_interface.h"
#endif
// #include "stm32f4xx_hal.h"
// #include "stm32f407xx.h"

#ifdef MOTOR_BSP
#include "x_nucleo_ihm03a1_stm32f4xx.h"
#endif
#ifdef USE_STM32F3XX_NUCLEO
#include "x_nucleo_ihm03a1_stm32f3xx.h"
#endif
#ifdef USE_STM32F0XX_NUCLEO
#include "x_nucleo_ihm03a1_stm32f0xx.h"
#endif
#ifdef USE_STM32L0XX_NUCLEO
#include "x_nucleo_ihm03a1_stm32l0xx.h"
#endif
void Error_Handler();
#include "uart.h"
#include "tim.h"
#include "i2c.h"

#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SystemClock_Config(void);

void MyErrorHandler(uint16_t error);

void Roplus_Pin_Init();
void showscreen(void);
uint32_t  Get_Desired_Postion_By_Cmd(uint8_t desireVal);

void Update_Home_Status();
void Update_Motor_Pos();
#ifdef USE_POWERSTEP
extern union powerstep01_Init_u initDeviceParameters;
void Motor_Find_Home(uint8_t deviceId,motorDir_t dir, uint32_t speed);
void Motor_Find_Upper_Position(uint8_t deviceId,motorDir_t dir, uint32_t speed);
void Motor_Cmd_Handler(uint8_t deviceId, uint8_t desireVal);
#endif

#ifdef USE_L6470
MotorParameterData_t *GetMotorParameterInitData(void);
void Motor_Find_Home(uint8_t deviceId,eL6470_DirId_t dir, uint32_t speed);
void Motor_Find_Upper_Position(uint8_t deviceId,eL6470_DirId_t dir, uint32_t speed);
#endif
void Update_Gear_Status(uint8_t GearVal);
void Pull_And_Run_Motor();
uint8_t PinState_To_Int(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void BufferInit(uint8_t* pBuffer1, uint8_t* pBuffer2, char *string ,uint16_t BufferLength);
void BufferCopy(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint32_t BufferParse(uint8_t* posBuffer);
#endif /* __MAIN_H */
void suction_test();
#define SENSOR_EXTI_PIN GPIO_PIN_0//DIN 05
#define SENSOR_EXTI_PIN_UPPER GPIO_PIN_3//DIN 06
#define SENSOR_EXTI_PORT GPIOA
#define UR_INPUT_PORT GPIOE
#define UR_INPUT_PIN1 GPIO_PIN_4//DIN 02
#define UR_INPUT_PIN2 GPIO_PIN_5//DIN 03
#define UR_INPUT_PIN3 GPIO_PIN_6//DIN 04

#define VALVE_PORT GPIOD

//PA2 cannnot be used, because this pin is used in ModBus
//#define UR_OUTPUT_PIN1 GPIO_PIN_2
#define VALVE_1_PIN GPIO_PIN_7//DOUT 08
#define VALVE_2_PIN GPIO_PIN_11//DOUT 02
#define VALVE_3_PIN GPIO_PIN_14//DOUT 03
#define VALVE_4_PIN GPIO_PIN_15//DOUT 04
#define VALVE_NUM 4

#define SENSOR_EXTI_LINE_IRQn EXTI0_IRQn
#define LED_DIAG_PORT GPIOC
#define LED_DIAG2_PIN GPIO_PIN_8
#define LED_DIAG1_PIN GPIO_PIN_9
#define LED_STATUS_PORT GPIOE
#define LED_RUN_PIN GPIO_PIN_0
#define LED_COMM_PIN GPIO_PIN_1
#define SPEED_IN_STEP_S_HIGH 400
#define SPEED_IN_STEP_S_LOW 200
#define RX_BUFFERSIZE 8
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
