################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./clear_program_flash.obj" \
"./constants.obj" \
"./cyclone_global_variables_defs.obj" \
"./device_id.obj" \
"./flash.obj" \
"./init_adc12.obj" \
"./init_bat_charge_loop.obj" \
"./init_bus_backup_loop.obj" \
"./init_dpwm.obj" \
"./init_miscellaneous.obj" \
"./init_protection.obj" \
"./interrupts.obj" \
"./load.obj" \
"./main.obj" \
"./pmbus.obj" \
"./pmbus_coefficients.obj" \
"./pmbus_handler.obj" \
"./pmbus_manuf_info_commands.obj" \
"./pmbus_manuf_specific_commands.obj" \
"./pmbus_tools.obj" \
"./software_interrupt_wrapper.obj" \
"./standard_interrupt.obj" \
"./zero_out_integrity_word.obj" \
$(GEN_CMDS__FLAG) \
-l"C:/Users/a0270670/Bitbucket/PMP21529/PMP21529 package/Linker Files/cyclone.cmd" \
-l"C:/Users/a0270670/Bitbucket/PMP21529/PMP21529 package/Linker Files/cyclone_headers.cmd" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
PMP21529.out \

EXE_OUTPUTS__QUOTED += \
"PMP21529.out" \

BIN_OUTPUTS += \
PMP21529.hex \

BIN_OUTPUTS__QUOTED += \
"PMP21529.hex" \


# All Target
all: PMP21529.out

# Tool invocations
PMP21529.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv4 --code_state=16 --abi=ti_arm9_abi -O2 -g --preproc_with_compile --preproc_with_comment --diag_warning=225 --display_error_number -z -m"C:/Users/a0270670/Bitbucket/PMP21529/PMP21529 package/UCD3138_PMP21529/PMP21529.map" --heap_size=10 --stack_size=200 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --reread_libs --display_error_number --warn_sections --xml_link_info="PMP21529_linkInfo.xml" --rom_model -o "PMP21529.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

PMP21529.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armhex"  -o "PMP21529.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "clear_program_flash.obj" "constants.obj" "cyclone_global_variables_defs.obj" "device_id.obj" "flash.obj" "init_adc12.obj" "init_bat_charge_loop.obj" "init_bus_backup_loop.obj" "init_dpwm.obj" "init_miscellaneous.obj" "init_protection.obj" "interrupts.obj" "load.obj" "main.obj" "pmbus.obj" "pmbus_coefficients.obj" "pmbus_handler.obj" "pmbus_manuf_info_commands.obj" "pmbus_manuf_specific_commands.obj" "pmbus_tools.obj" "software_interrupt_wrapper.obj" "standard_interrupt.obj" "zero_out_integrity_word.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Tektronix Extended format'
	-("C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armhex.exe" -x "PMP21529.out" -o "PMP21529.x0" -memwidth 8) & (perl ../../build_scripts/checkmem_CCS5.pl cyclone ../"PMP21529.map" ) & (perl ../../build_scripts/build_CCS5.pl "PMP21529")
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

