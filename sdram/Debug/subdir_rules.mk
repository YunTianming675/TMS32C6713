################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
dec6713.obj: ../dec6713.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/Projects/CCS5/sdram/include" --define=c6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="dec6713.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sdram.obj: ../sdram.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/Projects/CCS5/sdram/include" --define=c6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="sdram.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


