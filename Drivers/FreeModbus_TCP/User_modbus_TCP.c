#include <stdio.h>
#include <string.h>
#include "User_modbus_TCP.h"
#include "mb.h"
#include "mbutils.h"

void ModbusTCPInit(void)
{
    eMBTCPInit(MODBUS_TCP_PORT);
    eMBEnable();
}

void ModbusTCPDeInit(void)
{
    eMBDisable();
    eMBClose();
}

void ModbusTCPMain(void)
{
    if (MB_ENOERR != eMBPoll())
    {
        ModbusTCPDeInit();
        ModbusTCPInit();
    }
}


// 十路线圈
#define REG_COILS_SIZE      10
//uint8_t REG_COILS_BUF[REG_COILS_SIZE];
extern uint8_t REG_COILS_BUF[10];

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	 USHORT usRegIndex   = usAddress - 1;;
	 USHORT usCoilGroups = ((usNCoils - 1) / 8 + 1);
	 UCHAR  ucStatus     = 0;
	 UCHAR  ucBits       = 0;

	 UCHAR  ucDisp       = 0;
	 // 非法检测
	 if((usRegIndex + usNCoils)> REG_COILS_SIZE)
	 {
		 return MB_ENOREG;
	 }
	 // 写线圈
	 if(eMode == MB_REG_WRITE)
	 {
	     while(usCoilGroups--)
	     {
	        ucStatus=*pucRegBuffer++;
	        ucBits =8;
	        while((usNCoils--)!=0&& (ucBits--)!= 0)
	        {
	         REG_COILS_BUF[usRegIndex++]= ucStatus & 0X01;
	         ucStatus >>=1;
	        }
	     }

      }

	 // 读线圈
	     else
	     {
	         while(usCoilGroups--)
	         {
	             ucDisp = 0;
	             ucBits = 8;
	             while((usNCoils--) != 0 && (ucBits--) != 0)
	             {
	                 ucStatus |= (REG_COILS_BUF[usRegIndex++] << (ucDisp++));
	             }
	             *pucRegBuffer++ = ucStatus;
	         }
	     }
	     return MB_ENOERR;
	 }

// 十路离散量
#define REG_DISC_SIZE  10
//uint8_t REG_DISC_BUF[10]={0,0,1,0,1};
extern uint8_t REG_DISC_BUF[10];
 //离散寄存器
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	USHORT usRegIndex   = usAddress - 1;
	    USHORT usCoilGroups = ((usNDiscrete - 1) / 8 + 1);
	    UCHAR  ucStatus     = 0;
	    UCHAR  ucBits       = 0;
	    UCHAR  ucDisp       = 0;

	    // 非法检测
	    if((usRegIndex + usNDiscrete) > REG_DISC_SIZE)
	    {
	        return MB_ENOREG;
	    }

	        // 读离散输入
	        while(usCoilGroups--)
	        {
	                ucDisp = 0;
	                ucBits = 8;
	                while((usNDiscrete--) != 0 && (ucBits--) != 0)
	                {
	                        if(REG_DISC_BUF[usRegIndex])
	                        {
	                                ucStatus |= (1 << ucDisp);
	                        }
	                        ucDisp++;
	                }
	                *pucRegBuffer++ = ucStatus;
	        }

//	    // 模拟改变
//	    for(usRegIndex = 0; usRegIndex < REG_DISC_SIZE; usRegIndex++)
//	    {
//	        REG_DISC_BUF[usRegIndex] = !REG_DISC_BUF[usRegIndex];
//	    }

	    return MB_ENOERR;

}





//保持寄存器
#define REG_HOLDING_REGISTER_START   0
#define REG_HOLDING_REGISTER_SIZE    30

uint16_t  Holding_Data[REG_HOLDING_REGISTER_SIZE] = 
{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12};

/**
 * @brief: 读保持寄存器---03，写保持寄存器---06
 *
 * @param pucRegBuffer  缓存指针
 * @param usAddress     起始地址
 * @param usNRegs       寄存器个数
 * @param eMode         读写模式
 * @return eMBErrorCode 返回错误码
 */

eMBErrorCode eMBRegHoldingCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
    uint16_t i = 0,RegIndex = usAddress - REG_HOLDING_REGISTER_START-1;
  
    if ((usAddress >= REG_HOLDING_REGISTER_START )&&(usAddress + usNRegs <= REG_HOLDING_REGISTER_START  + REG_HOLDING_REGISTER_SIZE+1))
    {
        if (MB_REG_READ == eMode)//读
        {
          for(i=0;i<usNRegs;i++)
          {
            pucRegBuffer[i*2] = (UCHAR)(Holding_Data[RegIndex+i]>>8);
            pucRegBuffer[i*2+1] = (UCHAR)Holding_Data[RegIndex+i];
          }
        }
        else//写
        {
          for(i=0;i<usNRegs;i++)
          {
            Holding_Data[RegIndex+i]=(pucRegBuffer[i*2]<<8)|(pucRegBuffer[i*2+1]);
          }
        }
    }
    else
    {
        return MB_ENOREG;
    }

    return MB_ENOERR;
}

//输入寄存器
#define REG_INPUT_REGISTER_START    0
#define REG_INPUT_REGISTER_SIZE    20

uint16_t  Input_Data[REG_INPUT_REGISTER_SIZE] =
{100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119};
/**
 * @brief: 读输入寄存器---04
 *
 * @param pucRegBuffer  缓存指针
 * @param usAddress     起始地址
 * @param usNRegs       寄存器个数
 * @return eMBErrorCode 返回错误码
 */
eMBErrorCode eMBRegInputCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
    uint16_t i = 0,RegIndex = usAddress - REG_INPUT_REGISTER_START-1;
    if ((usAddress >= REG_INPUT_REGISTER_START)&&(usAddress + usNRegs <= REG_INPUT_REGISTER_START + REG_INPUT_REGISTER_SIZE+1))
    {
        for(i=0;i<usNRegs;i++)
        {
          pucRegBuffer[i*2] = (UCHAR)(Input_Data[RegIndex+i]>>8);
          pucRegBuffer[i*2+1] = (UCHAR)Input_Data[RegIndex+i];
        }
    }
    else
    {
        return MB_ENOREG;
    }
    
    return MB_ENOERR;
}

/**********************printf重定向****************************/
//取消ARM的半主机工作模式
#pragma import(__use_no_semihosting)//标准库需要的支持函数                 
struct __FILE 
{ 
    int handle; 
}; 
FILE __stdout;       
void _sys_exit(int x) //定义_sys_exit()以避免使用半主机模式
{ 
    x = x; 
} 

int fputc(int ch, FILE *f)
{  
    return ch;
}
