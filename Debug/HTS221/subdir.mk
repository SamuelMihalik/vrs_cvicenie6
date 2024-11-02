################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HTS221/HTS221.c 

OBJS += \
./HTS221/HTS221.o 

C_DEPS += \
./HTS221/HTS221.d 


# Each subdirectory must supply rules for building sources it contributes
HTS221/%.o HTS221/%.su HTS221/%.cyclo: ../HTS221/%.c HTS221/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F303x8 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/mihal/STM32CubeIDE/workspace_1.16.1/vrs_cvicenie_6/HTS221" -I"C:/Users/mihal/STM32CubeIDE/workspace_1.16.1/vrs_cvicenie_6/LPS25HB" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HTS221

clean-HTS221:
	-$(RM) ./HTS221/HTS221.cyclo ./HTS221/HTS221.d ./HTS221/HTS221.o ./HTS221/HTS221.su

.PHONY: clean-HTS221

