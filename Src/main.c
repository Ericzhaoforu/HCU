/**
  ******************************************************************************
  * @file    main.c 
  * @author  Eric Zhao
  * @version V1.0
  * @brief   This code is about the motor driver POWERSTEP01 & L6470D
  ******************************************************************************
  * @attention
  *
  */

#include "main.h"
#include "lwip.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> // Include the header file for boolean data type
#include <string.h>

static volatile uint16_t gLastError;
bool is_home=FALSE;
int32_t cur_pos;
uint8_t cur_gear_pos;
uint32_t counter = 0;
int16_t count = 0;
int16_t position = 0;
uint32_t usrPow(uint8_t base, uint8_t exponent);
uint8_t Rx_Buffer[RX_BUFFERSIZE];
uint8_t Rx_Buffer_former[RX_BUFFERSIZE];
uint8_t board;
uint8_t gripper_motor;
uint8_t test_motor;
uint16_t GPIO_VALVES[VALVE_NUM] = {VALVE_1_PIN,VALVE_2_PIN,VALVE_3_PIN,VALVE_4_PIN};
//Handler & Parameter container
StepperMotorBoardHandle_t *StepperMotorBoardHandle;
MotorParameterData_t *MotorParameterDataGlobal, *MotorParameterDataSingle;
//STM32 WRITE BUF
uint8_t REG_DISC_BUF[10]={0,0,0,0,0,0,0,0,0,0};
//STM32 READ BUF
uint8_t REG_COILS_BUF[10]={0,0,0,0,0,0,0,0,0,0};
uint8_t REG_COILS_BUF_FORMER[10]={0,0,0,0,0,0,0,0,0,0};
bool cleared = TRUE;

#ifdef USE_POWERSTEP
/* Private function prototypes -----------------------------------------------*/
static void MyBusyInterruptHandler(void);
static void MyFlagInterruptHandler(void);
#endif

