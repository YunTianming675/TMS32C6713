/****************************************************************************/
/*  C6713.cmd                                                               */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an TMS320C6713        */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/


-c
-x

/* Memory Map 0 - the default */

MEMORY
{
	PMEM:	o = 00000000h	l = 00010000h
	BMEM:	o = 00010000h	l = 00030000h
	SDRAM:	o = 80000000h	l = 01000000h
}

SECTIONS
{
    .text       >   PMEM
    .csldata	> 	PMEM
    .stack		>   PMEM
    .far		>   PMEM
    .switch		>   BMEM
    .tables 	>   BMEM
    .data   	>   BMEM
    .bss		>   BMEM
    .sysmem		>   BMEM
    .cinit		>   PMEM
    .const		>   BMEM
    .cio    	>   BMEM
}
