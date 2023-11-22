################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/Startup/startup_stm32f407vgtx.s 

S_DEPS += \
./Drivers/Startup/startup_stm32f407vgtx.d 

OBJS += \
./Drivers/Startup/startup_stm32f407vgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Startup/%.o: ../Drivers/Startup/%.s Drivers/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

