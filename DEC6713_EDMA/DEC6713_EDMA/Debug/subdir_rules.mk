################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
f:/dec6713/soft\ design/dec6713/csl/DEC6713_EDMA/Debug/DEC6713.obj: D:/Projects/CCS5/DEC6713_EDMA/DEC6713.C $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6710 --abi=coffabi -g --include_path="C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/MyProgram/tools/CCS5/c6000/bios/include" --include_path="C:/MyProgram/tools/CCS5/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="D:/Projects/CCS5/DEC6713_EDMA/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --obj_directory="f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug" --preproc_with_compile --preproc_dependency="DEC6713.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

f:/dec6713/soft\ design/dec6713/csl/DEC6713_EDMA/Debug/DEC6713_EDMA.obj: D:/Projects/CCS5/DEC6713_EDMA/DEC6713_EDMA.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6710 --abi=coffabi -g --include_path="C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/MyProgram/tools/CCS5/c6000/bios/include" --include_path="C:/MyProgram/tools/CCS5/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="D:/Projects/CCS5/DEC6713_EDMA/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --obj_directory="f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug" --preproc_with_compile --preproc_dependency="DEC6713_EDMA.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

f:/dec6713/soft\ design/dec6713/csl/DEC6713_EDMA/Debug/vecs.obj: D:/Projects/CCS5/DEC6713_EDMA/vecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6710 --abi=coffabi -g --include_path="C:/MyProgram/tools/CCS5/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/MyProgram/tools/CCS5/c6000/bios/include" --include_path="C:/MyProgram/tools/CCS5/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="D:/Projects/CCS5/DEC6713_EDMA/include" --define="CHIP_6713" --quiet --display_error_number --diag_wrap=off --obj_directory="f:/dec6713/soft design/dec6713/csl/DEC6713_EDMA/Debug" --preproc_with_compile --preproc_dependency="vecs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


