/*********************************************************************************
* Copyright	2003 by SEED Electronic Technology Ltd.
* All rights reserved. Property of SEED Electronic Technology Ltd.			                *
* Designed by:	Hongshuai.Li								                                *
*********************************************************************************/
/* FILENAME...... DEC6713_EDMA.c
* DATE CREATED.. 21/12/2004
* LAST MODIFIED. 21/12/2004
*------------------------------------------------------------------------------
* This program uses the timer to trigger EDMA events. These events in turn
* trigger linked EDMA parameter tables to fill a ping pong buffer structure.
* On running the program you'll note that the program bounces between the ping
* and pong buffers filling each with a value that comes from the source.
* (Note: This example runs with CACHE enable).
\******************************************************************************/
#include <stdio.h>
#include <csl_cache.h>
#include <dec6713.h>
#include <irq.h>
#include <edma.h>
#include <c6x.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------*/
/* Pick which EDMA transfer completion interrupt we want to use */
#define TCCINTNUM   10

/* define the constants */
#define BUFF_SZ      256              /* ping-pong buffer sizes in # of ints  */
#define FCPU         150000000        /* CPU clock frequency                  */
#define SRATE        8000             /* data sample rate (simulated w/timer  */
#define TPRD         (FCPU/(4*SRATE)) /* timer period                         */
#define TRANSFER_CNT 20               /* Transfer count */

/* Create the buffers. We want to align the buffers to be cache friendly */
/* by aligning them on an L2 cache line boundary.                        */
#pragma DATA_ALIGN(ping,128);
#pragma DATA_ALIGN(pong,128);
#pragma DATA_ALIGN(outbuff,128);
int ping[BUFF_SZ];
int pong[BUFF_SZ];
int outbuff[BUFF_SZ];
volatile int sp[1100];
/* These two variables serve as the data sources for this example. */
/* Also want to align these on a cache line boundary since they    */
/* sources of EDMA transfers.                                      */
#pragma DATA_ALIGN(ping_data,128);
#pragma DATA_ALIGN(pong_data,128);
static int ping_data;
static int pong_data;

/* global variable used to track the ping-pong'ing */
static int pingpong = 0;

volatile int transferCount = 0;
volatile Uint32 *pram_base,*esel_base,*edmar_base;
extern far void vectors();

void setupInterrupts(void);
void stopEdma(void); /* function used to stop EDMA */
void CACHE_clean1(Uint32 region,void *addr,Uint32 wordCnt);
void CACHE_wbInvL2(void *blockPtr,Uint32 byteCnt,int wait);
//typedef unsigned int Uint32;
//typedef unsigned short Uint16;
//typedef unsigned char Uint8;
//typedef int Int32;
//typedef short Int16;
//typedef char Int8;
/*-------------------------------------------------------------------------*/
/* declare the CSL objects */
//TIMER_Handle hTimer;   /* Handle for the timer device                 */
//EDMA_Handle hEdma;     /* Handle for the EDMA channel                 */
//EDMA_Handle hEdmaPing; /* Handle for the ping EDMA reload parameters  */
//EDMA_Handle hEdmaPong; /* Handle for the pong EDMA reload parameters  */
//EDMA_Config cfgEdma;   /* EDMA configuration structure                */
Uint32 *mux_addr=(Uint32 *)MUXADDR,*timer_base=(Uint32 *)TIM1ADDR;
//EDMA_Handle hEdma;     /* Handle for the EDMA channel                 */
Uint32 *edma_addr=(Uint32 *)EDMAADDR;
Uint32 *edma_Ping=(Uint32 *)EDMAPING;
Uint32 *edma_Pong=(Uint32 *)EDMAPONG;
Uint32 *edma_hEdma=(Uint32 *)EDMABASE;
//Uint32 *esel_base=(Uint32 *)EDMAESEL;//0x01A0FF00
/* Create the EDMA configuration structure for ping transfers */