int main(void)
{
  /* STM32F4xx HAL library initialization */
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();
  
  /*Initialize pin used for Roplus*/
  Roplus_Pin_Init();
  //led test
  // HAL_GPIO_WritePin(LED_STATUS_PORT,LED_RUN_PIN,GPIO_PIN_SET);
  // HAL_GPIO_WritePin(LED_STATUS_PORT,LED_COMM_PIN,GPIO_PIN_SET);
  // HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG1_PIN,GPIO_PIN_RESET);
  // HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_SET);
  
  /*UART initialization, used for debug*/
  MX_USART1_Init();
  Uart_Send("UART OK!\n");
  HAL_Delay(100);
//  while(1)
//  {
//    HAL_GPIO_TogglePin(LED_STATUS_PORT,LED_RUN_PIN);
//    Uart_Send("UART OK!\n");
//    HAL_Delay(1000);
//  }
  MX_LWIP_Init();
  ModbusTCPInit();
  Uart_Send("Modbus OK!\n");
  HAL_Delay(100);

//  #ifdef USE_L6470
    /*Initialize the SPI used by the X-NUCLEO-IMH02A1*/

    MX_SPI_Init();
//    HAL_Delay(100);
    Uart_Send("SPI-L6470 OK!\n");
    HAL_Delay(100);
    /* X-NUCLEO-IHM02A1 initialization */
    BSP_Init();
    Uart_Send("BSP-L6470 OK!\n");

//  #endif

  /*LED screen initialization*/
  MX_I2C1_Init();
  ssd1306_Init();
  Uart_Send("LED OK!\n");

  /*Encoder Init*/
  //MX_TIM2_Init();
  //Uart_Send("TIM OK!\n");

  /*Indicator to show all initialization have been done, if done, turn on the DIAG1 led*/
  HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG1_PIN,GPIO_PIN_SET);

  /*show screen*/
  showscreen();
  BufferInit((uint8_t *) Rx_Buffer,(uint8_t *) Rx_Buffer_former,"Tian",RX_BUFFERSIZE);
  HAL_UART_Transmit_IT(&huart1, (uint8_t *) Rx_Buffer, RX_BUFFERSIZE);
  HAL_Delay(100);
  HAL_UART_Transmit_IT(&huart1, (uint8_t *) Rx_Buffer_former, RX_BUFFERSIZE);
  /*execute home process, for L6470 & POWERSTEP respectively*/
  #ifdef USE_L6470
    uint8_t id;
    
    /*Get parameters*/
    MotorParameterDataGlobal = GetMotorParameterInitData();
    /*Set Paeameters*/
    for (id = 0; id < EXPBRD_MOUNTED_NR; id++)
      {
        /*Get board handler, 1 board in default*/
        StepperMotorBoardHandle = BSP_GetExpansionBoardHandle(EXPBRD_ID(id));
        MotorParameterDataSingle = MotorParameterDataGlobal+(id*L6470DAISYCHAINSIZE);
        StepperMotorBoardHandle->Config(MotorParameterDataSingle);
      }  
    /*Select 1st board and get handler*/
    board = EXPBRD_ID(0);
    StepperMotorBoardHandle = BSP_GetExpansionBoardHandle(board);

    /*DRIVER_0 GRIPPER MOTOR*/
    gripper_motor = L6470_ID(0);
    /*DRIVER_1 TEST MOTOR*/
    test_motor =L6470_ID(1);

    /*Go Home, Test needed to define the right rotation direction*/
    Motor_Find_Home(gripper_motor,L6470_DIR_REV_ID,Step_s_2_Speed(5000));
    /*Can use this function to find to upper position of the motor, orange light should  be on to indicate finish*/
    //Motor_Find_Upper_Position(gripper_motor,L6470_DIR_FWD_ID,Step_s_2_Speed(5000));
    Update_Motor_Pos();
    
    //Just for test, To make sure everything is working well
    // StepperMotorBoardHandle->Command->Move(board, test_motor, L6470_DIR_FWD_ID, 200*128*5);
    // while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, test_motor, BUSY_ID) == 0);
    // StepperMotorBoardHandle->Command->Move(board, test_motor, L6470_DIR_REV_ID, 200*128*5);
    // while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, test_motor, BUSY_ID) == 0);

  #endif

  #ifdef USE_POWERSTEP
    //----- Init of the Powerstep01 library 
    /* Set the Powerstep01 library to use 1 device */
    BSP_MotorControl_SetNbDevices(BSP_MOTOR_CONTROL_BOARD_ID_POWERSTEP01, 1);
    /* When BSP_MotorControl_Init is called with NULL pointer,                  */
    /* the Powerstep01 registers are set with the predefined values from file   */
    /* powerstep01_target_config.h, otherwise the registers are set using the   */
    /* powerstep01_Init_u relevant union of structure values.                   */
    /* The first call to BSP_MotorControl_Init initializes the first device     */
    /* whose Id is 0.                                                           */
    /* The nth call to BSP_MotorControl_Init initializes the nth device         */
    /* whose Id is n-1.                                                         */
    /* Uncomment the call to BSP_MotorControl_Init below to initialize the      */
    /* device with the union declared in the the main.c file and comment the    */
    /* subsequent call having the NULL pointer                                  */
    BSP_MotorControl_Init(BSP_MOTOR_CONTROL_BOARD_ID_POWERSTEP01, &initDeviceParameters);
    //BSP_MotorControl_Init(BSP_MOTOR_CONTROL_BOARD_ID_POWERSTEP01, NULL);

    /* Attach the function MyFlagInterruptHandler (defined below) to the flag interrupt */
    BSP_MotorControl_AttachFlagInterrupt(MyFlagInterruptHandler);

    /* Attach the function MyBusyInterruptHandler (defined below) to the busy interrupt */
    BSP_MotorControl_AttachBusyInterrupt(MyBusyInterruptHandler);
    
    /* Attach the function Error_Handler (defined below) to the error Handler*/
    BSP_MotorControl_AttachErrorHandler(MyErrorHandler);
    //find home, RED led blinking
    Motor_Find_Home(0,BACKWARD,15000); 
    //Motor_Find_Upper_Position(0,FORWARD,10000);
  #endif
    /*DIAG2 LED solid on to indicate initialize compeleted*/
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_SET);
  while(1)
  {
    //Get Modbus data
    MX_LWIP_Process();
	  ModbusTCPMain();

    /*STM32 READ BUF:REG_COILS_BUF*/
    /*if REG_COIL_BUF changed, we need to open the valves, and we only compare first 4 bits as we have 4 valves*/
    if(Buffercmp((uint8_t *) REG_COILS_BUF,(uint8_t *)REG_COILS_BUF_FORMER,VALVE_NUM) != 0)
    {
      //open the valves accordingly
      for(int i=0; i<VALVE_NUM; i++)
      {
        /*if currently the valve is close, we open it*/
        if(REG_COILS_BUF[i]==1  && HAL_GPIO_ReadPin(VALVE_PORT,GPIO_VALVES[i])==GPIO_PIN_RESET && REG_COILS_BUF_FORMER[i]==0)
        {
          HAL_GPIO_WritePin(VALVE_PORT,GPIO_VALVES[i],GPIO_PIN_SET);
          /*Renew the former buffer*/
          REG_COILS_BUF_FORMER[i]=REG_COILS_BUF[i];
          continue;
        }
        /*if currently the valve is open, we close it*/
        if(REG_COILS_BUF[i]==0 && HAL_GPIO_ReadPin(VALVE_PORT,GPIO_VALVES[i])==GPIO_PIN_SET && REG_COILS_BUF_FORMER[i]==1 )
        {
          HAL_GPIO_WritePin(VALVE_PORT,GPIO_VALVES[i],GPIO_PIN_RESET);
          /*Renew the former buffer*/
          REG_COILS_BUF_FORMER[i]=REG_COILS_BUF[i];
          continue;
        }
      }
    }
    //if REG_COILS_BUF[4]==1, means the arm is moving so we can clear the size register
    if(REG_COILS_BUF[VALVE_NUM]==1 && cleared ==FALSE)
    {
      REG_DISC_BUF[0]=0;
      REG_DISC_BUF[1]=0;
      REG_DISC_BUF[2]=0;
      cleared = TRUE;
    }
    HAL_Delay(100);
    #ifdef USE_POWERSTEP
    Pull_And_Run_Motor();
    #endif
    #ifdef USE_L6470
     //Receive Motor Running Cmd Using Uart
    HAL_UART_Receive_IT(&huart1, (uint8_t *)Rx_Buffer,RX_BUFFERSIZE);
    #endif
    /*whiting for control input, DIAG1 led blinking*/
    HAL_GPIO_TogglePin(LED_DIAG_PORT,LED_DIAG1_PIN);
  }

}

void showscreen(void){
      ssd1306_Line(0,0,0,63,White);
      ssd1306_Line(1,0,127,0,White);
      ssd1306_Line(127,1,127,63,White);
      ssd1306_Line(1,63,126,63,White);
      ssd1306_Line(1,13,126,13,White);
      ssd1306_Line(1,25,126,25,White);
      ssd1306_Line(1,37,126,37,White);
      ssd1306_SetCursor(1,3);
      ssd1306_WriteString("      Roplus      ", Font_7x10, White);
      Update_Home_Status();
      ssd1306_SetCursor(1,27);
      ssd1306_WriteString(" Pos: ", Font_7x10, White);
      ssd1306_SetCursor(1,44);
      ssd1306_WriteString("  Gear :    NA    ", Font_7x10, White);  
      ssd1306_UpdateScreen();
      HAL_Delay(200);
}

void Update_Home_Status()
{
  char Home_Flag[9]=" HOME:";
  ssd1306_SetCursor(1,15);
  if(is_home ==FALSE)
  {
      strcat(Home_Flag,"F ");
  }
  else
  {
      strcat(Home_Flag,"T ");
  }
  ssd1306_WriteString(Home_Flag,Font_7x10, White);
}
#ifdef USE_POWERSTEP
void Motor_Find_Home(uint8_t deviceId,motorDir_t dir, uint32_t speed)
{
  BSP_MotorControl_CmdRun(deviceId,dir,speed);
  //let motor run to get the lower/upper limit depends on the limitation until the sensor senses something
  while(HAL_GPIO_ReadPin(SENSOR_EXTI_PORT,SENSOR_EXTI_PIN)==GPIO_PIN_SET)
  {
    HAL_GPIO_TogglePin(LED_PORT,LED3_PIN);
    HAL_Delay(200);
  }
  //Set indicator
  HAL_GPIO_WritePin(LED_PORT,LED3_PIN,GPIO_PIN_SET);
  //Stop motor & set current position as home
  BSP_MotorControl_HardStop(deviceId);
  is_home = TRUE;
  BSP_MotorControl_CmdResetPos(0);
  Update_Home_Status();
  Update_Motor_Pos();
  cur_gear_pos = 0;
  Update_Gear_Status(cur_gear_pos);
}

void Motor_Find_Upper_Position(uint8_t deviceId,motorDir_t dir, uint32_t speed)
{
  BSP_MotorControl_CmdRun(deviceId,dir,speed);
  while(HAL_GPIO_ReadPin(SENSOR_EXTI_PORT,SENSOR_EXTI_PIN_UPPER)==GPIO_PIN_SET)
  {
    HAL_GPIO_TogglePin(LED_PORT,LED2_PIN);
    HAL_Delay(200);
  }
  //Set indicator
  HAL_GPIO_WritePin(LED_PORT,LED2_PIN,GPIO_PIN_SET);
  //Stop moto
  BSP_MotorControl_HardStop(deviceId);
  //Show Pos in led
  Update_Motor_Pos();
  //ssd1306_WriteString("Upper Limit Pos:", Font_7x10, White);
}

