#include<dec6713.h>
#include<irq.h>
#include<c6x.h>
#include<stdio.h>
#include<stdlib.h>

extern far void vectors();

static Uint32 cnt = 0;

volatile Uint32 *mux = (volatile Uint32 *)MUX_ADDR;
volatile Uint32 *tim = (volatile Uint32 *)TIM1_ADDR;

int main()
{

	register int x0, x1;
	register int y0, y1, y2;

	DEC6713_Init();
	IRQ_setVecs(vectors);

	x0 = TINT1ID;
	x1 = CSR;
	x1 |= 1;
	CSR = x1;
	x1 = IER;
	x1 |= 2;
	IER = x1;
	x1 = mux[0];
	x1 &= 0xFC1FFFFF;
	x1 |= x0<<21;
	mux[0] = x1;
	x1 = IER;
	x1 &= ~x0;
	IER = x1;
	y0 = tim[0];
	y1 = 0xB72;
	y2 = 0;
	y0 &= 0xFFFFFBFF;
	y0 |= 0x00000200;
	y0 &= 0xFFFFFEFF;
	y0 |= 0x00000080;
	y0 &= 0xFFFFFFBF;
	y0 |= 0x00000010;
	y0 &= 0xFFFFFFFD;
	y0 |= 1;
	tim[0] = y0;
	tim[1] = y1;
	tim[2] = y2;
	x1 = IER;
	x1 |= 0x00004000;
	IER = x1;
	x1 = tim[0];

	while(cnt<20);
}

void TimerEventHandler(void)
{
	register int x;

	cnt++;
	if(cnt > 20)
	{
		x = tim[0];
		x &= 0x00000080;
		tim[0] = x;
	}
}

interrupt void
c_int14(void)
{
    TimerEventHandler();
    return;
}
