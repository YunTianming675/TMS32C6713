#include<dec6713.h>
#include<stdio.h>

void Delay(Uint32 n)
{
	volatile Uint32 i = n;
	while(i--);
}

void DEC6713_Init(void)
{
	struct pll *p;
	register int x;

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
}
