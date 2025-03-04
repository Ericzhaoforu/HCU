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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/Common" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/L6470" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/Components/lan8742" -I"D:/work/R-HCU/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Include" -I"D:/work/R-HCU/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/work/R-HCU/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/functions" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/include" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/port" -I"D:/work/R-HCU/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"D:/work/R-HCU/R-HCU/Inc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"D:/work/R-HCU/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"D:/work/R-HCU/R-HCU/LWIP/App" -I"D:/work/R-HCU/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.d ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.o ./Middlewares/Third_Party/LwIP/src/netif/bridgeif.su ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.cyclo ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.d ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.o ./Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.su ./Middlewares/Third_Party/LwIP/src/netif/ethernet.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ethernet.d ./Middlewares/Third_Party/LwIP/src/netif/ethernet.o ./Middlewares/Third_Party/LwIP/src/netif/ethernet.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.su ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.cyclo ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.d ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.o ./Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.su ./Middlewares/Third_Party/LwIP/src/netif/slipif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/slipif.d ./Middlewares/Third_Party/LwIP/src/netif/slipif.o ./Middlewares/Third_Party/LwIP/src/netif/slipif.su ./Middlewares/Third_Party/LwIP/src/netif/zepif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/zepif.d ./Middlewares/Third_Party/LwIP/src/netif/zepif.o ./Middlewares/Third_Party/LwIP/src/netif/zepif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif

