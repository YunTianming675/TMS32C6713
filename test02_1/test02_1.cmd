 test02_1.obj
-o test02_1.out
MEMORY
{
 	PAGE 0: ROM:  ORIGIN=00000080H, LENGTH=1000H
          	ROM1: ORIGIN=00002000H, LENGTH=500H
 	PAGE 1: RAM1: ORIGIN=00003000H, LENGTH=2000H
          	RAM2: ORIGIN=00005500H, LENGTH=1000H
          	RAM3: ORIGIN=00006600H, LENGTH=500H
 }
 SECTIONS
{
	.text	     :>ROM   PAGE 0
	.bss	     :>RAM1  PAGE 1
	fir_tab      :>ROM1  PAGE 0
	fir_buff     :>RAM2  PAGE 1
	data_buff    :>RAM3  PAGE 1
}
