################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/andrea/Progetti/STM32MidiSynth/Tool/SineTable/SineTable.c 

OBJS += \
./SineTable/SineTable.o 

C_DEPS += \
./SineTable/SineTable.d 


# Each subdirectory must supply rules for building sources it contributes
SineTable/SineTable.o: /home/andrea/Progetti/STM32MidiSynth/Tool/SineTable/SineTable.c SineTable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../../Core/Inc -I/home/andrea/Progetti/STM32MidiSynth/Tool/SineTable -I/home/andrea/Progetti/STM32MidiSynth/Firmware/Library/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SineTable

clean-SineTable:
	-$(RM) ./SineTable/SineTable.cyclo ./SineTable/SineTable.d ./SineTable/SineTable.o ./SineTable/SineTable.su

.PHONY: clean-SineTable

