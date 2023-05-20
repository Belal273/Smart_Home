################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIMER1/subdir.mk
-include MCAL/TIMER0/subdir.mk
-include MCAL/GLOBAL_INT/subdir.mk
-include MCAL/EXT_INT/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/TEMP_SENSOR/subdir.mk
-include HAL/SWITCH/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LDR/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/EEPROM/subdir.mk
-include HAL/DC_MOTOR/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Layered.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: Layered.elf secondary-outputs

# Tool invocations
Layered.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Layered.map -mmcu=atmega32 -o "Layered.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Layered.lss: Layered.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Layered.elf  >"Layered.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Layered.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Layered.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Layered.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
