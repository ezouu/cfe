################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/ui/ui_cmddisp.c \
../cfe/ui/ui_command.c \
../cfe/ui/ui_devcmds.c \
../cfe/ui/ui_envcmds.c \
../cfe/ui/ui_examcmds.c \
../cfe/ui/ui_loadcmds.c \
../cfe/ui/ui_memcmds.c \
../cfe/ui/ui_misccmds.c \
../cfe/ui/url.c 

OBJS += \
./cfe/ui/ui_cmddisp.o \
./cfe/ui/ui_command.o \
./cfe/ui/ui_devcmds.o \
./cfe/ui/ui_envcmds.o \
./cfe/ui/ui_examcmds.o \
./cfe/ui/ui_loadcmds.o \
./cfe/ui/ui_memcmds.o \
./cfe/ui/ui_misccmds.o \
./cfe/ui/url.o 

C_DEPS += \
./cfe/ui/ui_cmddisp.d \
./cfe/ui/ui_command.d \
./cfe/ui/ui_devcmds.d \
./cfe/ui/ui_envcmds.d \
./cfe/ui/ui_examcmds.d \
./cfe/ui/ui_loadcmds.d \
./cfe/ui/ui_memcmds.d \
./cfe/ui/ui_misccmds.d \
./cfe/ui/url.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/ui/%.o cfe/ui/%.su cfe/ui/%.cyclo: ../cfe/ui/%.c cfe/ui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-ui

clean-cfe-2f-ui:
	-$(RM) ./cfe/ui/ui_cmddisp.cyclo ./cfe/ui/ui_cmddisp.d ./cfe/ui/ui_cmddisp.o ./cfe/ui/ui_cmddisp.su ./cfe/ui/ui_command.cyclo ./cfe/ui/ui_command.d ./cfe/ui/ui_command.o ./cfe/ui/ui_command.su ./cfe/ui/ui_devcmds.cyclo ./cfe/ui/ui_devcmds.d ./cfe/ui/ui_devcmds.o ./cfe/ui/ui_devcmds.su ./cfe/ui/ui_envcmds.cyclo ./cfe/ui/ui_envcmds.d ./cfe/ui/ui_envcmds.o ./cfe/ui/ui_envcmds.su ./cfe/ui/ui_examcmds.cyclo ./cfe/ui/ui_examcmds.d ./cfe/ui/ui_examcmds.o ./cfe/ui/ui_examcmds.su ./cfe/ui/ui_loadcmds.cyclo ./cfe/ui/ui_loadcmds.d ./cfe/ui/ui_loadcmds.o ./cfe/ui/ui_loadcmds.su ./cfe/ui/ui_memcmds.cyclo ./cfe/ui/ui_memcmds.d ./cfe/ui/ui_memcmds.o ./cfe/ui/ui_memcmds.su ./cfe/ui/ui_misccmds.cyclo ./cfe/ui/ui_misccmds.d ./cfe/ui/ui_misccmds.o ./cfe/ui/ui_misccmds.su ./cfe/ui/url.cyclo ./cfe/ui/url.d ./cfe/ui/url.o ./cfe/ui/url.su

.PHONY: clean-cfe-2f-ui

