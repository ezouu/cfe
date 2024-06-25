################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../cfe/arch/arm/init_arm.s 

C_SRCS += \
../cfe/arch/arm/lib_printf.c 

OBJS += \
./cfe/arch/arm/init_arm.o \
./cfe/arch/arm/lib_printf.o 

S_DEPS += \
./cfe/arch/arm/init_arm.d 

C_DEPS += \
./cfe/arch/arm/lib_printf.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/arch/arm/%.o: ../cfe/arch/arm/%.s cfe/arch/arm/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
cfe/arch/arm/%.o cfe/arch/arm/%.su cfe/arch/arm/%.cyclo: ../cfe/arch/arm/%.c cfe/arch/arm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-arch-2f-arm

clean-cfe-2f-arch-2f-arm:
	-$(RM) ./cfe/arch/arm/init_arm.d ./cfe/arch/arm/init_arm.o ./cfe/arch/arm/lib_printf.cyclo ./cfe/arch/arm/lib_printf.d ./cfe/arch/arm/lib_printf.o ./cfe/arch/arm/lib_printf.su

.PHONY: clean-cfe-2f-arch-2f-arm

