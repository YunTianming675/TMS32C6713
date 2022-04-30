/********************************************************************************\
\*DEC6713.H	  	v1.00	     							                            *
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
\********************************************************************************/
#ifndef DEC6713_
#define DEC6713_


//#include <csl.h>

/* CPLD address definitions */
#define DEC6713_CPLD_BASE    0xA0080000

/* CPLD Register Indices */
#define DEC6713_CTL_REG    	 	0x00;
#define DEC6713_INTSTAT_REG		0x01;
#define DEC6713_STAT_REG		0x02;
#define DEC6713_WDT_REG			0x03;

#define GBLSTL 0
#define CECTL0 2
#define CECTL1 1
#define CECTL2 4
#define CECTL3 4
#define SDCTL 6
#define SDTIM 7

#define PLLCSR 0
#define PLLM 4
#define PLLDIV0 5
#define PLLDIV1 6
#define PLLDIV2 7
#define PLLDIV3 8
#define OSDDIV 9

typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;
typedef  int Int32;
typedef short Int16;
typedef char Int8;

/* Initialize all board APIs */
void DEC6713_init();

/* Read an 8-bit value from a CPLD register */
Uint8 DEC6713_cpld_rget(Int8 regnum);

/* Write an 8-bit value to a CPLD register */
void DEC6713_cpld_rset(Int8 regnum, Uint8 regval);

/* Spin in a delay loop for delay iterations */
void DEC6713_wait(Uint32 delay);

#endif