/*----------------------------------------------------------------------------*/
void main(){
  register int x1,x2,x3,x4,x5,x6;
  register int y1,y2,y3,y4,y5,y6;
  register int t,t1,t2;
  volatile Uint32 *p1,*p2,*p3;
  /*Set the CCFG register of Cache to default value*/
  *(int *)0x01840000 = (*(int *)0x01840000 & 0x00000000); //地址里面的值清0
  /*Set the CCFG register of Cache to default value*/
  x1=edma_Ping[OPT];
  x2=edma_Ping[SRC];
  x3=edma_Ping[CNT];
  x4=edma_Ping[DST];
  x5=edma_Ping[IDX];
  x6=edma_Ping[RLD];
  x1=0x403a0002;    //OPT 通道选择状态：低优先，32位，1维，源地址固定，  目的地址1维，自增，TCINT置1链路连接  TCC=10, LINK=1 链路使能  ，FS=0
                    //31-29 PRI=010  低优先级传输
                    //28-27 ESIZE=00 32位
                    //26    2DS=0    1维
                    //25-24 SUM=0    源地址固定
                    //23    2DD=0    1维
                    //22-21 DUM=01   目的地址自增
                    //20    TCINT=1  链路连接
                    //19-16 TCC=1010=10(D)
                    //15-2  X
                    //1     LINK=1   链路使能
                    //0     FS=0
  x2=(Uint32)(&ping_data);//SRC
  x3=BUFF_SZ;             //传递个数256
  x4=(Uint32)ping;  //目的地址是该数组的首地址
  x5=0x00000004;    //自增索引值=4   每4个自增一个  一个字
  x6=0x00000000;    // x6 RLD先不赋值
  edma_Ping[OPT]=x1;
  edma_Ping[SRC]=x2;
  edma_Ping[CNT]=x3;
  edma_Ping[DST]=x4;
  edma_Ping[IDX]=x5;
  edma_Ping[RLD]=x6;


  y1=edma_Pong[OPT];
  y2=edma_Pong[SRC];
  y3=edma_Pong[CNT];
  y4=edma_Pong[DST];
  y5=edma_Pong[IDX];
  y6=edma_Pong[RLD];
  y1=0x403a0002;
  y2=(Uint32)(&pong_data);
  y3=BUFF_SZ;
  y4=(Uint32)pong;  //目的地址是该数组的首地址
  y5=0x00000004;    //自增索引值=4   每4个自增一个  一个字
  y6=0x00000000;
  edma_Pong[OPT]=y1;
  edma_Pong[SRC]=y2;
  edma_Pong[CNT]=y3;
  edma_Pong[DST]=y4;
  edma_Pong[IDX]=y5;
  edma_Pong[RLD]=y6;

  /* initialize the CSL library */
//  CSL_init();

  /* Initialize DEC6713 board */
  DEC6713_init();
  /* initialize the input source data */
  ping_data=0x00000000;
  pong_data=0x80000000;

  /* Since these variables are the source of an EDMA transfer, we     */
  /* need to flush them out of the cache since we just wrote to them. */
  CACHE_wbInvL2(&ping_data, 4, CACHE_WAIT);
  CACHE_wbInvL2(&pong_data, 4, CACHE_WAIT);

  /* Let's disable/clear related interrupts just in case they are pending */
  /* from a previous run of the program.                                  */
  setupInterrupts();  /* defined below */

  /* Although not required, let's clear all of the EDMA parameter RAM. */
  /* This makes it easier to view the RAM and see the changes as we    */
  /* configure it.                                                     */
//  EDMA_clearPram(0x00000000);
   for(p1=(Uint32 *)0x01a00000,t=0;t<=0x8000>>2;t++) //16个通道的参数都放在这里，清零
   {
	   p1[t]=y6;
   }
  /* Let's open up a timer device, we'll use this to simulate input events */
  /* at a given sample rate.                                                */
  //hTimer = TIMER_open(TIMER_DEV1, TIMER_OPEN_RESET);

  /* Lets open up the EDMA channel associated with timer #1. */
 // hEdma = EDMA_open(EDMA_CHA_TINT1, EDMA_OPEN_RESET);
  esel_base=(volatile Uint32 *)0x01a0ff00; //ESEL0地址
  t=esel_base[0];    //通道2 EVTSEL2=2  TINT1
  t&=0xffc0ffff;
  t|=0x00020000;
  esel_base[0]=t;
  /* We also need two EDMA reload parameter sets so let's allocate them */
  /* here. Notice the -1, this means allocate any availale table.        */
//  hEdmaPing = EDMA_allocTable(-1);
//  hEdmaPong = EDMA_allocTable(-1);

  /* Let's copy the ping reload configuration structure to an */
  /* intermediate configuration structure.                    */
//  cfgEdma = cfgEdmaPing;
  /* Now let's program up the EDMA channel with the configuration structure */
//  EDMA_config(hEdma, &cfgEdma);
  /* Let's also configure the reload parameter tables in the EDMA PRAM */
  /* with the values in the configuration structures.                  */

  pram_base=(volatile Uint32 *)(PRAMADDR+2*6*4); //00+48=30H  Event2 地址
  pram_base[0]=x1;
  pram_base[1]=x2;
  pram_base[2]=x3;
  pram_base[3]=x4;
  pram_base[4]=x5;
  pram_base[5]=(PRAMADDR+10*6*4)&0x0000ffff;//运行先pong再ping
  p1=&pram_base[5];

  //  EDMA_config(hEdmaPing, &cfgEdmaPing);
  pram_base=(volatile Uint32 *)(PRAMADDR+8*6*4); //48*4=C0H,8里面装ping
  t1=(Uint32)pram_base;
  pram_base[0]=x1;
  pram_base[1]=x2;
  pram_base[2]=x3;
  pram_base[3]=x4;
  pram_base[4]=x5;
  pram_base[5]=x6;
  p2=&pram_base[5];

  //  EDMA_config(hEdmaPong, &cfgEdmaPong);
  pram_base=(volatile Uint32 *)(PRAMADDR+10*6*4);//240=F0H  10里面装pong
  t2=(Uint32)pram_base;
  pram_base[0]=y1;
  pram_base[1]=y2;
  pram_base[2]=y3;
  pram_base[3]=y4;
  pram_base[4]=y5;
  pram_base[5]=y6;
  p3=&pram_base[5];
  /* Let's initialize the link fields of the configuration structures */
  *p1=t2;
  *p2=t1;
  *p3=t2;
//  cfgEdmaPing.rld = EDMA_RLD_RMK(0,hEdmaPing);
//  cfgEdmaPong.rld = EDMA_RLD_RMK(0,hEdmaPong);
//  cfgEdma.rld     = EDMA_RLD_RMK(0,hEdmaPong);



  p1=(volatile Uint32 *)0x01980000;
  p1[0]=0x00000200;
  p1[1]=TPRD;
  p1[2]=0;
  /* Configure up the timer. */
//  TIMER_configArgs(hTimer,
//    TIMER_CTL_OF(0x00000200),
//    TIMER_PRD_OF(TPRD), /* timer period  */
//    TIMER_CNT_OF(0)
//  );
	x1=timer_base[0];
	x1&=0xfffffbfff;
	x1|=0x00000200;
	x1|=0x00000080;
	x1&=0xffffffbf;
	x1|=0x00000010;
	x1&=0xfffffffb;
	x1&=0xfffffffd;
	x1|=1;
	x2=0x00000b72;
	x3=0;
	timer_base[0]=x1;
	timer_base[1]=x2;
	timer_base[2]=x3;
  /* Enable the related interrupts */


//  EDMA_intClear(TCCINTNUM);

  t=IER;
  t|=1<<8;
  IER=t;   //   IE8
  //  IRQ_enable(IRQ_EVT_EDMAINT);
  edmar_base=(volatile Uint32 *)0x01a0ffe0; //PQSR
  t=edmar_base[CIER];
  t&=~(1<<TCCINTNUM);   //disabled INT10
  edmar_base[CIER]=t;
  //  EDMA_intDisable(TCCINTNUM);
  t=edmar_base[CIPR];
  t&=~(1<<TCCINTNUM);   //悬浮10通道中断
  edmar_base[CIPR]=t;
  //  EDMA_intEnable(TCCINTNUM);
  t=edmar_base[CIER];
  t|=(1<<TCCINTNUM);    //使能10号中断
  edmar_base[CIER]=t;
  /* Enable the EDMA channel */
  edmar_base=(volatile Uint32 *)0x01a0ffe0;
  t=edmar_base[EER];
  t|=1<<2;
  edmar_base[EER]=t;   //EDMA 事件2 使能

//EDMA_enableChannel(hEdma);
  t=edma_addr[CCER];
  	t|=0x00000004;
  	edma_addr[CCER]=y3;
  	t=edma_addr[ECR];
  	t|=0x00000004;
  	edma_addr[ECR]=y3;
    /* Finally, enable the timer which will drive everything. */
    //TIMER_start(hTimer);
  	x1=timer_base[0];
  	x1|=0x00000080;
  	x1|=0x00000040;
  	timer_base[0]=x1;


  while(transferCount <= TRANSFER_CNT); /* waiting for interrupts */
}

