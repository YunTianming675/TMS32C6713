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
#define GPINT4ID 4       //定时器中断
#define GPINT5ID 5
#define GPINT6ID 6
#define GPINT7ID 7
#define EDMAINTID 8
#define EMUDTDMAID 9
#define SDINTID 3
#define EMURTDXRXID 10
#define EMURTDXTXID 11
#define DSPINTID 0
#define TINT0ID 1
#define TINT1ID 2

#define XINT0ID 12
#define XINT1ID 14
#define RINT0ID 13
#define RINT1ID 15
#define GPINT0ID 16
#define I2CINT0ID 22
#define I2CINT1ID 23
#define AXINT0ID 28
#define AXINT1ID 30
#define ARINT0ID 29
#define ARINT1ID 31

#define MUX_ADDR 0x019c0000   //起始地址
#define MUXH 0    //偏移地址
#define MUXL 1

#define TIM0_ADDR 0x01940000
#define TIM1_ADDR 0x01980000
#define TIMCTL 0
#define PRD 1
#define CNT 2

typedef struct
{
	Uint32 TimerEvent;
	Uint32 *base_addr;
}TIMER_Handle;

void *IRQ_setVecs(void *vecs);     /* point to the IRQ vector table	*/
//void IRQ_globalEnable();       /* Globally enable interrupts       */
//void IRQ_nmiEnable();          /* Enable NMI interrupt             */

#endif /* IRQ_H_ */
