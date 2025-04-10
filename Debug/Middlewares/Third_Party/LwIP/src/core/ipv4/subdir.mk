################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/ipv4/%.o Middlewares/Third_Party/LwIP/src/core/ipv4/%.su Middlewares/Third_Party/LwIP/src/core/ipv4/%.cyclo: ../Middlewares/Third_Party/LwIP/src/core/ipv4/%.c Middlewares/Third_Party/LwIP/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DMOTOR_BSP -c -I../Inc -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHMxx" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/Common" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/L6470" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/powerSTEP01" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/Components/lan8742" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/BSP/X-NUCLEO-IHM02A1" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/functions" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/port" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Drivers/FreeModbus_TCP/tcp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Inc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/HCU-Integrate/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/App" -I"C:/Users/Eric/STM32CubeIDE/workspace_1.14.1/R-HCU/LWIP/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4