void Motor_Cmd_Handler(uint8_t deviceId, uint8_t GearVal)
{
  //Do not move when home is not setup yet
  if(is_home ==FALSE)
  {
    return;
  }
  else{
    if(Get_Desired_Postion_By_Cmd(GearVal)!=-1)
    {
      int desired_pos = Get_Desired_Postion_By_Cmd(GearVal);
      //functions to determin what speed and which direction
      //Only let motor move when desired pos is not equal to cur_pos
      if (desired_pos>cur_pos && desired_pos<=273000)
      {
        //Test for set max step value
        //
        //BSP_MotorControl_CmdSetParam(0,POWERSTEP01_MAX_SPEED, Powerstep01_MaxSpd_Steps_s_to_RegVal(50));
        
        //what to move to upper limit, then we need to go 250000 first, 
        //and then slow down to reach upperlimit for safety
        if(desired_pos == 265000)
        {
            //Set Higher Speed
            BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_HIGH);
            BSP_MotorControl_CmdGoToDir(deviceId,FORWARD,250000);
            BSP_MotorControl_WaitWhileActive(0);
            HAL_Delay(1000);
            //Set Lower Speed
            BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_LOW);
            BSP_MotorControl_CmdGoToDir(deviceId,FORWARD,desired_pos);
            BSP_MotorControl_WaitWhileActive(0);
        }
        //If not,just move 
        else
        {
            //Set Higher Speed
            BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_HIGH);
            BSP_MotorControl_CmdGoToDir(deviceId,FORWARD,desired_pos);
            BSP_MotorControl_WaitWhileActive(0);
        }
        Update_Motor_Pos();
      }
      if(desired_pos<cur_pos && desired_pos>=0)
      {//what to move home, so we first go to 50000 and then slow down to 0
        if(desired_pos == 0)
        {
          //Set Higher Speed
          BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_HIGH);
          BSP_MotorControl_CmdGoToDir(deviceId,BACKWARD,50000);
          BSP_MotorControl_WaitWhileActive(0);
          HAL_Delay(1000);
          //Set Lower Speed
          BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_LOW);
          BSP_MotorControl_CmdGoToDir(deviceId,BACKWARD,desired_pos);
          BSP_MotorControl_WaitWhileActive(0);
        }

        else
        {
          //Set Higher Speed
          BSP_MotorControl_SetAnalogValue(0,POWERSTEP01_MAX_SPEED,SPEED_IN_STEP_S_HIGH);
          BSP_MotorControl_CmdGoToDir(deviceId,BACKWARD,desired_pos);
          BSP_MotorControl_WaitWhileActive(0);
        }
        Update_Motor_Pos();
      }
    }
  }
}

/**
  * @brief  This function is the User handler for the flag interrupt
  * @param  None
  * @retval None
  */
