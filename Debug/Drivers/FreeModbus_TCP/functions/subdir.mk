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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/Common" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/L6470" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/lan8742" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/functions" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/port" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/HCU-Integrate/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/App" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FreeModbus_TCP-2f-functions

clean-Drivers-2f-FreeModbus_TCP-2f-functions:
	-$(RM) ./Drivers/FreeModbus_TCP/functions/mbfunccoils.cyclo ./Drivers/FreeModbus_TCP/functions/mbfunccoils.d ./Drivers/FreeModbus_TCP/functions/mbfunccoils.o ./Drivers/FreeModbus_TCP/functions/mbfunccoils.su ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.d ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.o ./Drivers/FreeModbus_TCP/functions/mbfuncdiag.su ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.d ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.o ./Drivers/FreeModbus_TCP/functions/mbfuncdisc.su ./Drivers/FreeModbus_TCP/functions/mbfuncholding.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncholding.d ./Drivers/FreeModbus_TCP/functions/mbfuncholding.o ./Drivers/FreeModbus_TCP/functions/mbfuncholding.su ./Drivers/FreeModbus_TCP/functions/mbfuncinput.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncinput.d ./Drivers/FreeModbus_TCP/functions/mbfuncinput.o ./Drivers/FreeModbus_TCP/functions/mbfuncinput.su ./Drivers/FreeModbus_TCP/functions/mbfuncother.cyclo ./Drivers/FreeModbus_TCP/functions/mbfuncother.d ./Drivers/FreeModbus_TCP/functions/mbfuncother.o ./Drivers/FreeModbus_TCP/functions/mbfuncother.su ./Drivers/FreeModbus_TCP/functions/mbutils.cyclo ./Drivers/FreeModbus_TCP/functions/mbutils.d ./Drivers/FreeModbus_TCP/functions/mbutils.o ./Drivers/FreeModbus_TCP/functions/mbutils.su

.PHONY: clean-Drivers-2f-FreeModbus_TCP-2f-functions

