/*
 * irq.h
 *
 *  Created on: 2021-4-14
 *      Author: bobo
 */

#ifndef IRQ_H_
#define IRQ_H_
#include<DEC6713.h>
#include<c6x.h>
#define GPINT4 4       //定时器中断
#define GPINT5 5
#define GPINT6 6
#define GPINT7 7
#define EDMAINT 8
#define EMUDTDMA 9
#define SDINT 3
#define EMURTDXRX 10
#define EMURTDXTX 11
#define DSPINT 0
#define TINT0 1
#define TINT1 2

#define XINT0 12
#define XINT1 14
#define RINT0 13
#define RINT1 15
#define GPINT0 16
#define I2CINT0 22
#define I2CINT1 23
#define AXINT0 28
#define AXINT1 30
#define ARINT0 29
#define ARINT1 31

#define MUXADDR 0x019C0000   //起始地址
#define MUXH 0    //偏移地址
#define MUXL 1

#define TIM0ADDR 0x01940000
#define TIM1ADDR 0x01980000
#define TIMCTL 0
#define PRD 1
#define CNT 2

typedef struct
{
	Uint32 TimerEvent;
	Uint32 *base_addr;
}TIMER_Handle;

void IRQ_setVecs(void *vecs);     /* point to the IRQ vector table	*/
//void IRQ_globalEnable();       /* Globally enable interrupts       */
//void IRQ_nmiEnable();          /* Enable NMI interrupt             */

#endif /* IRQ_H_ */