void MyFlagInterruptHandler(void)
{
  /* Get the value of the status register via the command GET_STATUS */
  uint16_t statusRegister = BSP_MotorControl_CmdGetStatus(0);

  /* Check HIZ flag: if set, power brigdes are disabled */
  if ((statusRegister & POWERSTEP01_STATUS_HIZ) == POWERSTEP01_STATUS_HIZ)
  {
    // HIZ state
  }

  /* Check BUSY flag: if not set, a command is under execution */
  if ((statusRegister & POWERSTEP01_STATUS_BUSY) == 0)
  {
    // BUSY
  }

  /* Check SW_F flag: if not set, the SW input is opened */
  if ((statusRegister & POWERSTEP01_STATUS_SW_F ) == 0)
  {
     // SW OPEN
  }
  else
  {
    // SW CLOSED   
  }  
  /* Check SW_EN bit */
  if ((statusRegister & POWERSTEP01_STATUS_SW_EVN) == POWERSTEP01_STATUS_SW_EVN)
  {
    // switch turn_on event
  }  
  /* Check direction bit */
  if ((statusRegister & POWERSTEP01_STATUS_DIR) == 0)
  {
    // BACKWARD
  }
  else  
  {
    // FORWARD 
  }
  if ((statusRegister & POWERSTEP01_STATUS_MOT_STATUS) == POWERSTEP01_STATUS_MOT_STATUS_STOPPED )
  {
       // MOTOR STOPPED
  }
  else  if ((statusRegister & POWERSTEP01_STATUS_MOT_STATUS) == POWERSTEP01_STATUS_MOT_STATUS_ACCELERATION )
  {
           // MOTOR ACCELERATION
  }  
  else  if ((statusRegister & POWERSTEP01_STATUS_MOT_STATUS) == POWERSTEP01_STATUS_MOT_STATUS_DECELERATION )
  {
           // MOTOR DECELERATION
  }
  else  if ((statusRegister & POWERSTEP01_STATUS_MOT_STATUS) == POWERSTEP01_STATUS_MOT_STATUS_CONST_SPD )
  {
       // MOTOR RUNNING AT CONSTANT SPEED
  }  

  /* Check Command Error flag: if set, the command received by SPI can't be */
  /* performed. This occurs for instance when a move command is sent to the */
  /* Powerstep01 while it is already running */
  if ((statusRegister & POWERSTEP01_STATUS_CMD_ERROR) == POWERSTEP01_STATUS_CMD_ERROR)
  {
       // Command Error
  }  

  /* Check Step mode clock flag: if set, the device is working in step clock mode */
  if ((statusRegister & POWERSTEP01_STATUS_STCK_MOD) == POWERSTEP01_STATUS_STCK_MOD)
  {
     //Step clock mode enabled
  }  

  /* Check UVLO flag: if not set, there is an undervoltage lock-out */
  if ((statusRegister & POWERSTEP01_STATUS_UVLO) == 0)
  {
     //undervoltage lock-out 
  }  

  /* Check UVLO ADC flag: if not set, there is an ADC undervoltage lock-out */
  if ((statusRegister & POWERSTEP01_STATUS_UVLO_ADC) == 0)
  {
     //ADC undervoltage lock-out 
  } 
  
  /* Check thermal STATUS flags: if  set, the thermal status is not normal */
  if ((statusRegister & POWERSTEP01_STATUS_TH_STATUS) != 0)
  {
    //thermal status: 1: Warning, 2: Bridge shutdown, 3: Device shutdown
  }    

  /* Check OCD  flag: if not set, there is an overcurrent detection */
  if ((statusRegister & POWERSTEP01_STATUS_OCD) == 0)
  {
    //overcurrent detection 
  }      

  /* Check STALL_A flag: if not set, there is a Stall condition on bridge A */
  if ((statusRegister & POWERSTEP01_STATUS_STALL_A) == 0)
  {
    //overcurrent detection 
  }    

  /* Check STALL_B flag: if not set, there is a Stall condition on bridge B */
  if ((statusRegister & POWERSTEP01_STATUS_STALL_B) == 0)
  {
    //overcurrent detection 
  }      

}

/**
  * @brief  This function is the User handler for the busy interrupt
  * @param  None
  * @retval None
  */
void MyBusyInterruptHandler(void)
{

   if (BSP_MotorControl_CheckBusyHw())
   {
    //HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_SET);
      /* Busy pin is low, so at list one Powerstep01 chip is busy */
     /* To be customized (for example Switch on a LED) */
   }
   else
   {
    //HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_RESET);
     /* To be customized (for example Switch off a LED) */
   }
}
#endif
void Update_Motor_Pos()
{
  //Position start cursor
  ssd1306_SetCursor(43,27);
  //Clear Screen first
  ssd1306_WriteString("            ", Font_7x10, White); 
  ssd1306_UpdateScreen();
  ssd1306_SetCursor(43,27);
  #ifdef USE_POWERSTEP
  cur_pos = BSP_MotorControl_GetPosition(0);
  #endif
  #ifdef USE_L6470
  cur_pos = (int32_t)StepperMotorBoardHandle->Command->GetParam(board, gripper_motor, L6470_ABS_POS_ID);
  #endif
  char position[11];
  sprintf(position, "%ld", cur_pos);
  ssd1306_WriteString(position, Font_7x10, White);    
  ssd1306_UpdateScreen();
}

void Update_Gear_Status(uint8_t GearVal)
{
  char Gear[3]; 
  char Gear_Status[3]=" ";
  sprintf(Gear,"%d", GearVal);
  strcat(Gear_Status,Gear);
  ssd1306_SetCursor(84,44);
  ssd1306_WriteString(Gear_Status,Font_7x10,White);
  ssd1306_UpdateScreen();
}

