/*
 * edma.h
 *
 *  Created on: 2021-5-12
 *      Author: zjh
 */

#ifndef EDMA_H_
#define EDMA_H_

#include<DEC6713.h>
#include <c6x.h>
#define DSPINT     0
#define TINT0      1
#define TINT1      2
#define SDINT      3
#define EXTINT4    4
#define EXTINT5    5
#define EXTINT6    6
#define EXTINT7    7
#define EDMATCC8   8
#define EDMATCC9   9
#define EDMATCC10  10
#define EDMATCC11  11
#define XEVT0    12
#define REVT0    13
#define XEVT1    14
#define REVT1    15

#define OPT 0
#define SRC 1
#define CNT 2
#define DST 3
#define IDX 4
#define RLD 5

#define EDMABASE 0x01A00030 //Event 2 §ç§á§à§Ú
#define EDMAPING 0x01A001B0 //Reload Event N parameters with null parameters located at address 01A0 01B0h
#define EDMAPONG 0x01A001C8 //PING param
#define EDMAADDR 0x01A0FFE0
#define EDMAESEL 0x01A0FF00
#define PRAMADDR  0x01A00030
//#define ESEL0 0
//#define ESEL1 1
//#define ESEL3 3
#define PQSR  0
#define CIPR  1
#define CIER  2
#define CCER  3
#define ER    4
#define EER   5
#define ECR   6
#define ESR   7
#define PQSR 0
#define CIPR 1
#define CIER 2
#define CCER 3
#define ER 4
#define EER 5
#define ECR 6
#define ESR 7

#endif /* EDMA_H_ */
