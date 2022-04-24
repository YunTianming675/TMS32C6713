/********************************************************************************\
\*  DEC6713_TIMER.c	V1.00													    *\

\*  Copyright 2004 by SEED Electronic Technology LTD.                           *\
\*  All rights reserved. SEED Electronic Technology LTD.                        *\
\*  Restricted rights to use, duplicate or disclose this code are               *\
\*  granted through contract.    											    *\

\*	Designed by: Hongshuai.Li												    *\
\********************************************************************************/

/********************************************************************************\
\*		The example generate a square wave on TOUT0 with certain frequency. You
	can observe the square wave with oscillograph, and can also get some messages
	in the watch windows. *\
\********************************************************************************/

//#include <csl.h>
//#include <csl_timer.h>
//#include <csl_irq.h>
#include <stdio.h>
#include <dec6713.h>
#include <c6x.h>
#include <irq.h>
#include <stdlib.h>

#define TIMER_CNT  20  		/* Maximum count value */

//void IRQ_setVecs(void *vectors);
//void TimerEventHandler(void);
extern far void vectors();
//Uint32 *timer_base,*mux_base;
Uint32 *mux_addr=(Uint32 *)MUX_ADDR,*timer_base=(Uint32 *)TIM1_ADDR;
//static TIMER_Handle hTimer1;
//static Uint32 TimerEventId;
static Uint32 cnt = 0;

/********************************************************************************/

/********************************************************************************/

void main()
{
	register int x3,x2,x1;
	//Uint32 *timer_base,*mux_base;

	/* Initialize CSL, must when using CSL. */
	//CSL_init();

	/* Initialize DEC6713 board. */
	DEC6713_init();
	/* Open TIMER1 device, and reset them to power-on default state. */
	x1=TINT1;
	//hTimer1 = TIMER_open(TIMER_DEV1,TIMER_OPEN_RESET);
	//hTimer1->TimerEvent=TINT1;
	//hTimer1->base_addr=(Uint32 *)TIM1_ADDR;
	/* Obtain the event ID for the timer device. */
	//TimerEventId =hTimer1->TimerEvent;

	IRQ_setVecs(vectors);     /* point to the IRQ vector table	*/
	x3=CSR;    //开全局中断
 	x3|=1;
 	CSR=x3;
 	//IRQ_globalEnable();       /* Globally enable interrupts       */
 	x3=IER;   //不可屏蔽中断开
  	x3|=2;
  	IER=x3;
 	//IRQ_nmiEnable();          /* Enable NMI interrupt             */

  	/* Map TIMER events to physical interrupt number */
  	//mux_base=(Uint32 *)MUX_ADDR;
  	x3=mux_addr[0];
  	x3&=0xfffc1fff;
  	x3|=0x00400000;
  	mux_addr[0]=x3;//映射中断14
 	//IRQ_map(TimerEventId, 14);

  	/* Reset the timer events. */
  	x3=IER;  //中断14不使能
  	x3&=~x1;
  	IER=x3;
  	ICR=x1;//清除中断14
	//IRQ_reset(TimerEventId);

	/* Configure the timer devices */
  	//TIMER_configArgs(hTimer1,
    //TimerControl, /* use predefined control value  */
    //0x00000B72,   /* set period                    */
    //0x00000000    /* start count value at zero     */
  	//);
	//timer_base=(Uint32*)MUXADDR;
	x1=timer_base[0];//设置ctl定时控制寄存器
	x1&=0xfffffbff;
	x1|=0x00000200;//选择内部时钟
	x1|=0x00000080;//允许计数
	x1&=0xffffffbf;
	x1|=0x00000010;
	x1&=0xfffffffb;
	x1&=0xfffffffd;
	x1|=1;
	x2=0x00000b72;
	x3=0;
	timer_base[0]=x1;
	timer_base[1]=x2;//时钟周期的数量
	timer_base[2]=x3;//从0开始

  /* Enable the timer events(events are disabled while resetting) */
  //IRQ_enable(TimerEventId);
  x1=IER;
  x1|=0x4000;
  IER=x1;//中断14使能
  /* Start the timers */
  //TIMER_start(hTimer1);
  x1=timer_base[0];//启动定时器
  x1|=0x00000080;
  x1|=0x00000040;
  timer_base[0]=x1;

  while(cnt <= TIMER_CNT); /* waiting for interrupt*/
//  while(1);
}
/********************************************************************************/
/********************************************************************************\
\*TimerEventHandler()	-Function called from TIMER1 ISR. Just increments the count by
  			one each time it enters this function. Exit from the program
  			after certain count value is reached.
\*Parameters: No.
\*Returns: No.
\********************************************************************************/
void TimerEventHandler(void)
 {
	register int x;
  /* process timer event here */
  cnt++;

  /* Exit from the program when certain count is reached */
  if (cnt > TIMER_CNT)
  {
	  x=timer_base[0];
	  x&=0x00000080;
	  timer_base[0]=x;
     // TIMER_pause(hTimer1);
     // TIMER_close(hTimer1);
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