void Pull_And_Run_Motor()
{
  // Cmd is not enabled, just return
  if(HAL_GPIO_ReadPin(UR_INPUT_PORT,UR_INPUT_PIN1) == GPIO_PIN_RESET)
  {
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG1_PIN,GPIO_PIN_RESET);
    return;
  }
  else{
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG1_PIN,GPIO_PIN_SET);
    if(PinState_To_Int(UR_INPUT_PORT,UR_INPUT_PIN2)== -1 || PinState_To_Int(UR_INPUT_PORT,UR_INPUT_PIN3)==-1)
    {
      return;
    }
    uint8_t bit_high = PinState_To_Int(UR_INPUT_PORT,UR_INPUT_PIN2);
    uint8_t bit_low =  PinState_To_Int(UR_INPUT_PORT,UR_INPUT_PIN3);
    uint8_t new_gear_pos = bit_high*2 +bit_low;
    //If new gear pos is same as former one,or invaild comd, just return and don not move
    if(cur_gear_pos == new_gear_pos || Get_Desired_Postion_By_Cmd(new_gear_pos)==-1)
    {
      return;
    }
    else
    {
      //vaild Cmd, then update led, and update cur_gear_pos
      cur_gear_pos = new_gear_pos;
      Update_Gear_Status(cur_gear_pos);
      #ifdef  USE_POWERSTEP
      Motor_Cmd_Handler(0,cur_gear_pos);
      #endif
    }
  }
}

uint8_t PinState_To_Int(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)== GPIO_PIN_SET)
  {
    return 1;
  }

  if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin)== GPIO_PIN_RESET)
  {
    return 0;
  }
  return -1;
}

uint32_t Get_Desired_Postion_By_Cmd(uint8_t GearVal) 
{
  uint32_t desired_pos=-1;
  switch (GearVal)
  {
  //Gear 0 
  case 0:
    desired_pos = 0;
    break;  
  //Gear 1
  case 1:
    desired_pos = 50000;
    break;
  //Gear 2
  case 2:
    desired_pos = 150000;
    //desired_pos = 100000;
    break;
  //Gear 3
  case 3:
    desired_pos = 250000;
    //desired_pos = 150000;
    break;
  //Gear 4
  // case 4:
  //   desired_pos = 200000;
  //   break;
  // //Gear 5
  // case 5: 
  //   desired_pos = 250000;
  // //Gear 6
  // case 6:
  //   desired_pos = 265000;  
  //Invailed Input
  default:
    desired_pos = -1; 
    break;
  }
  return desired_pos;
}

void Roplus_Pin_Init()
{ 
  //Enable GPIO Clock
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  //Sensor Pin Init
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = SENSOR_EXTI_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(SENSOR_EXTI_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SENSOR_EXTI_PIN_UPPER;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(SENSOR_EXTI_PORT, &GPIO_InitStruct);

  //Reset all values
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_RESET);

  // Valves Pin init,
  GPIO_InitStruct.Pin = VALVE_1_PIN|VALVE_2_PIN|VALVE_3_PIN|VALVE_4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VALVE_PORT, &GPIO_InitStruct);
   
  //UR input Pin init, no  pull  mode
  GPIO_InitStruct.Pin = UR_INPUT_PIN1|UR_INPUT_PIN2|UR_INPUT_PIN3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(UR_INPUT_PORT, &GPIO_InitStruct);

  //LED Pin Init
  GPIO_InitStruct.Pin = LED_DIAG2_PIN|LED_DIAG1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_DIAG_PORT, &GPIO_InitStruct);

  //LED Pin Init
  GPIO_InitStruct.Pin = LED_RUN_PIN|LED_COMM_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_STATUS_PORT, &GPIO_InitStruct);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	counter = __HAL_TIM_GET_COUNTER(htim);
	count = (int16_t)counter;
	position = count/4;
  //Can not concurrently update the screen
  //HAL_GPIO_TogglePin(LED_PORT,LED2_PIN);
  //   HAL_Delay(200);
  // ssd1306_SetCursor(43,27);
  // //Clear Screen first
  // ssd1306_WriteString("            ", Font_7x10, White); 
  // ssd1306_UpdateScreen();
  // ssd1306_SetCursor(43,27);
  // char pos_[11];
  // sprintf(pos_, "%d", position);
  // ssd1306_WriteString(pos_, Font_7x10, White);    
  // ssd1306_UpdateScreen();
}

