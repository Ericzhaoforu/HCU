################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/clock_f4.c \
../Src/i2c.c \
../Src/main.c \
../Src/params.c \
../Src/ssd1306.c \
../Src/ssd1306_fonts.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/clock_f4.o \
./Src/i2c.o \
./Src/main.o \
./Src/params.o \
./Src/ssd1306.o \
./Src/ssd1306_fonts.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/clock_f4.d \
./Src/i2c.d \
./Src/main.d \
./Src/params.d \
./Src/ssd1306.d \
./Src/ssd1306_fonts.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/Common" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/L6470" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/lan8742" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/functions" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/port" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/HCU-Integrate/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/App" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/clock_f4.cyclo ./Src/clock_f4.d ./Src/clock_f4.o ./Src/clock_f4.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/params.cyclo ./Src/params.d ./Src/params.o ./Src/params.su ./Src/ssd1306.cyclo ./Src/ssd1306.d ./Src/ssd1306.o ./Src/ssd1306.su ./Src/ssd1306_fonts.cyclo ./Src/ssd1306_fonts.d ./Src/ssd1306_fonts.o ./Src/ssd1306_fonts.su ./Src/stm32f4xx_hal_msp.cyclo ./Src/stm32f4xx_hal_msp.d ./Src/stm32f4xx_hal_msp.o ./Src/stm32f4xx_hal_msp.su ./Src/stm32f4xx_it.cyclo ./Src/stm32f4xx_it.d ./Src/stm32f4xx_it.o ./Src/stm32f4xx_it.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/tim.cyclo ./Src/tim.d ./Src/tim.o ./Src/tim.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

