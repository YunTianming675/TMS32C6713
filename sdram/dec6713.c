#include<dec6713.h>
#include<stdio.h>

void Delay(Uint32 n)
{
	volatile Uint32 i = n;
	while(i--);
}

void DEC6713_Init(void)
{
	volatile Uint32 *emif_base;
	volatile struct pll *p;
	register int x, x0, x1, x2, x3, x4;

	p = (struct pll *)0x01B7C100;
	x = p->pllcsr;
	x &= -2;			// 1111....1110
	p->pllcsr = x;  	// 关闭PLL
	Delay(20);
	x = p->pllcsr;
	x |= 8;				// 1000
	p->pllcsr = x;		// PLL复位
	Delay(20);
//	x = p->pllm;
//	x &= 0xFFFFFFE0;	// 1111_1111_1110_0000
//	p->pllm = x;		// 倍频系数置0
	x = 18;				// 0001_0000
	p->pllm = x;		// 倍频系数置1
	Delay(20);
	x = 0x00008000;
	p->plldiv0 = x;	// 使能分频器0
//	x = 0xFFE0;			// 1111_1111_1110_0000
//	p->plldiv0 &= x;	// 分频系数置1
//	x = 1;
//	p->plldiv0 |= x;	// 分频系数置2
	Delay(20);

	x = 0x00008001;
	p->plldiv1 = x;	// 使能分频器1
//	x = 0xFFE0;			// 1111_1111_1110_0000
//	p->plldiv1 &= x;	// 分频系数置1
//	x = 3;				// 0011
//	p->plldiv1 |= x;	// 分频系数置3
	Delay(20);

	x = 0x00008003;
	p->plldiv2 = x;	// 使能分频器2
//	x = 0xFFE0;
//	p->plldiv2 &= x;	// 分频系数置1
//	x = 4;
//	p->plldiv2 |= x;	// 分频系数置5
	Delay(20);

	x = 0x00008004;
	p->plldiv3 = x;
	Delay(20);

//	x = p->oscdiv;
//	x |= 1<<15;
//	p->oscdiv |= x;		// 使能晶振分频
//	x &= 0xFFFFFFE0;
//	p->oscdiv &= x;		// 晶振分频置1
//	x |= 4;
	p->oscdiv = x;		// 晶振分频置5
	Delay(20);

	x &= 0xFFFFFFFE;			// 1111_1111_1111_0111
	p->pllcsr = x;		// 释放PLL复位
	Delay(20);

	x &= -2;
	x |= 8;
	x &= 0xFFFFFFF7;
	p->pllcsr = x;		// 将系统时钟切换到PLL
	Delay(1500);
	x |= 1;
	p->pllcsr = x;
	Delay(20);

	// EMIF
	emif_base = (volatile Uint32 *)0x01800000;
	x1 = emif_base[0];
	x1 &= 0xFFFFFF67;	// ...0010_0111
	x1 |= 1<<5;

	x2 = emif_base[2];
	x2 = 0xFFFFBF33;
//	x2 |= 3<<4;

//	x3 = emif_base[6];
//	x3 &= 0x80000FFF;
//	x3 |= 1<<30;
//	x3 |= 1<<28;
//	x3 |= 1<<26;
//	x3 |= 0xFF226FFF;	// ...0010_0010_0110...
	x3 = 0x56227000;

//	x4 = emif_base[7];
//	x4 &= 0xFC000000;	// 1111_1100...
//	x4 |= 1<<24;
//	x4 |= 1400;
	x4 = 0x00281578;

	x0 = emif_base[8];	// EMIF SDRAM extension
	x0 &= 0xFFE00000;
	x0 |= 0x0008854;

	emif_base[0] = x;
	emif_base[2] = x2;
	emif_base[6] = x3;
	emif_base[7] = x4;
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
