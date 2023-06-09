################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c 

CPP_SRCS += \
../Core/Src/Encoder.cpp \
../Core/Src/MotorPI.cpp \
../Core/Src/main.cpp \
../Core/Src/mainpp.cpp 

C_DEPS += \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d 

OBJS += \
./Core/Src/Encoder.o \
./Core/Src/MotorPI.o \
./Core/Src/main.o \
./Core/Src/mainpp.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o 

CPP_DEPS += \
./Core/Src/Encoder.d \
./Core/Src/MotorPI.d \
./Core/Src/main.d \
./Core/Src/mainpp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I/home/josue/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Encoder.cyclo ./Core/Src/Encoder.d ./Core/Src/Encoder.o ./Core/Src/Encoder.su ./Core/Src/MotorPI.cyclo ./Core/Src/MotorPI.d ./Core/Src/MotorPI.o ./Core/Src/MotorPI.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mainpp.cyclo ./Core/Src/mainpp.d ./Core/Src/mainpp.o ./Core/Src/mainpp.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su

.PHONY: clean-Core-2f-Src