/*----------------------------------------------------------------------------*/
void processbuff(int arg){

  int *inbuff;
  int x;
  printf("\n %2d -",transferCount);
  if (pingpong){

    /* If pingpong is 0, then we own the ping input buffer */
    inbuff = ping;
    printf(" Ping ");

  }else{

    /* If pingpong is 1, then we own the pong input buffer */
    inbuff = pong;
    printf(" Pong " );

  }

  transferCount++;
  /* Now let's process the input buffer, for simplicity, we'll */
  /* just copy it to the output buffer.                        */
  for (x=0; x<BUFF_SZ; x++) {
    outbuff[x] = inbuff[x];
  }

  /* If this example is enhanced to actually do something with the  */
  /* output buffer such as DMA it somewhere, you will want to flush */
  /* it out of the cache first.                                     */
   CACHE_wbInvL2(outbuff, (BUFF_SZ << 2), CACHE_WAIT);


  /* Since we're done processing the input buffer, clean it from cache, */
  /* this invalidates it from cache to ensure we read a fresh version   */
  /* the next time.                                                     */
   CACHE_clean(CACHE_L2,inbuff,(BUFF_SZ << 2));
}
/*----------------------------------------------------------------------------*/

/************************************************************************\
 name:      SetInterruptsEdma

 purpose:   Sets up interrupts to service EDMA transfers

 inputs:    void

 returns:   void
\************************************************************************/
void setupInterrupts(void)
{
	register int t;
	volatile Uint32 *p;

     IRQ_setVecs(vectors);     /* point to the IRQ vector table	*/

     t=IER;
     t|=1<<1;
     IER=t;
//     IRQ_nmiEnable(); 打开不可屏蔽中断
     t=CSR;
     t|=1;
     CSR=t;
//     IRQ_globalEnable(); 使能全局中断
     p=(volatile Uint32*)0x019c0000;
     t=p[MUXL];
     t&=0xfc1fffff;
     t|=8<<21;
     p[MUXL]=t;
//     IRQ_map(IRQ_EVT_EDMAINT, 8);
     t=IER;            //不论哪个通道中断 最终都由8决定
     t&=~(1<<8);
     IER=t;            //清零复位
//     t=ICR;
//     t|=1<<8;
     t=8;
     ICR=t;

//     IRQ_reset(IRQ_EVT_EDMAINT);
     //	EDMA产生的中断
} /* End of SetInterruptsEdma() */


