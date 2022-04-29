
/*********************************************************************************
* DEC6713.C	v1.00	     							                            *
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
*********************************************************************************/
#include<dec6713.h>
#include<c6x.h>

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
	volatile Uint32 *emif_base = (volatile Uint32 *)0x01800000;
	volatile Uint32	*pll_base=(volatile Uint32 *)0x01b7c100;
		register int x0,x1,x2,x3,x4,x5,x6,y0,y1,y2,y3,y4,y5,y6;
		x0=emif_base[GBLCTL]; //0180 0000   EMIF global control
		x0|=0x00000020;/*��5λ��һ������ʱ��*/
		x0&=0xffffff67;/*3 4 7 ���� ����λΪ0���������� 34λΪ0������״̬*/
		x1=0xffffbf33;
		x5=0x56227000;
		x6=0x00281578;
		y0 = pll_base[PLLCSR];   //01B7 C100  PLL control/status register
		y1 = 0x00008012;
		y2 = 0x00008000;
		y3 = 0x00008001;
		y4 = 0x00008003;
		y5 = 0x00008004;
		y6 = 0x00008004;

		/* Initialize PLL Registers ��ʼ�����໷�Ĵ���*/
		/* Put PLL in bypass �����໷������·*/
		y0 &= 0xfffffffe;/*ĩλ���� ��·ģʽ�����໷����*/
		pll_base[PLLCSR]=y0;

		PLLDelay(20);
		/* Reset PLL ��λ���໷ */
		y0 |= 0x00000008;/*��3λ��һ��λ���໷*/
		pll_base[PLLCSR]=y0;
		PLLDelay(20);

		pll_base[PLLM]=y1; ;/*y1=0x00000012;���໷��ģʽ10010.PLL_RSET(PLLM, 18)18��Ƶ*/
		PLLDelay(20);
		pll_base[PLLDIV0]=y2;//y2=0x00008000;15λ��һ��������Ƶ�����á�0000λһ��Ƶ
		PLLDelay(20);
		pll_base[OSDDIV]=y6;//y6=0x00008004;15λ��һ������Ƶ��1����(Ĭ��)��0100���Ƶ
		PLLDelay(20);

		pll_base[PLLDIV1]=y3;//y3=0x00008001;15λ��1��������Ƶ�����á�0001λ����Ƶ
		PLLDelay(20);

		pll_base[PLLDIV2]=y4;//450M/4=112.5M
		PLLDelay(20);

		pll_base[PLLDIV3]=y5;//450M/5=90MHz
		PLLDelay(20);

		y0 &=0xfffffff7;/*��3λ���� ���໷��λ*/
		pll_base[PLLCSR]=y0;
		PLLDelay(1500);

		y0 |=0x00000001;/*ĩλ��1 ���໷ģʽ*/
		pll_base[PLLCSR]=y0;
		PLLDelay(20);

		emif_base[GBLCTL]=x0;
		emif_base[CECTL0]=x1;
		emif_base[SDCTL]=x5;
		emif_base[SDTIM]=x6;
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
