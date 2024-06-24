################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/api/cfe_api.c 

OBJS += \
./cfe/api/cfe_api.o 

C_DEPS += \
./cfe/api/cfe_api.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/api/%.o cfe/api/%.su cfe/api/%.cyclo: ../cfe/api/%.c cfe/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/pzou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-api

clean-cfe-2f-api:
	-$(RM) ./cfe/api/cfe_api.cyclo ./cfe/api/cfe_api.d ./cfe/api/cfe_api.o ./cfe/api/cfe_api.su

.PHONY: clean-cfe-2f-api

