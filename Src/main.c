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
int32_t Desired_Pos;
char gear_status[2];
uint32_t counter = 0;
int16_t count = 0;
int16_t position = 0;

uint8_t Rx_Buffer[RX_BUFFERSIZE];
uint8_t Rx_Buffer_former[RX_BUFFERSIZE];
uint8_t board;
uint8_t gripper_motor;
uint8_t test_motor;
uint16_t GPIO_VALVES[VALVE_NUM] = {VALVE_SUCTION_PIN,VALVE_BENDING_C_PIN,VALVE_BENDING_O_PIN,VALVE_JAMMING_PIN};

//STM32 WRITE BUFgi
uint8_t REG_DISC_BUF[10]={0,0,0,0,0,0,0,0,0,0};
//STM32 READ BUF
uint8_t REG_COILS_BUF[10]={0,0,0,0,0,0,0,0,0,0};
uint8_t REG_COILS_BUF_FORMER[10]={0,0,0,0,0,0,0,0,0,0};

uint8_t suction_bit = 0;
uint8_t suction_bit_former = 0;
uint8_t eth_status = 0;
uint8_t eth_status_former = 0; 
uint8_t gear_buff_former[2] = {0,0};
uint8_t gear_buff[2] = {0,0};
uint32_t Vacuum_ADCvalues;
bool cleared = TRUE;
bool ps_error = FALSE;

#ifdef USE_L6470
//Handler & Parameter container for L6470PD
StepperMotorBoardHandle_t *StepperMotorBoardHandle;
MotorParameterData_t *MotorParameterDataGlobal, *MotorParameterDataSingle;
#endif

