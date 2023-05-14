################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drv/GPIO.c \
../drv/LED.c \
../drv/LED_Cfg.c \
../drv/RCC2.c \
../drv/Systick.c 

OBJS += \
./drv/GPIO.o \
./drv/LED.o \
./drv/LED_Cfg.o \
./drv/RCC2.o \
./drv/Systick.o 

C_DEPS += \
./drv/GPIO.d \
./drv/LED.d \
./drv/LED_Cfg.d \
./drv/RCC2.d \
./drv/Systick.d 


# Each subdirectory must supply rules for building sources it contributes
drv/%.o: ../drv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"E:\ITI\Tourky\ARM_WorkSpace\SYSTICK\drv\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


