#include<dec6713.h>
#include<stdio.h>
#include<stdlib.h>

Uint32 *Src_StartAdd;
Uint32 TempData;
extern far void vectors();

int main()
{
	Uint32 i;

	Src_StartAdd = (Uint32 *)0x80000000;

	/* Initialize DSK6713 board. */
	DEC6713_Init();

	/* Write data in the whole chip. */
	for(i=0;i<0x400000;i++)
	{
		*(Src_StartAdd++) = i;
	}

	printf("\nFinish writing Source data.");

	Src_StartAdd = (Uint32 *)0x80000000;

	/* Read data from Dst_StartAdd. */
	for(i=0;i<0x400000;i++)
	{
		TempData = *(Src_StartAdd++);
		if(TempData != i)
		{
			printf("\nTesting is failure!");
			printf("\nAddress 0x%x is error!", i);
			exit(0);
		}
		else continue;
	}
	printf("\nTesting is success!");
}
