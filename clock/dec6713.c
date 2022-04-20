#include<dec6713.h>
#include<stdio.h>

int main(void)
{
	DEC6713_Init();
	while(1)
	{}
}

void Delay(Uint32 n)
{
	volatile Uint32 i = n;
	while(i--);
}

void DEC6713_Init(void)
{
	struct pll *p;
	register int x, x0, x1, x2, x3, x4;

	p = (struct pll *)0x01B7C100;
	x = -2;				// 1111....1110
	p->pllcsr &= x;  	// �ر�PLL
	Delay(20);
	x = 8;				// 1000
	p->pllcsr |= 8;		// PLL��λ
	Delay(20);
	x = 0xFFE0;			// 1111_1111_1110_0000
	p->pllm &= x;		// ��Ƶϵ����0
	x = 17;				// 0001_0001
	p->pllm |= x;		// ��Ƶϵ����1
	Delay(20);
	x = 1<<15;			// 1000_0000_0000_0000
	p->plldiv0 |= x;	// ʹ�ܷ�Ƶ��0
	x = 0xFFE0;			// 1111_1111_1110_0000
	p->plldiv0 &= x;	// ��Ƶϵ����1
	x = 1;
	p->plldiv0 |= x;	// ��Ƶϵ����2
	Delay(20);

	x = 1<<15;			// 1000_0000_0000_0000
	p->plldiv1 |= x;	// ʹ�ܷ�Ƶ��1
	x = 0xFFE0;			// 1111_1111_1110_0000
	p->plldiv1 &= x;	// ��Ƶϵ����1
	x = 3;				// 0011
	p->plldiv1 |= x;	// ��Ƶϵ����3
	Delay(20);

	x = 1<<15;
	p->plldiv2 |= x;	// ʹ�ܷ�Ƶ��2
	x = 0xFFE0;
	p->plldiv2 &= x;	// ��Ƶϵ����1
	x = 4;
	p->plldiv2 |= x;	// ��Ƶϵ����5
	Delay(20);

	x = 1<<15;
	p->oscdiv |= x;		// ʹ�ܾ����Ƶ
	x = 0xFFE0;
	p->oscdiv &= x;		// �����Ƶ��1
	x = 4;
	p->oscdiv |= x;		// �����Ƶ��5
	Delay(20);

	x = 0xFFF7;			// 1111_1111_1111_0111
	p->pllcsr &= x;		// �ͷ�PLL��λ
	Delay(20);

	x = 1;
	p->pllcsr |= x;		// ��ϵͳʱ���л���PLL
	Delay(1500);
	x = p->pllcsr;
	x |= 1;
	p->pllcsr = x;
	Delay(20);

	// EMIF
	emif_base = (volatile Uint32 *)0x01800000;
	x1 = emif_base[0];
	x1 &= 0xFFFFFF37;
	x1 |= 1<<5;

	x2 = emif_base[2];
	x2 &= 0xFFFFFF0F;
	x2 |= 3<<4;

	x3 = emif_base[6];
	x3 &= 0x80000FFF;
	x3 |= 1<<30;
	x3 |= 1<<28;
	x3 |= 1<<26;
	x3 |= 0xFF226FFF;

	x4 = emif_base[7];
	x4 &= 0xFC000000;
	x4 |= 1<<24;
	x4 |= 1400;

	x0 = emif_base[8];
	x0 &= 0xFFE00000;
	x0 |= 0x0008854;

	emif_base[0] = x1;
	emif_base[2] = x2;
	emif_base[6] = x3;
	emif_base[7] = x4;
	emif_base[8] = x0;
}
