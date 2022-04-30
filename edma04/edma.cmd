/*********************************************************************************
* edma.cmd
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
*********************************************************************************/

-c
-x

/* Memory Map 0 - the default */

MEMORY
{
	PMEM:	o = 00000000h	l = 00010000h
	BMEM:	o = 00010000h	l = 00030000h 
	
}

SECTIONS
{    
    .text       >   PMEM
    .csldata	> 	PMEM
    .stack	>   PMEM
    .far	>   PMEM
    .switch	>   BMEM 
    .tables >   BMEM
    .data   >   BMEM
    .bss	>   BMEM
    .sysmem	>   BMEM
    .cinit	>   PMEM
    .const	>   BMEM
    .cio    >   BMEM 
}
