#include<stdio.h>
#include<stdlib.h>
#include<dec6713.h>
#include<irq.h>
#include<edma.h>
#include<c6x.h>

#define TCCINTNUM	 10
#define BUFF_SZ      256
#define FCPU         150000000
#define SRATE        8000
#define TPRD         (FCPU/(4*SRATE))
#define TRANSFER_CNT 20

#pragma DATA_ALIGN(ping, 128);
#pragma DATA_ALIGN(pong, 128);
#pragma DATA_ALIGN(outbuff, 128);
int ping[BUFF_SZ];
int pong[BUFF_SZ];
int outbuff[BUFF_SZ];
volatile int sp[1100];

#pragma DATA_ALIGN(ping_data, 128);
#pragma DATA_ALIGN(pong_data, 128);
static int ping_data;
static int pong_data;

static int pingpong = 0;

volatile int transferCount = 0;

volatile Uint32 *pram_base;
volatile Uint32 *esel_base;
volatile Uint32 *edmar_base;

extern far void vectors();

void setupInterrupts(void);
void stopEdma(void);
void CACHE_clean1(Uint32 region, void *addr, Uint32 wordCnt);
void CACHE_wbInvL2(void *blockPtr, Uint32 byteCnt, int wait);

Uint32 *mux_addr = (Uint32 *)MUXADDR;
Uint32 *timer_base = (Uint32 *)TIM1ADDR;
Uint32 *edma_addr = (Uint32 *)EDMAADDR;

int main()
{
	register int x1, x2, x3, x4, x5, x6;
	register int y1, y2, y3, y4, y5, y6;
	register int t, t1, t2;
	volatile Uint32 *p1, *p2, *p3;

	x1 = 0x403A0002;
	x2 = (Uint32)(&ping_data);
	x3 = BUFF_SZ;
	x4 = (Uint32)ping;
	x5 = 0x00000004;
	x6 = 0x00000000;

	y1 = 0x403A0002;
	y2 = (Uint32)(&pong_data);
	y3 = BUFF_SZ;
	y4 = (Uint32)pong;
	y5 = 0x00000004;
	y6 = 0x00000000;

	*(int *)0x01840000 = (*(int *)0x01840000 & 0x00000000);

	DEC6713_init();
	ping_data = 0x00000000;
	pong_data = 0x80000000;

	CACHE_wbInvL2(&ping_data, 4, CACHE_WAIT);
	CACHE_wbInvL2(&pong_data, 4, CACHE_WAIT);

	setupInterrupts();

	for(p1=(Uint32 *)0x01a00000, t=0; t <= 0x8000>>2; t++)
	{
		p1[t] = y6;
	}

	esel_base = (volatile Uint32 *)0x01A0FF00;
	t = esel_base[0];
	t &= 0xFFC0FFFF;
	t |= 0x00020000;
	esel_base[0] = t;

	pram_base = (volatile Uint32 *)(PRAMADDR+2*6*4);
	pram_base[0] = x1;
	pram_base[1] = x2;
	pram_base[2] = x3;
	pram_base[3] = x4;
	pram_base[4] = x5;
	pram_base[5] = (PRAMADDR+10*6*4)&0x0000FFFF;
	p1 = &pram_base[5];

	pram_base = (volatile Uint32 *)(PRAMADDR+8*6*4);
	t1 = (Uint32)pram_base;
	pram_base[0] = x1;
	pram_base[1] = x2;
	pram_base[2] = x3;
	pram_base[3] = x4;
	pram_base[4] = x5;
	pram_base[5] = x6;
	p2 = &pram_base[5];

	pram_base = (volatile Uint32 *)(PRAMADDR+10*6*4);
	t2 = (Uint32)pram_base;
	pram_base[0] = y1;
	pram_base[1] = y2;
	pram_base[2] = y3;
	pram_base[3] = y4;
	pram_base[4] = y5;
	pram_base[5] = y6;
	p3 = &pram_base[5];

	*p1 = t2;
	*p2 = t1;
	*p3 = t2;

	p1 = (volatile Uint32 *)0x01980000;
	p1[0] = 0x00000200;
	p1[1] = TPRD;
	p1[2] = 0;

	t = IER;
	t |= 1<<8;
	IER = t;
	edmar_base = (volatile Uint32 *)0x01A0FFE0;
	t = edmar_base[CIER];
	t &= ~(1<<TCCINTNUM);
	edmar_base[CIER] = t;
	t = edmar_base[CIPR];
	t &= ~(1<<TCCINTNUM);
	edmar_base[CIPR] = t;
	t = edmar_base[CIER];
	t |= (1<<TCCINTNUM);
	edmar_base[CIER] = t;
	edmar_base = (volatile Uint32 *)0x01A0FFE0;
	t = edmar_base[EER];
	t |= 1<<2;
	edmar_base[EER] = t;
	x1 = timer_base[0];
	x1 |= 0x00000080;
	x1 |= 0x00000040;
	timer_base[0] = x1;

	while(transferCount <= TRANSFER_CNT);
}

