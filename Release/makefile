################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\Wire\src\utility\subdir.mk
-include libraries\Wire\src\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:\sloeber\ws\VUB_Buttons\Release\arduino.ar \

ELF += \
VUB_Buttons.elf \

HEX += \
VUB_Buttons.hex \


# All Target
all: VUB_Buttons

# Tool invocations
VUB_Buttons: $(HEX)
	@echo 'Building target: $@'
	@echo 'Druk de grote af:'
	"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-size" -A "C:/sloeber/ws/VUB_Buttons/Release/VUB_Buttons.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:\sloeber\ws\VUB_Buttons\Release\arduino.ar: $(AR_OBJ)
	@echo 'Start de archief bouwer'
	"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-gcc-ar" rcs     C:/sloeber/ws/VUB_Buttons/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

VUB_Buttons.elf: $(LINK_OBJ) $(AR)
	@echo 'Start de samenvoeger'
	"C:\sloeber\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-gcc" -Wall -Wextra -Os -Wl,--gc-sections,--relax -mmcu=atmega2560  -o "C:/sloeber/ws/VUB_Buttons/Release/VUB_Buttons.elf"   $(LINK_OBJ)   C:/sloeber/ws/VUB_Buttons/Release/arduino.ar  "-LC:/sloeber/ws/VUB_Buttons/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

VUB_Buttons.hex: $(ELF)
	@echo 'Voer alle objcopy opdrachten uit'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ..\makefile.targets
