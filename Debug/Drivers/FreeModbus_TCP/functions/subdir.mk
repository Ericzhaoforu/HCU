################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FreeModbus_TCP/functions/mbfunccoils.c \
../Drivers/FreeModbus_TCP/functions/mbfuncdiag.c \
../Drivers/FreeModbus_TCP/functions/mbfuncdisc.c \
../Drivers/FreeModbus_TCP/functions/mbfuncholding.c \
../Drivers/FreeModbus_TCP/functions/mbfuncinput.c \
../Drivers/FreeModbus_TCP/functions/mbfuncother.c \
../Drivers/FreeModbus_TCP/functions/mbutils.c 

OBJS += \
./Drivers/FreeModbus_TCP/functions/mbfunccoils.o \
./Drivers/FreeModbus_TCP/functions/mbfuncdiag.o \
./Drivers/FreeModbus_TCP/functions/mbfuncdisc.o \
./Drivers/FreeModbus_TCP/functions/mbfuncholding.o \
./Drivers/FreeModbus_TCP/functions/mbfuncinput.o \
./Drivers/FreeModbus_TCP/functions/mbfuncother.o \
./Drivers/FreeModbus_TCP/functions/mbutils.o 

C_DEPS += \
./Drivers/FreeModbus_TCP/functions/mbfunccoils.d \
./Drivers/FreeModbus_TCP/functions/mbfuncdiag.d \
./Drivers/FreeModbus_TCP/functions/mbfuncdisc.d \
./Drivers/FreeModbus_TCP/functions/mbfuncholding.d \
./Drivers/FreeModbus_TCP/functions/mbfuncinput.d \
./Drivers/FreeModbus_TCP/functions/mbfuncother.d \
./Drivers/FreeModbus_TCP/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FreeModbus_TCP/functions/%.o Drivers/FreeModbus_TCP/functions/%.su Drivers/FreeModbus_TCP/functions/%.cyclo: ../Drivers/FreeModbus_TCP/functions/%.c Drivers/FreeModbus_TCP/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/Common" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/L6470" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/lan8742" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Include" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/work/R-HCU/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/functions" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/include" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/port" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"D:/work/R-HCU/R-HCU/Inc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"D:/work/R-HCU/R-HCU/LWIP/App" -I"D:/work/R-HCU/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FreeModbus_TCP-2f-functions

clean-Drivers-2f-FreeModbus_TCP-2f-functions:
	-$(RM) ./Drivers/FreeModbus_TCP/functions/mbfunccoils.cyclo ./Drivers/FreeModbus_TCP/functions/mbfunccoils.d ./Drivers/FreeModbus_TCP/functions/mbfunccoils.o ./Drivers/FreeModbus_TCP/functions/mbfunccoils.su ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.d ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.o ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.su ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.d ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.o ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.su ./Drivers/FreeModbus_TCP/functions/mbfuncholding.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncholding.d ./Drivers/FreeModbus_TCP/functions/mbfuncholding.o ./Drivers/FreeModbus_TCP/functions/mbfuncholding.su ./Drivers/FreeModbus_TCP/functions/mbfuncinput.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncinput.d ./Drivers/FreeModbus_TCP/functions/mbfuncinput.o ./Drivers/FreeModbus_TCP/functions/mbfuncinput.su ./Drivers/FreeModbus_TCP/functions/mbfuncother.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncother.d ./Drivers/FreeModbus_TCP/functions/mbfuncother.o ./Drivers/FreeModbus_TCP/functions/mbfuncother.su ./Drivers/FreeModbus_TCP/functions/mbutils.cyclo ./Drivers/FreeModbus_TCP/functions/mbutils.d ./Drivers/FreeModbus_TCP/functions/mbutils.o ./Drivers/FreeModbus_TCP/functions/mbutils.su

.PHONY: clean-Drivers-2f-FreeModbus_TCP-2f-functions

