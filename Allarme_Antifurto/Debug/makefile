################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Allarme_Antifurto.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Allarme_Antifurto.list \

OBJCOPY_BIN += \
Allarme_Antifurto.bin \


# All Target
all: Allarme_Antifurto.elf secondary-outputs

# Tool invocations
Allarme_Antifurto.elf: $(OBJS) $(USER_OBJS) C:\Temp\SEI\CubeIDE_proj\Allarme_Antifurto\STM32F401RETX_FLASH.ld
	arm-none-eabi-gcc -o "Allarme_Antifurto.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Temp\SEI\CubeIDE_proj\Allarme_Antifurto\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Allarme_Antifurto.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Allarme_Antifurto.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Allarme_Antifurto.list"
	@echo 'Finished building: $@'
	@echo ' '

Allarme_Antifurto.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Allarme_Antifurto.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
