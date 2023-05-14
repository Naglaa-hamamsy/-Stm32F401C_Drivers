################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GPIO.c \
../src/Init.c \
../src/LED.c \
../src/LED_Cfg.c \
../src/NVIC.c \
../src/RCC2.c \
../src/Systick.c \
../src/UART.c \
../src/UART_Cfg.c \
../src/main.c 

OBJS += \
./src/GPIO.o \
./src/Init.o \
./src/LED.o \
./src/LED_Cfg.o \
./src/NVIC.o \
./src/RCC2.o \
./src/Systick.o \
./src/UART.o \
./src/UART_Cfg.o \
./src/main.o 

C_DEPS += \
./src/GPIO.d \
./src/Init.d \
./src/LED.d \
./src/LED_Cfg.d \
./src/NVIC.d \
./src/RCC2.d \
./src/Systick.d \
./src/UART.d \
./src/UART_Cfg.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


