################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI-ECV.c \
../Timer0.c \
../gpio.c \
../keypad.c \
../lcd.c \
../uart.c 

OBJS += \
./HMI-ECV.o \
./Timer0.o \
./gpio.o \
./keypad.o \
./lcd.o \
./uart.o 

C_DEPS += \
./HMI-ECV.d \
./Timer0.d \
./gpio.d \
./keypad.d \
./lcd.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


