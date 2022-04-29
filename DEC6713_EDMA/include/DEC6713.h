/********************************************************************************\
\*DEC6713.H	  	v1.00	     							                            *
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
\********************************************************************************/
#ifndef DEC6713_
#define DEC6713_

#include <csl.h>

/* CPLD address definitions */
#define DEC6713_CPLD_BASE    0x90100000

/* CPLD Register Indices */
#define DEC6713_CTL_REG    	 	0x00;
#define DEC6713_INTSTAT_REG		0x01;
#define DEC6713_STAT_REG		0x02;
#define DEC6713_WDT_REG			0x03;

/* Initialize all board APIs */
void DEC6713_init();

/* Read an 8-bit value from a CPLD register */
Uint8 DEC6713_cpld_rget(Uint8 regnum);

/* Write an 8-bit value to a CPLD register */
void DEC6713_cpld_rset(Uint8 regnum, Uint8 regval);

/* Spin in a delay loop for delay iterations */
void DEC6713_wait(Uint32 delay);

#endif
