		.global _c_int00
		.bss input, 2048
		.bss output, 2048
		.sect "fir_tab"
fir_start:
		.word -535, -639, -813, -965, -924
		.word -464, 657, 2637, 5575, 9430
		.word 13999, 18930, 23759, 27976, 31103
		.word 32767
fir_table 	.usect "fir_buff", 256
data_table 	.usect "data_buff", 256
		.text
_c_int00:
		ZERO	.S2 B0
		MVC 	.S2 B0				, AMR
		;在(*A0)=0x3000写入方波，一个周期32个点，共16个周期
		MVK 	.S2 16				, B0
	||	MVK 	.S1 1				, A0
		MVK 	.S1 -1				, A1
		MVK 	.S1 input			, A2
LOOP0:
		MVK 	.S2 16				, B1
LOOP1:
		STW		.D1 A0				, *A2++
		NOP 	3
		SUB 	.S2 B1, 1			, B1
	[B1]B		LOOP1
		NOP 	5
		MVK 	.S2 16				, B1
LOOP2:
		STW 	.D1 A1				, *A2++
		NOP 	3
		SUB 	.S2 B1, 1			, B1
	[B1]B		LOOP2
		NOP 	5
		SUB 	.S2 B0, 1			, B0
	[B0]B		LOOP0
		NOP 	5

		MVK 	.S1 fir_start		, A3	;0x2000
		MVK 	.S1 fir_table		, A4	;0x5500
		MVK 	.S1 data_table		, A5	;0x6600
	||	MVK 	.S2 64				, B0
	||	ZERO    .L1 A0
LOOP3:
		STW 	.D1 A0				, *A5++
		NOP 	3
		SUB 	.S2 B0, 1			, B0
	[B0]B		LOOP3
		NOP 	5
		MVK 	.S2 15				, B0
LOOP4:
		;写系数
		LDW 	.D1 *A3++			, A7
		NOP 	5
		STW 	.D1 A7				, *A4++
		NOP 	5
		SUB 	.S2 B0, 1			, B0
	[B0]B		LOOP4
		NOP 	5
		MVK 	.S2 16				, B0
LOOP5:
		LDW 	.D1 *A3--			, A7
		NOP 	5
		STW 	.D1 A7				, *A4++
		NOP 	5
		SUB 	.S2 B0, 1			, B0
	[B0]B		LOOP5
		NOP 	5
		MVK 	.S2 33				, B0
LOOP6:
		STW 	.D1 A0				, *A4++
		NOP 	5
		SUB 	.S2 B0, 1			, B0
	[B0]B		LOOP6
		NOP 	5
		MVKL	.S2 0x00000005		, B2
		MVKH	.S2 0x00070000		, B2
		MVC 	.S2 B2				, AMR	;bank=256
	||	MVK 	.S1 output			, A6	;0x3800
		MVK 	.S2 512				, B0
	||	MVK 	.S1 input			, A2	;0x3000
		MVK 	.S1 fir_table		, A4	;0x5500
		MVK 	.S1 data_table		, A5	;0x6600
LOOP7:
		MVK 	.S2 64				, B1
		LDW 	.D1 *A2++			, A8
		NOP 	5
		STW 	.D1 A8				, *--A5
		NOP 	5
LOOP8:
		LDW 	.D1 *A5++			, A9
		NOP 	5
		LDW 	.D1 *A4++			, A10
		NOP 	5
		MPY 	.M1 A9, A10			, A11
		NOP 	5
		ADD 	.L1 A11, A0			, A0
		SUB 	.S2 B1, 1			, B1
	[B1]B		LOOP8
		NOP		5
		STW 	.D1 A0				, *A6++
		NOP 	5
		SUB 	.L2 B0, 1			, B0
	[B0]B		LOOP7
		NOP 	5
		NOP 	5
		NOP 	5
		NOP 	5
		.end
