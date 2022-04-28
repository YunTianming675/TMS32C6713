
/*********************************************************************************
* DEC6713.C	v1.00	     							                            *
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
*********************************************************************************/
#include <csl.h>
#include <csl_mcasp.h>
#include <csl_i2c.h>
#include <csl_emif.h>
#include <csl_pll.h>
#include "dec6713.h"


/*Local software delay function*/
static void PLLDelay(int Count)
{
    volatile int i = Count;
    while(i--);
}

/********************************************************************************\
\*DEC6713_init()	-Initialize DEC6713 board.
\*Parameters: NO.
\*
\*Return:No.
\********************************************************************************/

void DEC6713_init()
{
	volatile Uint32 *emif_base = (volatile Uint32 *)0x01800000,*pll_base=(volatile Uint32 *)0x01b7c100;
		register int x0,x1,x2,x3,x4,x5,x6;
		register int y0,y1,y2,y3,y4,y5,y6;

		x0=emif_base[GBLCTL]; //0180 0000   EMIF global control
		x1=emif_base[CECTL0]; //0180 0008   EMIF CE0 space control
		x2=emif_base[CECTL1]; //0180 0004   EMIF CE1 space control
		x3=emif_base[CECTL2]; //0180 0010   EMIF CE2 space control
		x4=emif_base[CECTL3]; //0180 0014   EMIF CE3 space control
		x5=emif_base[SDCTL];  //0180 0018   EMIF SDRAM control
		x6=emif_base[SDTIM];  //0180 001C   EMIF SDRAM refresh control
		x0&= 0xffffff67;      //0180 0000
		x0|= 0x00000020;      //0180 0020
		x1|= 0xffffffff;      //ffff ffff
		x1&= 0xffffbf33;      //ffff bf33
		x5 = 0x56227000;
		x6 = 0x00281578;
		y0 = pll_base[PLLCSR];   //01B7 C100  PLL control/status register
		y1 = pll_base[PLLM];     //01B7 C110  PLL multiplier control register
		y2 = pll_base[PLLDIV0];  //01B7 C114  PLL controller divider 0 register
		y3 = pll_base[PLLDIV1];  //01B7 C118 PLLDIV1 PLL controller divider 1 register
		y4 = pll_base[PLLDIV2];  //01B7 C11C PLLDIV2 PLL controller divider 2 register
		y5 = pll_base[PLLDIV3];  //01B7 C120 PLLDIV3 PLL controller divider 3 register

		y1 = 0x00008012;
		y2 = 0x00008000;
		y3 = 0x00008001;
		y4 = 0x00008003;
		y5 = 0x00008004;
		y6 = 0x00008004;

		y0 &= 0xfffffffe;        //y0=01b7 c100    最低位=0;
		pll_base[PLLCSR]=y0;     //0位PLLEN=0, 旁路模式

		PLLDelay(20);

		y0 |= 0x00000008;        //y0=01b7 c108
		pll_base[PLLCSR]=y0;     //第3位 PLLRST=1 处于复位状态
		PLLDelay(20);

		pll_base[PLLM]=y1;       //y1=0x0000_8012  PLLMUL锁相环乘数位=12H=18   25MHz*18=450MHz
		PLLDelay(20);
		pll_base[PLLDIV0]=y2;    //y2=0x0000_8000  DnEN=1 Divider n is enabled; RATIO=0  f/1=450MHz
		PLLDelay(20);
		pll_base[OSDDIV]=y6;     //y6=0x0000_8004  OD1EN=1 Oscillator divider 1 is enabled.  RATIO=4  f/5  25M/5=5M
		PLLDelay(20);

		pll_base[PLLDIV1]=y3;    //y3=0x0000_8001   DnEN=1 Divider n is enabled; RATIO=1  f/2  450M/2=225M
		PLLDelay(20);

		pll_base[PLLDIV2]=y4;    //y4=0x0000_8003   DnEN=1 Divider n is enabled; RATIO=3  f/4  450M/4=112.5M
		PLLDelay(20);

		pll_base[PLLDIV3]=y5;    //y5=0x0000_8004   DnEN=1 Divider n is enabled; RATIO=4  f/5  450M/5=90MHz
		PLLDelay(20);

		y0 &=0xfffffff7;         //y0=01b7 c100
		pll_base[PLLCSR]=y0;     //复位、使能全清0
		PLLDelay(1500);

		y0 |=0x00000001;         //y0=01b7 c101
		pll_base[PLLCSR]=y0;     //PLLEN=1
		PLLDelay(20);

		emif_base[GBLCTL]=x0;    //x0=0180 0020
		emif_base[CECTL0]=x1;    //EK1EN=1
		emif_base[SDCTL]=x5;     //x5=0x5622_7000
		                         //SDBSZ=1   Two bank-select pins (four banks)
		                         //SDRSZ=01H  12 row address pins (4096 rows per bank)
	                             //SDCSZ=01H   8 column address pins (256 elements per row)
		                         //RFEN=1 SDRAM refresh is enabled
		                         //INIT=0
		                         //23-20 TRCD=2H
	                             //19-16 TRP=2H
		                         //15-12 TRC=7H
		                         //SLFRFR=00H
		emif_base[SDTIM]=x6;     //x6=0x00281578
		                         //25-24 XRFR=0 ,1 refresh
		                         //23-12 CNTR=281H   Current value of the refresh count
		                         //11-0 PERIOD=578H Refresh period in EMIF clock cycles.(2)
}
/********************************************************************************\
\*Uint8 DEC6713_cpld_rget()		-Read CPLD register?
\*Parameters:
\*		regnum: The related register.

\*Return: The related register value.
\********************************************************************************/

/* Read CPLD register(8bits) */
Uint8 DEC6713_cpld_rget(Uint8 regnum)
{
   	Uint8 *pdata;
   	/* Return register value. */
   	pdata = (Uint8 *)(DEC6713_CPLD_BASE + regnum);
   	return (*pdata & 0xff);
}
/********************************************************************************\
\*Uint8 DEC6713_cpld_rset()		-Write CPLD register.
\*Parameters:
\*		regnum: The related register
\*		regval:To be writen register value.

\*Return: No.
\********************************************************************************/

/* Write CPLD register(8bits). */
void DEC6713_cpld_rset(Uint8 regnum,Uint8 regval)
{
	Uint8 *pdata;
	pdata = (Uint8 *)(DEC6713_CPLD_BASE + regnum);
	*pdata = regval & 0xFF;
}
/********************************************************************************\
\*Uint8 DEC6713_wait()		-DEC6713 Delay function
\*Parameters:
\*		delay:Delay time.

\*Return:NO.
\********************************************************************************/
	/* Spin in a delay loop for delay iterations */
void DEC6713_wait(Uint32 delay)
{
    volatile Uint32 i, n;
    n = 0;
    for (i = 0; i < delay; i++)
    {
        n = n + 1;
    }
}

/********************************************************************************\
\* End of DEC6713.C *\
\********************************************************************************/

//void *IRQ_setVecs(void *vecs)
//		{
//			register int p,x;
//			p=(Uint32)vecs;
//			x=ISTP;
//			x&=0xfffffc00;
//			p&=0xfffffc00;
//			x=p;
//			ISTP=x;
//		}
