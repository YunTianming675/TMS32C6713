
/*********************************************************************************
* DEC6713.C	v1.00	     							                            *
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
*********************************************************************************/
//#include <csl.h>
//#include <csl_mcasp.h>
//#include <csl_i2c.h>
//#include <csl_emif.h>
//#include <csl_pll.h>
#include <dec6713.h>
#include <irq.h>
#include <c6x.h>

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

		volatile Uint32 *emif_base=(volatile Uint32*)0x01800000,*pll_base=(volatile Uint32*)0x01b7c100;
		register int x0,x1,x2,x3,x4,x5,x6;
		register int y0,y1,y2,y3,y4,y5,y6;
		x0=emif_base[GBLSTL];
		x0|=0x00000020;
		x0&=0xffffbf67;
		x1=0xffffbf33;
		x5=0x56227000;
		x6=0x00281578;
		y0=pll_base[PLLCSR];
		y1=0x00000012;
		y2=0x00008000;
		y3=0x00008001;
		y4=0x00008003;
		y5=0x00008004;
		y6=0x00008004;

	/* Initealize the board APIs */
	/*EMIF_Config MyEMIFcfg0={
		0x30								|
		EMIF_FMKS(GBLCTL,NOHOLD,DISABLE)	|
		EMIF_FMKS(GBLCTL,EKEN,DEFAULT)		|
		EMIF_FMKS(GBLCTL,CLK1EN,DISABLE)	|
		EMIF_FMKS(GBLCTL,CLK2EN,DISABLE),

		EMIF_FMKS(CECTL,WRSETUP,DEFAULT)	|
		EMIF_FMKS(CECTL,WRSTRB,DEFAULT)		|
		EMIF_FMKS(CECTL,WRHLD,DEFAULT)		|
		EMIF_FMKS(CECTL,RDSETUP,DEFAULT)	|
		EMIF_FMKS(CECTL,TA,OF(2))			|
		EMIF_FMKS(CECTL,RDSTRB,DEFAULT)		|
		EMIF_FMKS(CECTL,MTYPE,SDRAM32)		|
		EMIF_FMKS(CECTL,RDHLD,DEFAULT),

		EMIF_FMKS(CECTL, WRSETUP, OF(0))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(8))     |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(0))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(8))     |
        EMIF_FMKS(CECTL, MTYPE, ASYNC16)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),

        EMIF_FMKS(CECTL, WRSETUP, OF(0))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(8))     |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(0))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(8))     |
        EMIF_FMKS(CECTL, MTYPE, ASYNC8)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),

		EMIF_FMKS(CECTL, WRSETUP, OF(2))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(10))    |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(2))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(10))    |
        EMIF_FMKS(CECTL, MTYPE, ASYNC32)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),

        EMIF_FMKS(SDCTL,SDBSZ,4BANKS)		|
        EMIF_FMKS(SDCTL,SDRSZ,12ROW)		|
        EMIF_FMKS(SDCTL,SDCSZ,8COL)			|
        EMIF_FMKS(SDCTL,RFEN,ENABLE)		|
        EMIF_FMKS(SDCTL,INIT,YES)			|
        EMIF_FMKS(SDCTL,TRCD,OF(2))			|
        EMIF_FMKS(SDCTL,TRP,OF(2))			|
        EMIF_FMKS(SDCTL,TRC,OF(7)),

        //EMIF_FMKS(SDTIM,XRFR,OF(1))			|
        EMIF_FMKS(SDTIM, CNTR, OF(0))       |
        EMIF_FMKS(SDTIM, PERIOD, OF(1400)),

		EMIF_FMKS(SDEXT, WR2RD, OF(0))      |
        EMIF_FMKS(SDEXT, WR2DEAC, OF(2))    |
        EMIF_FMKS(SDEXT, WR2WR, OF(0))      |
        EMIF_FMKS(SDEXT, R2WDQM, OF(1))     |
        EMIF_FMKS(SDEXT, RD2WR, OF(0))      |
        EMIF_FMKS(SDEXT, RD2DEAC, OF(1))    |
        EMIF_FMKS(SDEXT, RD2RD, OF(0))      |
        EMIF_FMKS(SDEXT, THZP, OF(2))       |
        EMIF_FMKS(SDEXT, TWR, OF(2))        |
        EMIF_FMKS(SDEXT, TRRD, OF(0))       |
        EMIF_FMKS(SDEXT, TRAS, OF(5))       |
        EMIF_FMKS(SDEXT, TCL, OF(1))
        };*/

	/* Initialize PLL Registers */
		/* Put PLL in bypass */
		x0&=0xfffffffe;
		pll_base [PLLCSR]=x0;

	//PLL_bypass();
	PLLDelay(20);

		/* Reset PLL */
	    x0|=0x00000008;
		pll_base[PLLCSR]=x0;

	//PLL_reset();
	PLLDelay(20);

		/* Set main multiplier/divisor */
	    pll_base[PLLM]=y1;
		pll_base[PLLDIV0]=y2;
		pll_base[OSDDIV]=y6;

 	//PLL_RSET(PLLM, 18);                         // 25MHz  x 18 = 450MHz
   // PLL_RSET(PLLDIV0, PLL_PLLDIV0_RMK(1, 0));  // 450MHz / 1 = 450MHz
    //PLL_RSET(OSCDIV1, PLL_OSCDIV1_RMK(1, 4));  // 25MHz  / 5 = 5Mhz

    /* Set DSP clock */
        pll_base[PLLDIV1]=y3;

   // PLL_RSET(PLLDIV1, PLL_PLLDIV1_RMK(1, 1));  // 450MHz / 2 = 225MHz
    PLLDelay(20);

    /* Set peripheral clock */
    pll_base[PLLDIV2]=y4;
   // PLL_RSET(PLLDIV2, PLL_PLLDIV2_RMK(1, 3));  // 450MHz / 4 = 112.5MHz
    PLLDelay(20);

    /* Set EMIF clock */
       pll_base[PLLDIV3]=y5;

   // PLL_RSET(PLLDIV3, PLL_PLLDIV3_RMK(1, 4));  // 450MHz / 5 = 90MHz
    PLLDelay(20);

    	/* Take PLL out of reset */
       x0&=0xfffffff7;

   //PLL_deassert();
    PLLDelay(1500);

    	/* Enalbe PLL */
        x0|=0x00000001;
        pll_base[PLLCSR]=x0;

    //PLL_enable();
    PLLDelay(20);

   	/* Initialize EMIF */
        emif_base[GBLSTL]=x0;
        emif_base[CECTL0]=x1;
        emif_base[SDCTL]=x5;
        emif_base[SDTIM]=x6;

    //EMIF_config(&MyEMIFcfg0);

	/* Set CPLD registers to default state  */
   	//DEC6713_cpld_rset(DEC6713_CTL_REG, 0x00);

}
/********************************************************************************\
\*Uint8 DEC6713_cpld_rget()		-Read CPLD register?
\*Parameters:
\*		regnum: The related register.

\*Return: The related register value.
\********************************************************************************/

   	/* Read CPLD register(8bits) */
	Uint8 DEC6713_cpld_rget(Int8 regnum)
	{
    	Uint8 *pdata;

    	/* Return lower 8 bits of register */
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

	/* Write CPLD register(8bits) */
	void DEC6713_cpld_rset(Int8 regnum, Uint8 regval)
	{
	    Uint8 *pdata;

    	/* Write lower 8 bits of register */
    	pdata = (Uint8 *)(DEC6713_CPLD_BASE + regnum);
    	*pdata = (regval & 0xff);
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
	void IRQ_setVecs(void *vecs)
	{
		register int p,ir;
		p=(Uint32)vecs;
		ir=ISTP;
		ir&=0xfffffc00;
		p&=0xfffffc00;
		ir=p;
		ISTP=ir;

	}
/********************************************************************************\
\* End of DEC6713.C *\
\********************************************************************************/