int main(void)
{
  /* STM32F4xx HAL library initialization */
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();
  
  /*Initialize pin used for Roplus*/
  Roplus_Pin_Init();
  
  /*UART initialization, used for debug*/
  MX_USART1_Init();
  Uart_Send("UART OK!\n");
  HAL_Delay(100);

  //Modbus initialization
  MX_LWIP_Init();
  ModbusTCPInit();
  Uart_Send("Modbus OK!\n");
  HAL_Delay(100);

  //ADC initialization
  MX_ADC1_Init();
  MX_ADC2_Init();
  Uart_Send("ADC OK!\n");
  HAL_Delay(100);

  #ifdef USE_L6470
    /*Initialize the SPI used by the X-NUCLEO-IMH02A1*/
    MX_SPI_Init();
    // HAL_Delay(100);
    Uart_Send("SPI-L6470 OK!\n");
    HAL_Delay(100);
    /* X-NUCLEO-IHM02A1 initialization */
    BSP_Init();
    Uart_Send("BSP-L6470 OK!\n");
  #endif

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
  //show screen menu, indicate the homing process
  clearscreen();
  eth_status = DetectEthernetCable();
  eth_status_former = eth_status;
  Update_Eth_Status_Led();
  screenmenu();
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
    Motor_Find_Home(gripper_motor,L6470_DIR_REV_ID,Step_s_2_Speed(MOTOR_HOME_SPEED));
    /*Can use this function to find to upper position of the motor, orange light should  be on to indicate finish*/
    //Motor_Find_Upper_Position(gripper_motor,L6470_DIR_FWD_ID,Step_s_2_Speed(5000));
    //Update_Motor_Pos();

  #endif

  #ifdef USE_POWERSTEP
    //----- Init of the Powerstep01 library, SPI also initialized here
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
    if (ps_error)
    {
      continue;
    }
    
    //If the first bit of REG_COILS_BUF is 1 or the UR_IO_ENABLE_PIN is high, means the robot arm is moving, or the ps_error is set, so just skip the loop
    if(REG_COILS_BUF[0] ==1 || (HAL_GPIO_ReadPin(UR_IO_PORT,UR_IO_ENABLE_PIN)==GPIO_PIN_RESET))
    {
      // if (HAL_GPIO_ReadPin(UR_IO_PORT,UR_IO_ENABLE_PIN)==GPIO_PIN_SET)
      // {
      //   Uart_Send("I/O high\n");
      // }
      //Blink the COMM LED to indicate the error
      HAL_GPIO_TogglePin(LED_STATUS_PORT,LED_COMM_PIN);
      HAL_Delay(100);
      if (cleared ==FALSE)
      {
        cleared = TRUE;
      }
      REG_DISC_BUF[0]=0;
      HAL_GPIO_WritePin(MOTOR_READY_DIGITAL_OUTPUT_PORT,MOTOR_READY_DIGITAL_OUTPUT_PIN,GPIO_PIN_RESET);
      continue;
    }
    //The arm is not moving, so we can move the motor, this is achieved by get the desired position from three control intereface
    //Modbus TCP, UART, and UR IO
    else
    {
      // first get desired position from uart, to check if a msg come and modified the desired position
      #ifdef USE_L6470
      //Receive Motor Running Cmd Using Uart
        HAL_UART_Receive_IT(&huart1, (uint8_t *)Rx_Buffer,RX_BUFFERSIZE);
      #endif

      #ifdef USE_POWERSTEP
      Pull_And_Run_Motor();
      #endif
      if(cleared == FALSE)
      {
        continue;
      }
      //Then we check the UR IO combine with the modbus and move the motor
      Update_gear_buf();
      //if the bits have changed, we need to run the motor
      if(Buffercmp((uint8_t *) gear_buff,(uint8_t *)gear_buff_former,2) != 0)
      {
        uint8_t gear  = gear_buff[0]*2+gear_buff[1]*1;
        Desired_Pos = Gear_To_Position(gear);
        if(Desired_Pos == -1)
        {
          continue;
        }
        Desired_Pos = Pos_Saturate(Desired_Pos);
        Rotate_Motor(Desired_Pos);
        REG_DISC_BUF[0]=1;
        HAL_GPIO_WritePin(MOTOR_READY_DIGITAL_OUTPUT_PORT,MOTOR_READY_DIGITAL_OUTPUT_PIN,GPIO_PIN_SET);
        gear_status[0] = gear/10+'0';
        gear_status[1] = gear%10+'0';
        Update_Gear_Status();
        BufferCopy((uint8_t *) gear_buff,(uint8_t *)gear_buff_former,2); 
      }
    }
    //suction can be triggered at any time, as long as there's no error from thr pressure sensor
    suction_bit = (REG_COILS_BUF[3]==1) || (HAL_GPIO_ReadPin(UR_IO_PORT,UR_IO_SUCTION_PIN)== GPIO_PIN_RESET);
    if(suction_bit !=suction_bit_former)
    {
      suction();
      if(!ps_error)
      {
        suction_bit_former = suction_bit;
        Update_Suction_Status_Led();
      }
      else
      {
        Show_Err_Led();
      }
    }
    //Update Ethernet status
    eth_status = DetectEthernetCable();
    if(eth_status!=eth_status_former)
    {
      Update_Eth_Status_Led();
      eth_status_former = eth_status;
    }
    HAL_Delay(100);
    /*whiting for control input, DIAG1 led blinking*/
    HAL_GPIO_TogglePin(LED_DIAG_PORT,LED_DIAG1_PIN);
  }

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
      //The arm is running, so cannot response, just skip
      if(REG_COILS_BUF[0]==1)
      {
        return;
      }
      BufferCopy((uint8_t *) Rx_Buffer,(uint8_t *)Rx_Buffer_former,RX_BUFFERSIZE);
      //HAL_USART_Transmit_IT(&huart5, (uint8_t *) Rx_Buffer_former, RX_BUFFERSIZE);
      
      //Get Desired Pos
      Desired_Pos = BufferParse((uint8_t *) Rx_Buffer);
      // if(Desired_Pos == -1)
      // {
      //   Uart_Send("inp");
      // }
      /*Successful parsed*/
      if(Desired_Pos != -1)
      {
        if(Desired_Pos!=cur_pos)
        {
          /*Double check the range*/
          Desired_Pos=Pos_Saturate(Desired_Pos);
          /*One Direction*/
          Rotate_Motor(Desired_Pos);
          REG_DISC_BUF[0]=1;
          HAL_GPIO_WritePin(MOTOR_READY_DIGITAL_OUTPUT_PORT,MOTOR_READY_DIGITAL_OUTPUT_PIN,GPIO_PIN_SET);
          uint8_t gear = (Rx_Buffer[7]-48)*1+(Rx_Buffer[6]-48)*2+(Rx_Buffer[5]-48)*4+(Rx_Buffer[4]-48)*8;
          gear_status[0] = gear/10+'0';
          gear_status[1] = gear%10+'0';
          Update_Gear_Status();          
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
    //The arm is running, so cannot response, just skip
    if(REG_COILS_BUF[0]==1)
    {
      return;
    }
    //Get Desired Pos
    //Desired_Pos = BufferParse((uint8_t *) Rx_Buffer);
    REG_DISC_BUF[0]=1;
    HAL_GPIO_WritePin(MOTOR_READY_DIGITAL_OUTPUT_PORT,MOTOR_READY_DIGITAL_OUTPUT_PIN,GPIO_PIN_SET);
    uint8_t gear = (Rx_Buffer[7]-48)*1+(Rx_Buffer[6]-48)*2+(Rx_Buffer[5]-48)*4+(Rx_Buffer[4]-48)*8;
    gear_status[0] = gear/10+'0';
    gear_status[1] = gear%10+'0';
    Update_Gear_Status();
    cleared = FALSE;
    Uart_Send("M");
  }
}

