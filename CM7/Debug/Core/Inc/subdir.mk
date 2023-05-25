################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/duration.cpp \
../Core/Inc/time.cpp 

OBJS += \
./Core/Inc/duration.o \
./Core/Inc/time.o 

CPP_DEPS += \
./Core/Inc/duration.d \
./Core/Inc/time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.cpp Core/Inc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I/home/rosmelodic/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc -I/home/rosmelodic/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/home/rosmelodic/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/home/rosmelodic/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Include -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/duration.cyclo ./Core/Inc/duration.d ./Core/Inc/duration.o ./Core/Inc/duration.su ./Core/Inc/time.cyclo ./Core/Inc/time.d ./Core/Inc/time.o ./Core/Inc/time.su

.PHONY: clean-Core-2f-Inc

