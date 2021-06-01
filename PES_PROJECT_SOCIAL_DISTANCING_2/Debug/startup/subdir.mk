################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

OBJS += \
./startup/startup_mkl25z4.o 

C_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\board" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\source" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\drivers" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\CMSIS" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\utilities" -I"C:\Users\Pallavi\Desktop\Gopi Docs\PES_PROJECT_SOCIAL_DISTANCING_2\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


