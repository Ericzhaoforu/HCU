#ifndef __User_modbbus_TCP_H__
#define	__User_modbbus_TCP_H__

#include "main.h"

#define MODBUS_TCP_PORT 502

extern void ModbusTCPInit(void);
extern void ModbusTCPMain(void);

#endif