void processbuff(int arg)
{
	int *inbuff;
	int x;

	printf("\n %2d -",transferCount);
	if (pingpong)
	{
		inbuff = ping;
		printf(" Ping ");
	}
	else
	{
		inbuff = pong;
		printf(" Pong " );
	}
	transferCount++;
	for (x=0; x<BUFF_SZ; x++)
	{
		outbuff[x] = inbuff[x];
	}
	CACHE_wbInvL2(outbuff, (BUFF_SZ << 2), CACHE_WAIT);
	CACHE_clean1(CACHE_L2, inbuff, (BUFF_SZ << 2));
}

void setupInterrupts(void)
{
	register int t;
	volatile Uint32 *p;

	IRQ_setVecs(vectors);

	t = IER;
	t |= 1<<1;
	IER = t;
	t = CSR;
	t |= 1;
	CSR = t;

	p = (volatile Uint32*)0x019C0000;
	t = p[MUXL];
	t &= 0xFC1FFFFF;
	t |= 8<<21;
	p[MUXL] = t;
	t = IER;
	t &= ~(1<<8);
	IER = t;
	t = 8;
	ICR = t;
}

interrupt void
c_int08(void)
{
	register int t;
	volatile Uint32 *p1;

	p1 = (Uint32 *)0x01980000;
	t = edmar_base[CIPR];
	t &= ~(1<<TCCINTNUM);
	edmar_base[CIPR] = t;
	pingpong = (pingpong + 1) & 1;

	if (transferCount >= TRANSFER_CNT)
	{
		t = p1[0];
		t &= ~(1<<7);
		p1[0] = t;
		stopEdma();
		t = p1[0];
		t &= ~(1<<6);
		p1[0] = t;
		printf ("\nDone.....");
		exit(0);
	}
	if (pingpong)
	{
		ping_data++;
		CACHE_wbInvL2(&ping_data, 4, CACHE_WAIT);
		*(int *)0x01A00044 = 0x01A000C0 & 0x0000FFFF;
	}
	else
	{
		pong_data++;
		CACHE_wbInvL2(&pong_data, 4, CACHE_WAIT);
		*(int *)0x01A00044 = 0x01A000F0 & 0x0000FFFF;
	}
	processbuff(0);

	return;
}

void stopEdma(void)
{
	register int x1, x2;
	 x1 = EDMAINT;
	 x2 = IER;
	 x2 &= ~x1;
	 IER = x2;
	 ICR = x1;
}

void CACHE_clean1(Uint32 region,void *addr,Uint32 wordCnt)
{
	volatile Uint32 *p=(Uint32 *)0x01844010,*q=(Uint32 *)0x01845000,*a;
	volatile int *t;
	//int sp[1030];
	register int x1,x2,i;
	t=sp;
	a=addr;
	for(i=0;i<wordCnt>>2;i++)
	{
		x1=a[i];
		*t++=x1;
	}
	for(i=0;i<BUFF_SZ;i++)
	{
		x1=ping[i];
		*t++=x1;
	}
	for(i=0;i<BUFF_SZ;i++)
	{
		x1=pong[i];
		*t++=x1;
	}
	for(i=0;i<BUFF_SZ;i++)
	{
		x1=outbuff[i];
		*t++=x1;
	}
	x1=ping_data;
	*t++=x1;
	x1=pong_data;
	*t=pong_data;
	DEC6713_wait(8);
	x2=q[1];
	x2|=1;
	q[1]=x2;
	DEC6713_wait(5000);
	x2=q[1];
	x2&=0xfffffffe;
	q[1]=x2;
	DEC6713_wait(8);
	x1=*t--;
	pong_data=x1;
	x1=*t--;
	ping_data=x1;
	for(i=BUFF_SZ-1;i>=0;i--)
	{
		x1=*t--;
		outbuff[i]=x1;
	}
	for(i=BUFF_SZ-1;i>=0;i--)
	{
		x1=*t--;
		pong[i]=x1;
	}
	for(i=BUFF_SZ-1;i>=0;i--)
	{
		x1=*t--;
		ping[i]=x1;
	}DEC6713_wait(8);
	CACHE_wbInvL2(&ping_data, 4, CACHE_WAIT);
	CACHE_wbInvL2(&pong_data, 4, CACHE_WAIT);
	CACHE_wbInvL2(outbuff, (BUFF_SZ << 2), CACHE_WAIT);

	CACHE_wbInvL2(addr, wordCnt, CACHE_WAIT);
}

void CACHE_wbInvL2(void *blockPtr,Uint32 byteCnt,int wait)
{
	volatile Uint32 *p;
	register int t,a;
	p=(Uint32 *)0x01844010;
	a=(Uint32)blockPtr;
	t=byteCnt;
	DEC6713_wait(8);
	p[0]=a;

	p[1]=t;
	DEC6713_wait(5000);
}

