#include <DEC6713.h>

static void PLLDelay(int Count)
{
    volatile int i = Count;
    while(i--);
}

void DEC6713_init()
{
	volatile Uint32 *emif_base = (volatile Uint32 *)0x01800000;
	volatile Uint32 *pll_base = (volatile Uint32 *)0x01b7c100;
	register int x0, x1, x5, x6;
	register int y0, y1, y2, y3, y4, y5, y6;
	x0 = emif_base [GBLCTL];
	x0 |= 0x00000020;
	x0 &= 0xffffff67;
	x1 = 0xffffbf33;
	x5 = 0x56227000;
	x6 = 0x00281578;
	y0 = pll_base[PLLCSR];
	y1 = 0x00000012;
	y2 = 0x00008000;
	y3 = 0x00008001;
	y4 = 0x00008003;
	y5 = 0x00008004;
	y6 = 0x00008004;

	x0 &= 0xfffffffe;
	pll_base[PLLCSR]=x0;
	PLLDelay(20);
	x0 |= 0x00000008;
	pll_base[PLLCSR]=x0;
	PLLDelay(20);
	pll_base[PLLM]=y1;
	pll_base[PLLDIV0]=y2;
	pll_base[DSDDIV]=y6;
	pll_base[PLLDIV1]=y3;
	PLLDelay(20);
	pll_base[PLLDIV2]=y4;
	PLLDelay(20);
	pll_base[PLLDIV3]=y5;
	PLLDelay(20);
	x0 &=0xfffffff7;
	pll_base[PLLCSR]=x0;
	PLLDelay(1500);
	x0 |=0x00000001;
	pll_base[PLLCSR]=x0;
	PLLDelay(20);
	emif_base[GBLCTL]=x0;
	emif_base[GECTL0]=x1;
	emif_base[SDCTL]=x5;
	emif_base[SDTIM]=x6;
}

/* Read CPLD register(8bits) */
Uint8 DEC6713_cpld_rget(Int8 regnum)
{
	Uint8 *pdata;

	/* Return lower 8 bits of register */
	pdata = (Uint8 *)(DEC6713_CPLD_BASE + regnum);
	return (*pdata & 0xff);
}

void DEC6713_cpld_rset(Int8 regnum, Uint8 regval)
{
	Uint8 *pdata;

	/* Write lower 8 bits of register */
	pdata = (Uint8 *)(DEC6713_CPLD_BASE + regnum);
	*pdata = (regval & 0xff);
}

void DEC6713_wait(Uint32 delay)
{
	volatile Uint32 i, n;

	n = 0;
	for (i = 0; i < delay; i++)
	{
		n = n + 1;
	}
}
