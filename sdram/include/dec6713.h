#ifndef DEC6713_H
#define DEC6713_H

typedef unsigned long  Uint32;
typedef unsigned short Uint16;
typedef unsigned char  Uint8;

typedef long  Int32;
typedef short Int16;
typedef char  Int8;

#define DEC6713_CPLD_BASE 0xA0080000

#define DEC6713_CTL_REG 	0x00
#define DEC6713_INTSTAT_REG 0x01
#define DEC6713_STAT_REG	0x02
#define DEC6713_WDT_REG 	0x03

struct emif
{
	Uint32 gplctl;
	Uint32 cectl1;
	Uint32 cectl0;
	Uint32 cectl2;
	Uint32 cectl3;
	Uint32 rsv;
	Uint32 sdctl;
	Uint32 sdtim;
};
struct pll
{
	Uint32 pllcsr;
	Uint32 rsv1;
	Uint32 rsv2;
	Uint32 rsv3;
	Uint32 pllm;
	Uint32 plldiv0;
	Uint32 plldiv1;
	Uint32 plldiv2;
	Uint32 plldiv3;
	Uint32 oscdiv;
};

void Delay(Uint32 n);
void DEC6713_Init(void);

/* Read an 8-bit value from a CPLD register */
Uint8 DEC6713_cpld_rget(Int8 regnum);

/* Write an 8-bit value to a CPLD register */
void DEC6713_cpld_rset(Int8 regnum, Uint8 regval);

/* Spin in a delay loop for delay iterations */
void DEC6713_wait(Uint32 delay);

#endif
