################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/andrea/Progetti/STM32MidiSynth/Firmware/Library/Src/Engine.c 

OBJS += \
./Library/Src/Engine.o 

C_DEPS += \
./Library/Src/Engine.d 


# Each subdirectory must supply rules for building sources it contributes
Library/Src/Engine.o: /home/andrea/Progetti/STM32MidiSynth/Firmware/Library/Src/Engine.c Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../../Core/Inc -I/home/andrea/Progetti/STM32MidiSynth/Firmware/Library/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-Src

clean-Library-2f-Src:
	-$(RM) ./Library/Src/Engine.cyclo ./Library/Src/Engine.d ./Library/Src/Engine.o ./Library/Src/Engine.su

.PHONY: clean-Library-2f-Src

