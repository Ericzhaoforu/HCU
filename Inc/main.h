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
#include "adc.h"
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
void clearscreen(void);
void Update_Home_Status();
void Update_Motor_Pos();
#ifdef USE_POWERSTEP
static void MyBusyInterruptHandler(void);
static void MyFlagInterruptHandler(void);
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

void Update_Gear_Status();

#endif /* __MAIN_H */
#define SENSOR_EXTI_PIN GPIO_PIN_0//DIN 05
#define SENSOR_EXTI_PIN_UPPER GPIO_PIN_3//DIN 06
#define SENSOR_EXTI_PORT GPIOA

#define UR_IO_PORT GPIOE
#define UR_IO_ENABLE_PIN GPIO_PIN_2 //DIN 00
#define UR_IO_PIN1 GPIO_PIN_3//DIN 01
#define UR_IO_PIN2 GPIO_PIN_4//DIN 02

#define UR_IO_PIN3 GPIO_PIN_6//DIN 03
#define UR_IO_PIN4 GPIO_PIN_6//DIN 04
#define UR_IO_SUCTION_PIN GPIO_PIN_7//DIN 07

#define MOTOR_READY_DIGITAL_OUTPUT_PORT GPIOB
#define MOTOR_READY_DIGITAL_OUTPUT_PIN GPIO_PIN_6//DOUT 05

#define VALVE_PORT GPIOD
#define VALVE_PORT_BENDING GPIOE

#define VALVE_SUCTION_PIN GPIO_PIN_15//DOUT 04  PD15 suction
#define VALVE_BENDING_C_PIN GPIO_PIN_14//DOUT 03  PD14 bending C 
#define VALVE_BENDING_O_PIN GPIO_PIN_10//DOUT 01  PE10 bending_O
#define VALVE_JAMMING_PIN GPIO_PIN_11//DOUT 02  PD11 jamming 
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
#define PHY_LINK_STATUS               ((uint16_t)0x0004U)

void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void screenmenu(void);
uint8_t DetectEthernetCable(void);
void Rotate_Motor(int32_t d_Pos);
void Update_gear_buf();
void Update_Suction_Status_Led();
void Update_Eth_Status_Led();
void Show_Err_Led();
int32_t Gear_To_Position(uint8_t gear);
int32_t Pos_Saturate(int32_t pos);

#define POS_LOWER_LIMIT 200000
#define POS_UPPER_LIMIT 2200000
#define GEAR1_POS 200000
#define GEAR2_POS 1100000
#define GEAR3_POS 2200000
//1200: 14s
//1500 slip
#define MOTOR_SPEED 900.0
#define MOTOR_SPEED_MAX 1200.0
#define MOTOR_SPEED_MIN 0.0
#define MOTOR_ACC 8000.0

//home speed, dont care
#define MOTOR_HOME_SPEED 15000
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
