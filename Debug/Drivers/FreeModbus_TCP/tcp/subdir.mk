################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FreeModbus_TCP/tcp/mbtcp.c 

OBJS += \
./Drivers/FreeModbus_TCP/tcp/mbtcp.o 

C_DEPS += \
./Drivers/FreeModbus_TCP/tcp/mbtcp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FreeModbus_TCP/tcp/%.o Drivers/FreeModbus_TCP/tcp/%.su Drivers/FreeModbus_TCP/tcp/%.cyclo: ../Drivers/FreeModbus_TCP/tcp/%.c Drivers/FreeModbus_TCP/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/Common" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/L6470" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/lan8742" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/functions" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/port" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/HCU-Integrate/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/App" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FreeModbus_TCP-2f-tcp

clean-Drivers-2f-FreeModbus_TCP-2f-tcp:
	-$(RM) ./Drivers/FreeModbus_TCP/tcp/mbtcp.cyclo ./Drivers/FreeModbus_TCP/tcp/mbtcp.d ./Drivers/FreeModbus_TCP/tcp/mbtcp.o ./Drivers/FreeModbus_TCP/tcp/mbtcp.su

.PHONY: clean-Drivers-2f-FreeModbus_TCP-2f-tcp