void showscreen(void){
    ssd1306_Line(0,0,0,63,White);
    ssd1306_Line(1,0,127,0,White);
    ssd1306_Line(127,1,127,63,White);
    ssd1306_Line(1,63,126,63,White);
    ssd1306_SetCursor(1,3);
    ssd1306_WriteString("      Roplus      ", Font_7x10, White);
    ssd1306_SetCursor(1,20);
    ssd1306_WriteString("   Initializing    ", Font_7x10, White);
    ssd1306_UpdateScreen();
    //HAL_Delay(200);
}

void clearscreen(void){
  ssd1306_Fill( Black );
  ssd1306_UpdateScreen();
}

void Update_Home_Status()
{
  ssd1306_SetCursor(56,53);
  if(is_home ==FALSE)
  {
    ssd1306_WriteString("F",Font_7x10, White);
  }
  else
  {
    ssd1306_WriteString("T",Font_7x10, White);
  }
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
 // ssd1306_SetCursor(43,27);
  //Clear Screen first
  // ssd1306_WriteString("            ", Font_7x10, White); 
  // ssd1306_UpdateScreen();
  // ssd1306_SetCursor(43,27);
  #ifdef USE_POWERSTEP
  cur_pos = BSP_MotorControl_GetPosition(0);
  #endif
  #ifdef USE_L6470
  cur_pos = (int32_t)StepperMotorBoardHandle->Command->GetParam(board, gripper_motor, L6470_ABS_POS_ID);
  #endif
  // char position[11];
  // sprintf(position, "%ld", cur_pos);
  // ssd1306_WriteString(position, Font_7x10, White);    
  // ssd1306_UpdateScreen();
}

void Update_Gear_Status()
{
  ssd1306_SetCursor(112,53);
  ssd1306_WriteString(gear_status,Font_7x10,White);
  ssd1306_UpdateScreen();
}

#ifdef POWERSTEP
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
#endif

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
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_BENDING_C_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_SUCTION_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT,VALVE_JAMMING_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(VALVE_PORT_BENDING,VALVE_BENDING_O_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MOTOR_READY_DIGITAL_OUTPUT_PORT,MOTOR_READY_DIGITAL_OUTPUT_PIN,GPIO_PIN_RESET);
  // Valves Pin init,
  GPIO_InitStruct.Pin = VALVE_BENDING_C_PIN|VALVE_SUCTION_PIN|VALVE_JAMMING_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VALVE_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = VALVE_BENDING_O_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VALVE_PORT_BENDING, &GPIO_InitStruct);

  //Motor Ready Pin init
  GPIO_InitStruct.Pin = MOTOR_READY_DIGITAL_OUTPUT_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MOTOR_READY_DIGITAL_OUTPUT_PORT, &GPIO_InitStruct);

  //UR input Pin init, no  pull  mode
  GPIO_InitStruct.Pin = UR_IO_ENABLE_PIN|UR_IO_PIN1|UR_IO_PIN2|UR_IO_PIN3|UR_IO_PIN4|UR_IO_SUCTION_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(UR_IO_PORT, &GPIO_InitStruct);

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
}

#ifdef USE_POWERSTEP
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
#endif

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
    //Stop motor & set current position as home
    StepperMotorBoardHandle->Command->HardStop(board,deviceId);
    is_home = TRUE;
    StepperMotorBoardHandle->Command->ResetPos(board,deviceId);
    Update_Home_Status();
    gear_status[0] = 'H';
    gear_status[1] = ' ';
    Update_Gear_Status();
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



void screenmenu(void){
  ssd1306_SetCursor(1,17);
  ssd1306_WriteString(" SUCTION    ", Font_7x10, White);
  ssd1306_SetCursor(1,29);
  ssd1306_WriteString(" JAMMING    ", Font_7x10, White);
  ssd1306_SetCursor(1,41);
  ssd1306_WriteString(" BENDING    ", Font_7x10, White);
  ssd1306_SetCursor(80,17);
  ssd1306_WriteString(" OFF   ", Font_7x10, White);
  ssd1306_SetCursor(80,41);
  ssd1306_WriteString(" ---    ", Font_7x10, White);
  ssd1306_SetCursor(80,29);
  ssd1306_WriteString(" ---    ", Font_7x10, White);
  ssd1306_SetCursor(1,53);
  ssd1306_WriteString(" MOTOR: F  GEAR: A", Font_7x10, White);
  ssd1306_UpdateScreen();
}

