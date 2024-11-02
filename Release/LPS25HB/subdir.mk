################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LPS25HB/LPS25HB.c 

OBJS += \
./LPS25HB/LPS25HB.o 

C_DEPS += \
./LPS25HB/LPS25HB.d 


# Each subdirectory must supply rules for building sources it contributes
LPS25HB/%.o LPS25HB/%.su LPS25HB/%.cyclo: ../LPS25HB/%.c LPS25HB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F303x8 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/mihal/STM32CubeIDE/workspace_1.16.1/vrs_cvicenie_6/HTS221" -I"C:/Users/mihal/STM32CubeIDE/workspace_1.16.1/vrs_cvicenie_6/LPS25HB" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LPS25HB

clean-LPS25HB:
	-$(RM) ./LPS25HB/LPS25HB.cyclo ./LPS25HB/LPS25HB.d ./LPS25HB/LPS25HB.o ./LPS25HB/LPS25HB.su

.PHONY: clean-LPS25HB

