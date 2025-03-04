################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lan8742/lan8742.c 

OBJS += \
./Drivers/BSP/Components/lan8742/lan8742.o 

C_DEPS += \
./Drivers/BSP/Components/lan8742/lan8742.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lan8742/%.o Drivers/BSP/Components/lan8742/%.su Drivers/BSP/Components/lan8742/%.cyclo: ../Drivers/BSP/Components/lan8742/%.c Drivers/BSP/Components/lan8742/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/Common" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/L6470" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/lan8742" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Include" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/work/R-HCU/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/functions" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/include" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/port" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"D:/work/R-HCU/R-HCU/Inc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"D:/work/R-HCU/R-HCU/LWIP/App" -I"D:/work/R-HCU/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-lan8742

clean-Drivers-2f-BSP-2f-Components-2f-lan8742:
	-$(RM) ./Drivers/BSP/Components/lan8742/lan8742.cyclo ./Drivers/BSP/Components/lan8742/lan8742.d ./Drivers/BSP/Components/lan8742/lan8742.o ./Drivers/BSP/Components/lan8742/lan8742.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-lan8742