/************************************************************************\
 name:      Interrupt Service Routine c_int08

 purpose:   ISR to service EDMAINT. vecs.asm must be modified to include
            c_int08 entry.

 inputs:    n/a

 returns:   n/a
\************************************************************************/
interrupt void
c_int08(void)
{
	register int t;
	volatile Uint32 *p1;
	p1=(Uint32 *)0x01980000;
  /* Clear the pending interrupt from the EDMA interrupt pending register */
//  EDMA_intClear(TCCINTNUM);
    t=edmar_base[CIPR];
    t&=~(1<<TCCINTNUM);
    edmar_base[CIPR]=t;
  /* Perform ping-pong */
  pingpong = (pingpong + 1) & 1;

  /*Exit from the program if certain no of transfres are done*/
  if (transferCount >= TRANSFER_CNT)
  {
//      TIMER_pause(hTimer);
	  t=p1[0];
	  t&=~(1<<7);
	  p1[0]=t;
      stopEdma();
      //      TIMER_close(hTimer);
      t=p1[0];
      t&=~(1<<6);
      p1[0]=t;

      printf ("\nDone.....");
      exit(0);
  }

  /* Based on if we ping'ed or pong'ed, we need to set the EDMA channel */
  /* link address for the NEXT frame.                                   */
	if (pingpong){
    /* Currently doing pong so setup next frame for ping */

    /* Modify the input data source, this just simulates */
    /* the input data changing.                          */
    ping_data++;

    /* Rememer to flush this variable out of the cache */
    /* since it's the source of an EDMA transfer       */
    CACHE_wbInvL2(&ping_data, 4, CACHE_WAIT);

    /* Now filling pong so set link to ping */
//    EDMA_link(hEdma,hEdmaPing);
    *(int *)0x01a00044 = 0x01a000c0 & 0x0000ffff;

  }else{
    /* Currently doing ping so setup next frame for pong */

    /* Modify the output data source, this just simulates */
    /* the input data changing.                           */
    pong_data++;

    /* Rememer to flush this variable out of the cache */
    /* since it's the source of an EDMA transfer       */

    CACHE_wbInvL2(&pong_data, 4, CACHE_WAIT);
    /* Now filling ping so set link to pong */

//    EDMA_link(hEdma,hEdmaPong);
    *(int *)0x01a00044 = 0x01a000f0 & 0x0000ffff;
  }
  processbuff(0);
  return;

} /* end c_int08 */


