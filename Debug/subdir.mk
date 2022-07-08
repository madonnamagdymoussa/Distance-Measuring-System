################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcd.c \
../main.c \
../mdio.c \
../timer.c \
../timer_config.c \
../ultrasonic.c 

OBJS += \
./lcd.o \
./main.o \
./mdio.o \
./timer.o \
./timer_config.o \
./ultrasonic.o 

C_DEPS += \
./lcd.d \
./main.d \
./mdio.d \
./timer.d \
./timer_config.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


