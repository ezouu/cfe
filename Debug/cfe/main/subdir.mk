################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/main/cfe_attach.c \
../cfe/main/cfe_autoboot.c \
../cfe/main/cfe_background.c \
../cfe/main/cfe_boot.c \
../cfe/main/cfe_console.c \
../cfe/main/cfe_devfuncs.c \
../cfe/main/cfe_error.c \
../cfe/main/cfe_fatfs.c \
../cfe/main/cfe_filesys.c \
../cfe/main/cfe_httpfs.c \
../cfe/main/cfe_iocb_dispatch.c \
../cfe/main/cfe_loader.c \
../cfe/main/cfe_main.c \
../cfe/main/cfe_mem.c \
../cfe/main/cfe_savedata.c \
../cfe/main/cfe_spi.c \
../cfe/main/cfe_timer.c \
../cfe/main/env_subr.c 

OBJS += \
./cfe/main/cfe_attach.o \
./cfe/main/cfe_autoboot.o \
./cfe/main/cfe_background.o \
./cfe/main/cfe_boot.o \
./cfe/main/cfe_console.o \
./cfe/main/cfe_devfuncs.o \
./cfe/main/cfe_error.o \
./cfe/main/cfe_fatfs.o \
./cfe/main/cfe_filesys.o \
./cfe/main/cfe_httpfs.o \
./cfe/main/cfe_iocb_dispatch.o \
./cfe/main/cfe_loader.o \
./cfe/main/cfe_main.o \
./cfe/main/cfe_mem.o \
./cfe/main/cfe_savedata.o \
./cfe/main/cfe_spi.o \
./cfe/main/cfe_timer.o \
./cfe/main/env_subr.o 

C_DEPS += \
./cfe/main/cfe_attach.d \
./cfe/main/cfe_autoboot.d \
./cfe/main/cfe_background.d \
./cfe/main/cfe_boot.d \
./cfe/main/cfe_console.d \
./cfe/main/cfe_devfuncs.d \
./cfe/main/cfe_error.d \
./cfe/main/cfe_fatfs.d \
./cfe/main/cfe_filesys.d \
./cfe/main/cfe_httpfs.d \
./cfe/main/cfe_iocb_dispatch.d \
./cfe/main/cfe_loader.d \
./cfe/main/cfe_main.d \
./cfe/main/cfe_mem.d \
./cfe/main/cfe_savedata.d \
./cfe/main/cfe_spi.d \
./cfe/main/cfe_timer.d \
./cfe/main/env_subr.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/main/%.o cfe/main/%.su cfe/main/%.cyclo: ../cfe/main/%.c cfe/main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-main

clean-cfe-2f-main:
	-$(RM) ./cfe/main/cfe_attach.cyclo ./cfe/main/cfe_attach.d ./cfe/main/cfe_attach.o ./cfe/main/cfe_attach.su ./cfe/main/cfe_autoboot.cyclo ./cfe/main/cfe_autoboot.d ./cfe/main/cfe_autoboot.o ./cfe/main/cfe_autoboot.su ./cfe/main/cfe_background.cyclo ./cfe/main/cfe_background.d ./cfe/main/cfe_background.o ./cfe/main/cfe_background.su ./cfe/main/cfe_boot.cyclo ./cfe/main/cfe_boot.d ./cfe/main/cfe_boot.o ./cfe/main/cfe_boot.su ./cfe/main/cfe_console.cyclo ./cfe/main/cfe_console.d ./cfe/main/cfe_console.o ./cfe/main/cfe_console.su ./cfe/main/cfe_devfuncs.cyclo ./cfe/main/cfe_devfuncs.d ./cfe/main/cfe_devfuncs.o ./cfe/main/cfe_devfuncs.su ./cfe/main/cfe_error.cyclo ./cfe/main/cfe_error.d ./cfe/main/cfe_error.o ./cfe/main/cfe_error.su ./cfe/main/cfe_fatfs.cyclo ./cfe/main/cfe_fatfs.d ./cfe/main/cfe_fatfs.o ./cfe/main/cfe_fatfs.su ./cfe/main/cfe_filesys.cyclo ./cfe/main/cfe_filesys.d ./cfe/main/cfe_filesys.o ./cfe/main/cfe_filesys.su ./cfe/main/cfe_httpfs.cyclo ./cfe/main/cfe_httpfs.d ./cfe/main/cfe_httpfs.o ./cfe/main/cfe_httpfs.su ./cfe/main/cfe_iocb_dispatch.cyclo ./cfe/main/cfe_iocb_dispatch.d ./cfe/main/cfe_iocb_dispatch.o ./cfe/main/cfe_iocb_dispatch.su ./cfe/main/cfe_loader.cyclo ./cfe/main/cfe_loader.d ./cfe/main/cfe_loader.o ./cfe/main/cfe_loader.su ./cfe/main/cfe_main.cyclo ./cfe/main/cfe_main.d ./cfe/main/cfe_main.o ./cfe/main/cfe_main.su ./cfe/main/cfe_mem.cyclo ./cfe/main/cfe_mem.d ./cfe/main/cfe_mem.o ./cfe/main/cfe_mem.su ./cfe/main/cfe_savedata.cyclo ./cfe/main/cfe_savedata.d ./cfe/main/cfe_savedata.o ./cfe/main/cfe_savedata.su ./cfe/main/cfe_spi.cyclo ./cfe/main/cfe_spi.d ./cfe/main/cfe_spi.o ./cfe/main/cfe_spi.su ./cfe/main/cfe_timer.cyclo ./cfe/main/cfe_timer.d ./cfe/main/cfe_timer.o ./cfe/main/cfe_timer.su ./cfe/main/env_subr.cyclo ./cfe/main/env_subr.d ./cfe/main/env_subr.o ./cfe/main/env_subr.su

.PHONY: clean-cfe-2f-main

