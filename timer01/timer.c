#include <stdio.h>
#include <dec6713.h>
#include <c6x.h>
#include <irq.h>
#include <stdlib.h>

#define TIMER_CNT  20  		/* Maximum count value */

extern far void vectors();

Uint32 *mux_addr=(Uint32 *)MUX_ADDR,*timer_base=(Uint32 *)TIM1_ADDR;

static Uint32 cnt = 0;

void main()
{
	register int x3,x2,x1;

	DEC6713_init();
	x1=TINT1;

	IRQ_setVecs(vectors);
	x3 = CSR;    //开全局中断
 	x3 |= 1;
 	CSR = x3;
 	x3 = IER;   //不可屏蔽中断开
  	x3 |= 2;
  	IER = x3;
  	x3 = mux_addr[0];
  	x3 &= 0xfffc1fff;
  	x3 |= 0x00400000;
  	mux_addr[0] = x3;//映射中断14

  	x3 = IER;  //中断14不使能
  	x3 &= ~x1;
  	IER = x3;
  	ICR = x1;//清除中断14
	x1 = timer_base[0];//设置ctl定时控制寄存器
	x1 &= 0xfffffbff;
	x1 |= 0x00000200;//选择内部时钟
	x1 |= 0x00000080;//允许计数
	x1 &= 0xffffffbf;
	x1 |= 0x00000010;
	x1 &= 0xfffffffb;
	x1 &= 0xfffffffd;
	x1 |= 1;
	x2 = 0x00000b72;
	x3 = 0;
	timer_base[0] = x1;
	timer_base[1] = x2;//时钟周期的数量
	timer_base[2] = x3;//从0开始

	x1 = IER;
	x1 |= 0x4000;
	IER = x1;//中断14使能
	x1 = timer_base[0];//启动定时器
	x1 |= 0x00000080;
	x1 |= 0x00000040;
	timer_base[0] = x1;

	while(cnt <= TIMER_CNT); /* waiting for interrupt*/
//  while(1);
}

void TimerEventHandler(void)
 {
	register int x;
  /* process timer event here */
  cnt++;

  if (cnt > TIMER_CNT)
  {
	  x=timer_base[0];
	  x&=0x00000080;
	  timer_base[0]=x;
      printf("\nDone...");
      exit(0);
  }
  printf("\n Count : %3d ",cnt);


}

/************************************************************************\
 name:      Interrupt Service Routine c_int14

 purpose:   ISR to service TIMERINT1.
            vecs.asm must be modified to include
            c_int14 entry.

 inputs:    n/a

 returns:   n/a
\************************************************************************/
interrupt void
c_int14(void)
{
    TimerEventHandler();
    return;

} /* end c_int14 */

/******************************************************************************\
* End of DEC6713_TIMER.c
\******************************************************************************/
