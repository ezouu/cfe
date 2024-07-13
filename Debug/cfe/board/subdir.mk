################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/board/stm32_board.c 

OBJS += \
./cfe/board/stm32_board.o 

C_DEPS += \
./cfe/board/stm32_board.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/board/%.o cfe/board/%.su cfe/board/%.cyclo: ../cfe/board/%.c cfe/board/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-board

clean-cfe-2f-board:
	-$(RM) ./cfe/board/stm32_board.cyclo ./cfe/board/stm32_board.d ./cfe/board/stm32_board.o ./cfe/board/stm32_board.su

.PHONY: clean-cfe-2f-board