void MyErrorHandler(uint16_t error)
{
  /* Backup error number */
  gLastError = error; 
  /* Infinite loop */
  while(1)
  {
    //BLINK DIAG2 LED
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_RESET);
    HAL_Delay(100);
  }
}

void Error_Handler()
{
  __disable_irq();
  while (1)
  {
    //BLINKE DIAG2 LED
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_RESET);
    HAL_Delay(100);
  }
}

#ifdef USE_L6470
void Motor_Find_Home(uint8_t deviceId,eL6470_DirId_t dir, uint32_t speed)
{
   StepperMotorBoardHandle->Command->Run(board, deviceId, dir, speed);
   while(HAL_GPIO_ReadPin(SENSOR_EXTI_PORT,SENSOR_EXTI_PIN)==GPIO_PIN_SET)
    {
      //Blinking DIAG2 while finfing home
      HAL_GPIO_TogglePin(LED_DIAG_PORT,LED_DIAG2_PIN);
      HAL_Delay(200);
    }
    //Set indicator
    //HAL_GPIO_WritePin(LED_COMM_PORT,LED3_PIN,GPIO_PIN_SET);
    //Stop motor & set current position as home
    StepperMotorBoardHandle->Command->HardStop(board,deviceId);
    is_home = TRUE;
    StepperMotorBoardHandle->Command->ResetPos(board,deviceId);
    Update_Home_Status();
    Update_Motor_Pos();
    cur_gear_pos = 0;
    Update_Gear_Status(cur_gear_pos);
}
#endif

void Motor_Find_Upper_Position(uint8_t deviceId,eL6470_DirId_t dir, uint32_t speed)
{
  StepperMotorBoardHandle->Command->Run(board, deviceId, dir, speed);
  while(HAL_GPIO_ReadPin(SENSOR_EXTI_PORT,SENSOR_EXTI_PIN_UPPER)==GPIO_PIN_SET)
  {
    //Blinking DIAG2 while finfing upper position
    HAL_GPIO_TogglePin(LED_DIAG_PORT,LED_DIAG2_PIN);
    HAL_Delay(200);
  }
  //Set indicator
  HAL_GPIO_WritePin(LED_DIAG_PORT,LED_DIAG2_PIN,GPIO_PIN_SET);
  //Stop motor
  StepperMotorBoardHandle->Command->HardStop(board,deviceId);
  //Show Pos in led
  Update_Motor_Pos();
}


/**
  * @brief  Calculates the power of a number.
  * @param  base      the base
  * @param  exponent  the exponent
  * @retval power     the result as (base^exponent)
  * @note   There is not OVF control.
  */
uint32_t usrPow(uint8_t base, uint8_t exponent)
{
  uint8_t i;
  uint32_t power = 1;
  
  for (i=0; i<exponent; i++)
    power *= base;
  
  return power;
}

