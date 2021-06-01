################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PES_PROJECT_SOCIAL_DISTANCING.c \
../source/PWM_buzzer.c \
../source/TPM_sensors.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/systick.c \
../source/testing.c 

OBJS += \
./source/PES_PROJECT_SOCIAL_DISTANCING.o \
./source/PWM_buzzer.o \
./source/TPM_sensors.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/systick.o \
./source/testing.o 

C_DEPS += \
./source/PES_PROJECT_SOCIAL_DISTANCING.d \
./source/PWM_buzzer.d \
./source/TPM_sensors.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/systick.d \
./source/testing.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\board" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\source" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\drivers" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\CMSIS" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\utilities" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


