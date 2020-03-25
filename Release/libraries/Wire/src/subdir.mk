################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\libraries\Wire\src\Wire.cpp 

LINK_OBJ += \
.\libraries\Wire\src\Wire.cpp.o 

CPP_DEPS += \
.\libraries\Wire\src\Wire.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\Wire.cpp.o: C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\libraries\Wire\src\Wire.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\mega" -I"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


