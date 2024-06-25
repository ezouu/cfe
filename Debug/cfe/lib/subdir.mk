################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/lib/lib_arena.c \
../cfe/lib/lib_malloc.c \
../cfe/lib/lib_memfuncs.c \
../cfe/lib/lib_misc.c \
../cfe/lib/lib_qsort.c \
../cfe/lib/lib_queue.c \
../cfe/lib/lib_string.c \
../cfe/lib/lib_string2.c \
../cfe/lib/lib_try.c 

OBJS += \
./cfe/lib/lib_arena.o \
./cfe/lib/lib_malloc.o \
./cfe/lib/lib_memfuncs.o \
./cfe/lib/lib_misc.o \
./cfe/lib/lib_qsort.o \
./cfe/lib/lib_queue.o \
./cfe/lib/lib_string.o \
./cfe/lib/lib_string2.o \
./cfe/lib/lib_try.o 

C_DEPS += \
./cfe/lib/lib_arena.d \
./cfe/lib/lib_malloc.d \
./cfe/lib/lib_memfuncs.d \
./cfe/lib/lib_misc.d \
./cfe/lib/lib_qsort.d \
./cfe/lib/lib_queue.d \
./cfe/lib/lib_string.d \
./cfe/lib/lib_string2.d \
./cfe/lib/lib_try.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/lib/%.o cfe/lib/%.su cfe/lib/%.cyclo: ../cfe/lib/%.c cfe/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test2/cfe/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-lib

clean-cfe-2f-lib:
	-$(RM) ./cfe/lib/lib_arena.cyclo ./cfe/lib/lib_arena.d ./cfe/lib/lib_arena.o ./cfe/lib/lib_arena.su ./cfe/lib/lib_malloc.cyclo ./cfe/lib/lib_malloc.d ./cfe/lib/lib_malloc.o ./cfe/lib/lib_malloc.su ./cfe/lib/lib_memfuncs.cyclo ./cfe/lib/lib_memfuncs.d ./cfe/lib/lib_memfuncs.o ./cfe/lib/lib_memfuncs.su ./cfe/lib/lib_misc.cyclo ./cfe/lib/lib_misc.d ./cfe/lib/lib_misc.o ./cfe/lib/lib_misc.su ./cfe/lib/lib_qsort.cyclo ./cfe/lib/lib_qsort.d ./cfe/lib/lib_qsort.o ./cfe/lib/lib_qsort.su ./cfe/lib/lib_queue.cyclo ./cfe/lib/lib_queue.d ./cfe/lib/lib_queue.o ./cfe/lib/lib_queue.su ./cfe/lib/lib_string.cyclo ./cfe/lib/lib_string.d ./cfe/lib/lib_string.o ./cfe/lib/lib_string.su ./cfe/lib/lib_string2.cyclo ./cfe/lib/lib_string2.d ./cfe/lib/lib_string2.o ./cfe/lib/lib_string2.su ./cfe/lib/lib_try.cyclo ./cfe/lib/lib_try.d ./cfe/lib/lib_try.o ./cfe/lib/lib_try.su

.PHONY: clean-cfe-2f-lib

