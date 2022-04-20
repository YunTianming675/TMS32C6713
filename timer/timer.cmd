
/****************************************************************************\
\*  Timer.cmd	V1.00													    *\

\*  Copyright 2004 by SEED Electronic Technology LTD.                           *\
\*  All rights reserved. SEED Electronic Technology LTD.                        *\
\*  Restricted rights to use, duplicate or disclose this code are               *\
\*  granted through contract.    											    *\

\*	Designed by: Hongshuai.Li
\****************************************************************************/

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
