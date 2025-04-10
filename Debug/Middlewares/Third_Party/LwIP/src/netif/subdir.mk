################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/netif/bridgeif.c \
../Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.c \
../Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
../Middlewares/Third_Party/LwIP/src/netif/lowpan6.c \
../Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.c \
../Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.c \
../Middlewares/Third_Party/LwIP/src/netif/slipif.c \
../Middlewares/Third_Party/LwIP/src/netif/zepif.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/netif/bridgeif.o \
./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.o \
./Middlewares/Third_Party/LwIP/src/netif/ethernet.o \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6.o \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.o \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.o \
./Middlewares/Third_Party/LwIP/src/netif/slipif.o \
./Middlewares/Third_Party/LwIP/src/netif/zepif.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/netif/bridgeif.d \
./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.d \
./Middlewares/Third_Party/LwIP/src/netif/ethernet.d \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6.d \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.d \
./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.d \
./Middlewares/Third_Party/LwIP/src/netif/slipif.d \
./Middlewares/Third_Party/LwIP/src/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/netif/%.o Middlewares/Third_Party/LwIP/src/netif/%.su Middlewares/Third_Party/LwIP/src/netif/%.cyclo: ../Middlewares/Third_Party/LwIP/src/netif/%.c Middlewares/Third_Party/LwIP/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/Common" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/L6470" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/lan8742" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/functions" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/port" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/HCU-Integrate/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/App" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.d ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.o ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.su ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.cyclo ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.d ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.o ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.su ./Middlewares/Third_Party/LwIP/src/netif/ethernet.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ethernet.d ./Middlewares/Third_Party/LwIP/src/netif/ethernet.o ./Middlewares/Third_Party/LwIP/src/netif/ethernet.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.su ./Middlewares/Third_Party/LwIP/src/netif/slipif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/slipif.d ./Middlewares/Third_Party/LwIP/src/netif/slipif.o ./Middlewares/Third_Party/LwIP/src/netif/slipif.su ./Middlewares/Third_Party/LwIP/src/netif/zepif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/zepif.d ./Middlewares/Third_Party/LwIP/src/netif/zepif.o ./Middlewares/Third_Party/LwIP/src/netif/zepif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif

