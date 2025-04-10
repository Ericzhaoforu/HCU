/**
  ******************************************************************************
  * @file    params.c
  * @author  IPD SYSTEM LAB & TECH MKTG
  * @version V0.0.1
  * @date    04-June-2015
  * @brief   This file contains the parameters for the used stepper motors.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * @addtogroup   MotionControl
  * @{
  */

/**
  * @addtogroup MicrosteppingMotor_Example
  * @{
  */

/**
  * @addtogroup Attached_Motor_Parameters
  * @{
  */

/**
  * @addtogroup Parameters_Exported_Constants
  * @{
  */
#ifdef USE_L6470
/**
  * @brief  This array contains the initial parameters for the motors that are
  *         linked with each L6470 mounted on each stacked X-NUCLEO-IHM02A1.
  */
const MotorParameterData_t MotorParameterInitData[EXPBRD_MOUNTED_NR_MAX][L6470DAISYCHAINSIZE] = {
  {
    //Vbus,
    // min number of steps per round, 
    // max motor phase current in A, 
    // max motor phase voltage in V,

    // initial speed 
    // ACC
    // DEC
    // MaxSpeed
    // MinSpeed
    // FsSpd 

        {12, 200, 2.3, 1.8, MOTOR_SPEED, MOTOR_ACC, MOTOR_ACC, MOTOR_SPEED_MAX, MOTOR_SPEED_MIN, 602.7, 1.794, 1.794,
    1.794, 1.794, 354.6, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
    // {24, 200, 2.3, 1.8, 240.0, 400.0, 400.0, 900.0, 0.0, 602.7, 1.794, 1.794,\
    // 3, 3, 354.6, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
    //     3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
    {24, 200, 2.3, 1.8, MOTOR_SPEED, MOTOR_ACC, MOTOR_ACC, MOTOR_SPEED_MAX, MOTOR_SPEED_MIN, 602.7, 1.794, 1.794,\
    3, 3, 354.6, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
  },
  {
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
  },
  {
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
  },
  {
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
    {9.0, 400, 1.7, 3.06, 240.0, 400.0, 400.0, 320.0, 0.0, 602.7, 3.06, 3.06,\
      3.06, 3.06, 61.52, 392.1569e-6, 643.1372e-6, 643.1372e-6, 0,\
        3.06*1000*1.10, 3.06*1000*1.00, MICROSTEP_1_128, 0xFF, 0x2E88},
  },
};
  
/**
  * @}
  */    /* Parameters_Exported_Constants */

/**
  * @addtogroup Parameters_Exported_Functions
  * @{
  */

/**
  * @brief  Return the initial motor parameters.
  * @param  index   The index inside the array of parameters to point the right data.
  * @retval MotorParameterData_t*   The pointer to the data structure of parameters.
  */
MotorParameterData_t *GetMotorParameterInitData(void)
{
  return (MotorParameterData_t*)(MotorParameterInitData);
}
#endif

#ifdef USE_POWERSTEP
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Uncomment the define for the desired mode and comment the undesired one    */
#define CURRENT_MODE //to use initialization parameters for current mode
//#define VOLTAGE_MODE //to use initialization parameters for voltage mode


#ifdef CURRENT_MODE
/* Initialization parameters for current mode */
union powerstep01_Init_u initDeviceParameters =
{
  /* common parameters */
  .cm.cp.cmVmSelection = POWERSTEP01_CM_VM_CURRENT, // enum powerstep01_CmVm_t
  20, // Acceleration rate in step/s2, range 14.55 to 59590 steps/s^2
  20, // Deceleration rate in step/s2, range 14.55 to 59590 steps/s^2
  100, // Maximum speed in step/s, range 15.25 to 15610 steps/s
  0, // Minimum speed in step/s, range 0 to 976.3 steps/s
  POWERSTEP01_LSPD_OPT_OFF, // Low speed optimization bit, enum powerstep01_LspdOpt_t
  100, // Full step speed in step/s, range 7.63 to 15625 steps/s
  POWERSTEP01_BOOST_MODE_OFF, // Boost of the amplitude square wave, enum powerstep01_BoostMode_t
  281.25, // Overcurrent threshold settings via enum powerstep01_OcdTh_t
  STEP_MODE_1_16, // Step mode settings via enum motorStepMode_t
  POWERSTEP01_SYNC_SEL_DISABLED, // Synch. Mode settings via enum powerstep01_SyncSel_t
  (POWERSTEP01_ALARM_EN_OVERCURRENT|
   POWERSTEP01_ALARM_EN_THERMAL_SHUTDOWN|
   POWERSTEP01_ALARM_EN_THERMAL_WARNING|
   POWERSTEP01_ALARM_EN_UVLO|
   POWERSTEP01_ALARM_EN_STALL_DETECTION|
   POWERSTEP01_ALARM_EN_SW_TURN_ON|
   POWERSTEP01_ALARM_EN_WRONG_NPERF_CMD), // Alarm settings via bitmap enum powerstep01_AlarmEn_t
  POWERSTEP01_IGATE_64mA, // Gate sink/source current via enum powerstep01_Igate_t 
  POWERSTEP01_TBOOST_0ns, // Duration of the overboost phase during gate turn-off via enum powerstep01_Tboost_t
  POWERSTEP01_TCC_500ns, // Controlled current time via enum powerstep01_Tcc_t
  POWERSTEP01_WD_EN_DISABLE, // External clock watchdog, enum powerstep01_WdEn_t  
  POWERSTEP01_TBLANK_375ns, // Duration of the blanking time via enum powerstep01_TBlank_t
  POWERSTEP01_TDT_125ns, // Duration of the dead time via enum powerstep01_Tdt_t
  /* current mode parameters */
  // 21.45,
  // 21.45,
  // 21.45,
  // 21.45,
  49.5,
  49.5,
  49.5,
  49.5,
  //21.45, // Hold torque in mV, range from 7.8mV to 1000 mV
  //21.45, // Running torque in mV, range from 7.8mV to 1000 mV 
  //21.45, // Acceleration torque in mV, range from 7.8mV to 1000 mV
  //21.45, // Deceleration torque in mV, range from 7.8mV to 1000 mV
  POWERSTEP01_TOFF_FAST_8us, //Maximum fast decay time , enum powerstep01_ToffFast_t 
  POWERSTEP01_FAST_STEP_12us, //Maximum fall step time , enum powerstep01_FastStep_t 
  3.0, // Minimum on-time in us, range 0.5us to 64us
  21.0, // Minimum off-time in us, range 0.5us to 64us 
  POWERSTEP01_CONFIG_INT_16MHZ_OSCOUT_2MHZ, // Clock setting , enum powerstep01_ConfigOscMgmt_t
  POWERSTEP01_CONFIG_SW_HARD_STOP, // External switch hard stop interrupt mode, enum powerstep01_ConfigSwMode_t
  POWERSTEP01_CONFIG_TQ_REG_TVAL_USED, // External torque regulation enabling , enum powerstep01_ConfigEnTqReg_t
  POWERSTEP01_CONFIG_VS_COMP_DISABLE, // Motor Supply Voltage Compensation enabling , enum powerstep01_ConfigEnVscomp_t 
  POWERSTEP01_CONFIG_OC_SD_DISABLE, // Over current shutwdown enabling, enum powerstep01_ConfigOcSd_t
  POWERSTEP01_CONFIG_UVLOVAL_LOW, // UVLO Threshold via powerstep01_ConfigUvLoVal_t
  //POWERSTEP01_CONFIG_VCCVAL_7_5V,
  POWERSTEP01_CONFIG_VCCVAL_15V, // VCC Val, enum powerstep01_ConfigVccVal_t
  POWERSTEP01_CONFIG_TSW_048us, // Switching period, enum powerstep01_ConfigTsw_t
  POWERSTEP01_CONFIG_PRED_ENABLE,
  //POWERSTEP01_CONFIG_PRED_DISABLE, // Predictive current enabling , enum powerstep01_ConfigPredEn_t 
};
#endif //CURRENT_MODE

#ifdef VOLTAGE_MODE
/* Initialization parameters for voltage mode */
union powerstep01_Init_u initDeviceParameters =
{
  /* common parameters */
  .vm.cp.cmVmSelection = POWERSTEP01_CM_VM_VOLTAGE, // enum powerstep01_CmVm_t
  582, // Acceleration rate in step/s2, range 14.55 to 59590 steps/s^2
  582, // Deceleration rate in step/s2, range 14.55 to 59590 steps/s^2
  488, // Maximum speed in step/s, range 15.25 to 15610 steps/s
  0, // Minimum speed in step/s, range 0 to 976.3 steps/s
  POWERSTEP01_LSPD_OPT_OFF, // Low speed optimization bit, enum powerstep01_LspdOpt_t
  244.16, // Full step speed in step/s, range 7.63 to 15625 steps/s
  POWERSTEP01_BOOST_MODE_OFF, // Boost of the amplitude square wave, enum powerstep01_BoostMode_t
  281.25, // Overcurrent threshold settings via enum powerstep01_OcdTh_t
  STEP_MODE_1_16, // Step mode settings via enum motorStepMode_t
  POWERSTEP01_SYNC_SEL_DISABLED, // Synch. Mode settings via enum powerstep01_SyncSel_t
  (POWERSTEP01_ALARM_EN_OVERCURRENT|
   POWERSTEP01_ALARM_EN_THERMAL_SHUTDOWN|
   POWERSTEP01_ALARM_EN_THERMAL_WARNING|
   POWERSTEP01_ALARM_EN_UVLO|
   POWERSTEP01_ALARM_EN_STALL_DETECTION|
   POWERSTEP01_ALARM_EN_SW_TURN_ON|
   POWERSTEP01_ALARM_EN_WRONG_NPERF_CMD), // Alarm settings via bitmap enum powerstep01_AlarmEn_t
  POWERSTEP01_IGATE_64mA, // Gate sink/source current via enum powerstep01_Igate_t 
  POWERSTEP01_TBOOST_0ns, // Duration of the overboost phase during gate turn-off via enum powerstep01_Tboost_t
  POWERSTEP01_TCC_500ns, // Controlled current time via enum powerstep01_Tcc_t
  POWERSTEP01_WD_EN_DISABLE, // External clock watchdog, enum powerstep01_WdEn_t  
  POWERSTEP01_TBLANK_375ns, // Duration of the blanking time via enum powerstep01_TBlank_t
  POWERSTEP01_TDT_125ns, // Duration of the dead time via enum powerstep01_Tdt_t
  /* voltage mode parameters */
  16.02, // Hold duty cycle (torque) in %, range 0 to 99.6%
  16.02, // Run duty cycle (torque) in %, range 0 to 99.6%
  16.02, // Acceleration duty cycle (torque) in %, range 0 to 99.6%
  16.02, // Deceleration duty cycle (torque) in %, range 0 to 99.6%
  61.512, // Intersect speed settings for BEMF compensation in steps/s, range 0 to 3906 steps/s
  0.03815, // BEMF start slope settings for BEMF compensation in % step/s, range 0 to 0.4% s/step
  0.06256, // BEMF final acc slope settings for BEMF compensation in % step/s, range 0 to 0.4% s/step
  0.06256, // BEMF final dec slope settings for BEMF compensation in % step/s, range 0 to 0.4% s/step
  1, // Thermal compensation param, range 1 to 1.46875
  531.25, // Stall threshold settings in mV, range 31.25mV to 1000mV
  POWERSTEP01_CONFIG_INT_16MHZ_OSCOUT_2MHZ, // Clock setting , enum powerstep01_ConfigOscMgmt_t
  POWERSTEP01_CONFIG_SW_HARD_STOP, // External switch hard stop interrupt mode, enum powerstep01_ConfigSwMode_t
  POWERSTEP01_CONFIG_VS_COMP_DISABLE, // Motor Supply Voltage Compensation enabling , enum powerstep01_ConfigEnVscomp_t
  POWERSTEP01_CONFIG_OC_SD_DISABLE, // Over current shutwdown enabling, enum powerstep01_ConfigOcSd_t
  POWERSTEP01_CONFIG_UVLOVAL_LOW, // UVLO Threshold via powerstep01_ConfigUvLoVal_t
  POWERSTEP01_CONFIG_VCCVAL_15V, // VCC Val, enum powerstep01_ConfigVccVal_t
  POWERSTEP01_CONFIG_PWM_DIV_2, // PWM Frequency Integer division, enum powerstep01_ConfigFPwmInt_t
  POWERSTEP01_CONFIG_PWM_MUL_1, // PWM Frequency Integer Multiplier, enum powerstep01_ConfigFPwmDec_t
};
#endif //VOLTAGE_MODE

/**
  * @brief  Return the initial motor parameters.
  * @param  index   The index inside the array of parameters to point the right data.
  * @retval MotorParameterData_t*   The pointer to the data structure of parameters.
  */
// union powerstep01_Init_u *GetMotorParameterInitData(void)
// {
//   return (union powerstep01_Init_u*)(initDeviceParameters);
// }

#endif
/**
  * @}
  */    /* Parameters_Exported_Functions */
  
/**
  * @}
  */ /* End of Attached_Motor_Parameters */

/**
  * @}
  */ /* End of MicrosteppingMotor_Example */

/**
  * @}
  */ /* End of MotionControl */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