//Receive process finished
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /*Received, toggle COMM LED*/
  HAL_GPIO_TogglePin(LED_STATUS_PORT,LED_COMM_PIN);
  //Different Msg Received
  if(Buffercmp((uint8_t *) Rx_Buffer,(uint8_t *)Rx_Buffer_former,RX_BUFFERSIZE) != 0)
  {
    //HAL_USART_Transmit_IT(&huart5, (uint8_t *) Rx_Buffer, RX_BUFFERSIZE);
    if(Rx_Buffer[0] != 'A')
    {
      return;
    }
    /*Parse the string and get the desired motor position*/
    else
    {
      //Inidicate one transmission complete, toggle the RUN LED
      HAL_GPIO_TogglePin(LED_STATUS_PORT,LED_RUN_PIN);
      //The arm is running, so cannot response, just skip
      if(REG_COILS_BUF[VALVE_NUM]==1)
      {
        return;
      }
      BufferCopy((uint8_t *) Rx_Buffer,(uint8_t *)Rx_Buffer_former,RX_BUFFERSIZE);
      //HAL_USART_Transmit_IT(&huart5, (uint8_t *) Rx_Buffer_former, RX_BUFFERSIZE);
      
      //Get Desired Pos
      uint32_t Desired_Pos = BufferParse((uint8_t *) Rx_Buffer);
      /*Successful parsed*/
      if(Desired_Pos != -1)
      {
        if(Desired_Pos!=cur_pos)
        {
          /*Double check the range*/
          if(Desired_Pos >=2200000)
          {
            Desired_Pos =2200000;
          }
          if(Desired_Pos<=200000)
          {
            Desired_Pos = 200000;
          }
          /*One Direction*/
          if(Desired_Pos>cur_pos)
          {
            StepperMotorBoardHandle->Command->GoToDir(board, gripper_motor, L6470_DIR_FWD_ID, Desired_Pos);
            while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, gripper_motor, BUSY_ID) == 0)
            {
               //Just in case the motor reach upper limit
                MX_LWIP_Process();
	              ModbusTCPMain();
            }
            Update_Motor_Pos();
            
          }
          /*Annother Direction*/
          if(Desired_Pos<cur_pos)
          {
            StepperMotorBoardHandle->Command->GoToDir(board, gripper_motor, L6470_DIR_REV_ID, Desired_Pos);
            while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, gripper_motor, BUSY_ID) == 0)
            {
              //Just in case the motor reach lower limit
              MX_LWIP_Process();
	            ModbusTCPMain();
            }
            Update_Motor_Pos();
          }
          /*Send Modbus Msg*/
          /*Small Size*/
          if(Desired_Pos<=500000)
          {
            REG_DISC_BUF[0]=1;
          }
          /*Middle Size*/
          if(Desired_Pos>500000 && Desired_Pos<=1200000)
          {
            REG_DISC_BUF[1]=1;
          }
          /*Large Size*/
          if(Desired_Pos >1200000&&Desired_Pos<=2200000)
          {
            REG_DISC_BUF[2]=1;
          }
          cleared = FALSE;
          Uart_Send("M");
        }
      }
    }
  }
  //Same Msg Received, the motor shouldn't move, but we need to move the robot arm
  else
  {

    /*Same buffer, so no need to check whether the first byte is equal to 'A'*/
    //HAL_GPIO_TogglePin(LED_PORT,LED2_PIN);
    //The arm is running, so cannot response, just skip
    if(REG_COILS_BUF[VALVE_NUM]==1)
    {
      return;
    }
    //Get Desired Pos
    uint32_t Desired_Pos = BufferParse((uint8_t *) Rx_Buffer);
     /*Send Modbus Msg*/
    /*Small Size*/
    if(Desired_Pos<=500000)
    {
      REG_DISC_BUF[0]=1;
    }
    /*Middle Size*/
    if(Desired_Pos>500000 && Desired_Pos<=1200000)
    {
      REG_DISC_BUF[1]=1;
    }
    /*Large Size*/
    if(Desired_Pos >1200000&&Desired_Pos<=2200000)
    {
      REG_DISC_BUF[2]=1;
    }
    cleared = FALSE;
    Uart_Send("M");
  }
}

uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}
void BufferInit(uint8_t* pBuffer1, uint8_t* pBuffer2, char *string ,uint16_t BufferLength)
{
  if (strlen(string) != BufferLength)
  {
    while(BufferLength--)
    {
      *pBuffer1 = 'E';
      *pBuffer2 = 'E';
      pBuffer1++;
      pBuffer2++;
    }
  }
  else{
    while(BufferLength--)
    {
      *pBuffer1 = *pBuffer2 = *string;
      pBuffer1++;
      pBuffer2++;
      string++;
    }
  }
}

void BufferCopy(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    *pBuffer2= *pBuffer1;
    pBuffer1++;
    pBuffer2++;
  }
}
uint32_t BufferParse(uint8_t* posBuffer)
{
  //minimum postion
  uint32_t pos = 0;
  /*Double Check the msg*/
  if(posBuffer[0] !='A')
  {
    return -1;
  }
  bool find_first = false;
  for(int i=1;i<=7;i++)
  {
    /*Find First None 0*/
    if(find_first ==false && posBuffer[i]!='0')
    {
      find_first = true;
      if(posBuffer[i]>=48 && posBuffer[i]<=57)
      {
        pos+=(posBuffer[i]-48)*usrPow(10,7-i);
      }
      else
      {
        return -1;
      }
      break;
    }
    if(find_first == true)
    {
      if(posBuffer[i]>=48 && posBuffer[i]<=57)
      {
        pos+=(posBuffer[i]-48)*usrPow(10,8-i);
      }
      else
      {
        return -1;
      }
    }
  }
  if(pos>=2200000)
  {
    pos = 2200000;
  }
  if(pos<=200000)
  {
    pos=200000;
  }
  return pos;
}

//suction process, just to test the whole logic
void suction_test()
{
  //OPEN VALUE 3&4, BEGIN SUCTION
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_SET);
  HAL_Delay(500);
  //extention, open value 1&3
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);
  //bending &jamming, open 2
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);
  //bending open 3
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);
  //Reset
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_2_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_3_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_4_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);
}
