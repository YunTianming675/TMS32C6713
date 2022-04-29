################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug/vecs.obj" \
"f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug/DEC6713_EDMA.obj" \
"f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug/DEC6713.obj" \
"D:/Projects/CCS5/DEC6713_EDMA/edma.cmd" \
-l"csl6713.lib" \
-l"rts6700.lib" \

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
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
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

# All Target
all: D:/Projects/CCS5/DEC6713_EDMA/DEC6713_EDMA/../Debug/DEC6713_EDMA.out

# Tool invocations
D:/Projects/CCS5/DEC6713_EDMA/DEC6713_EDMA/../Debug/DEC6713_EDMA.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6710 --abi=coffabi -g --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --obj_directory="f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug" -z --stack_size=1000 -m"D:/Projects/CCS5/DEC6713_EDMA/Debug/DEC6713_EDMA.map" --heap_size=1000 -i"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/lib" -i"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" -i"D:/Projects/CCS5/DEC6713_EDMA/DEC6713_EDMA" -i"D:/Projects/CCS5/DEC6713_EDMA" -i"/lib" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="DEC6713_EDMA_linkInfo.xml" --rom_model -o "D:/Projects/CCS5/DEC6713_EDMA/DEC6713_EDMA/../Debug/DEC6713_EDMA.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "D:\Projects\CCS5\DEC6713_EDMA\Debug\DEC6713_EDMA.out"
	-$(RM) "DEC6713_EDMA.pp" 
	-$(RM) "DEC6713.pp" 
	-$(RM) "f:\dec6713\soft design\dec6713\csl\DEC6713_EDMA\Debug\DEC6713.obj" "f:\dec6713\soft design\dec6713\csl\DEC6713_EDMA\Debug\DEC6713_EDMA.obj" "f:\dec6713\soft design\dec6713\csl\DEC6713_EDMA\Debug\vecs.obj" 
	-$(RM) "vecs.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