/************************************************************************\
 name:      stopEdma

 purpose:   Stops the EDMA service.

 inputs:    void

 returns:   void
\************************************************************************/
void stopEdma(void) {
register int x1,x2,x3;
    /*Disable interrupts, close EDMA channel before exit of the program*/
    //IRQ_disable(IRQ_EVT_EDMAINT);
    x1=EDMAINTID;
    x3=IER;
    x3&=~x1;
    IER=x3;
    ICR=x1;

    //EDMA_RSET(CCER,0x00000000);
    x1=edma_addr[CCER];
    x1&=0;
    edma_addr[CCER]=x1;

    //EDMA_disableChannel(hEdma);
    x3=edma_addr[EER];
    x3&=0xfffffffb;
    edma_addr[EER]=x3;

    //EDMA_intDisable(TCCINTNUM);
    x3=edma_addr[CIER];
    x3&=0xfffffbff;
    edma_addr[CIER]=x3;

    //EDMA_intClear(TCCINTNUM);
    x3=edma_addr[CIPR];
    x3|=0x00000000;
    edma_addr[CIPR]=x3;

 	//EDMA_close(hEdma);
 	x1=esel_base[0];
 	x1|=0xfffdffff;
 	esel_base[0]=x1;

    //EDMA_resetAll();

 	//EDMA_RSET(CIPR,0xFFFFFFFF);
 	x3=edma_addr[CIPR];
 	x3=0;
 	edma_addr[CIPR]=x3;

 	//EDMA_RSET(ECR,0xFFFFFFFF);
    x2=edma_addr[ECR];
    x2|=0;
    edma_addr[ECR]=x2;
}

/******************************************************************************\
* End of main.c
\******************************************************************************/
