#ifndef IRQ_H_
#define IRQ_H_

#include<dec6713.h>
#include<c6x.h>

#define DSPINTID	0
#define TINT0ID		1
#define TINT1ID 	2
#define SDINTID 	3
#define GPINT4ID 	4
#define GPINT5ID 	5
#define GPINT6ID 	6
#define GPINT7ID 	7
#define EDMAINTID 	8
#define EMUDTDMAID 	9
#define EMUDTXRXID 	10
#define EMUDTXTXID 	11
#define XINT0ID 	12
#define RINT0ID 	13
#define XINT1ID 	14
#define RINT1ID 	15
#define GPINT0ID 	16
#define I2CINT0ID 	22
#define I2CINT1ID 	23
#define AXINT0ID 	28
#define ARINT0ID 	29
#define AXINT1ID 	30
#define ARINT1ID 	31
#define MUXADDR 	0x019C0000
#define TIM0ADDR 	0x01940000
#define TIM1ADDR 	0x01980000
#define MUXH 		0
#define MUXL 		1
#define EXTPOL 		2
#define CTL 		0
#define PRD 		1
#define CNT 		2

void IRQ_setVecs(void *vecs);

#endif
