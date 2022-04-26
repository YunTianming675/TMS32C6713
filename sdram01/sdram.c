#include<dec6713.h>
#include<stdio.h>
#include<stdlib.h>

Uint32 *Src_StartAdd;
Uint32 *Dst_StartAdd;
Uint32 *Src_EndAdd;
Uint32 *Dst_EndAdd;
Uint32 TempData;
Uint32 DataBuff[2048]={0};
Uint32 ReceiveData[2048] = {0};

int main()
{
	Uint32 i;

	Src_StartAdd = (Uint32 *)0x80000000;
	Dst_StartAdd = (Uint32 *)0x801FF000;
	Src_EndAdd = (Uint32 *)0x80000FFC;
	Dst_EndAdd = (Uint32 *)0x801FFFFC;

	DEC6713_init();

	for(i=0;i<0x400000;i++)
	{
		*(Src_StartAdd++) = i;
	}

	printf("\nFinish writing Source data.");

	Src_StartAdd = (Uint32 *)0x80000000;

	for(i=0;i<0x400000;i++)
	{
		TempData = *(Src_StartAdd ++);
		if(TempData != i)
		{
			printf("\nTesting is failure");
			exit(0);
		}
		else continue;
	}
	printf("\nTesting is success");
}