uint8_t DetectEthernetCable(void) {
  uint32_t phyRegValue = 0;

  if (HAL_ETH_ReadPHYRegister(&heth, 0x01, PHY_BSR, &phyRegValue) == HAL_OK) {
      // Link Status
      if (phyRegValue & PHY_LINK_STATUS) {
          return 1;  // connected
      }
  }

  return 0;  // no connection
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

void Rotate_Motor(int32_t d_Pos)
{
  if(d_Pos>cur_pos)
    {
      StepperMotorBoardHandle->Command->GoToDir(board, gripper_motor, L6470_DIR_FWD_ID, d_Pos);
      while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, gripper_motor, BUSY_ID) == 0)
      {
          //Just in case the motor reach upper limit
          MX_LWIP_Process();
          ModbusTCPMain();
      }
      //Update cur_pos
      Update_Motor_Pos();
    }
    /*Annother Direction*/
    if(d_Pos<cur_pos)
    {
      StepperMotorBoardHandle->Command->GoToDir(board, gripper_motor, L6470_DIR_REV_ID, d_Pos);
      while(StepperMotorBoardHandle->Command->CheckStatusRegisterFlag(board, gripper_motor, BUSY_ID) == 0)
      {
        //Just in case the motor reach lower limit
        MX_LWIP_Process();
        ModbusTCPMain();
      }
      Update_Motor_Pos();
    }
}

void Update_gear_buf()
{
  gear_buff[0] = (REG_COILS_BUF[1]==1) || (HAL_GPIO_ReadPin(UR_IO_PORT,UR_IO_PIN1)== GPIO_PIN_RESET);
  gear_buff[1] = (REG_COILS_BUF[2]==1) || (HAL_GPIO_ReadPin(UR_IO_PORT,UR_IO_PIN2)== GPIO_PIN_RESET);
}

void suction() {  //suction
  if (suction_bit) {
    HAL_GPIO_WritePin(VALVE_PORT, VALVE_SUCTION_PIN, GPIO_PIN_SET);
      HAL_ADC_Start(&hadc1);
   	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
   	  Vacuum_ADCvalues=HAL_ADC_GetValue(&hadc1);//read suction adc value
    if(Vacuum_ADCvalues > 1800)
       {
    	REG_DISC_BUF[5]=1;
       }
    else{
    	REG_DISC_BUF[5]=0;//this is suction engaged bit in modbus buffer, used for ensuring safely suction
    }
  } else {
	HAL_GPIO_WritePin(VALVE_PORT, VALVE_SUCTION_PIN, GPIO_PIN_RESET);
	REG_DISC_BUF[5]=0;
  }
}

void Update_Suction_Status_Led()
{
  ssd1306_SetCursor(80,17);
  if (suction_bit==1){
    ssd1306_WriteString(" ON    ", Font_7x10, White);
  }
  else{
  ssd1306_WriteString(" OFF   ", Font_7x10, White);
  }
  ssd1306_UpdateScreen();
}

void Update_Eth_Status_Led()
{
  ssd1306_SetCursor(1,3);
  if (eth_status ==1)
  {
    ssd1306_WriteString(" MODBUS IO MODE     ", Font_7x10, White);
  }
  else
  {
    ssd1306_WriteString(" IO ONLY MODE     ", Font_7x10, White);
  }
  ssd1306_UpdateScreen();
}

void Show_Err_Led()
{
  ssd1306_SetCursor(80,17);
  ssd1306_WriteString(" ERR   ", Font_7x10, White);
  ssd1306_UpdateScreen();
}

//gear value is from 1 - 3
int32_t Gear_To_Position(uint8_t gear)
{
  switch (gear)
  {
  case 1:
    return GEAR1_POS;
    break;
  case 2:
    return GEAR2_POS;
  case 3: 
    return GEAR3_POS;
  default:
    return -1;
    break;
  }

}

int32_t Pos_Saturate(int32_t pos)
{
  int32_t p = pos;
  if(p>=POS_UPPER_LIMIT)
  {
    p = POS_UPPER_LIMIT;
  }
  if(p<=POS_LOWER_LIMIT)
  {
    p= POS_LOWER_LIMIT;
  }
  return p;
}