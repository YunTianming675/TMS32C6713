		.global _c_int00
		.bss val_1, 8
		.bss val_2, 16
		.bss val_3, 8
		.data
data_1: .word 291, -60000
		.text
_c_int00:
		MVK 	.S1 val_1 		, A0	;A0是RAM中val_1的地址
		MVK 	.S1 val_2		, A1	;address val_2
		MVK 	.S1 data_1		, A3	;
		LDW 	.D1 *A3++		, A2	;将A3地址里的值放到A2
		NOP		5
		STW 	.D1 A2 			, *A0++ ;将A2的值放到A0的地址
		NOP 	5
		LDW 	.D1 *A3			, A2	;
		NOP 	5
		STW 	.D1 A2			, *A0
		NOP 	5
		MVK 	.S1 val_1		, A0
		LDW 	.D1 *A0++		, A8
		NOP     5
		LDW 	.D1 *A0			, A9
		NOP 	5
		;判断A8是否是有符号数
		SHR 	.S1 A8, 31		, A10
		MVK 	.S1 0xFFFFFFFF  , A11
		CMPEQ	.L1 A10, A11	, A6
		MVK 	.S1 val_3		, A0
		STW 	.D1 A6			, *A0
		NOP		5
		LDW		.D1T2 *A0		, B0
		NOP 	5
	[B0]B		.S2 SIGN
		NOP 	5
		;判断A9是否是有符号数
		SHR		.S1 A9, 31		, A10
		CMPEQ	.L1 A10, A11	, A6
		STW 	.D1 A6			, *A0
		NOP 	5
		LDW 	.D1T2 *A0		, B0
		NOP 	5
	[B0]B		.S2 SIGN
		NOP 	5

		;MPYID   .M1 A8, A9		, A5:A4
		MPY 	.M1 A8, A9		, A10	;A8与A9低16位的乘积
		NOP 	8
		SHRU	.S1 A9, 16		, A9
		MPY 	.M1 A8, A9		, A11	;A8低16位与A9高16位的乘积
		NOP 	8
		LDW 	.D1 *A3			, A9	;重新将数字加载到A9
		NOP 	5
		SHRU	.S1 A8, 16		, A8
		MPY 	.M1 A8, A9 		, A12	;A8高16位与A9低16位的乘积
		NOP 	8
		SHRU	.S1 A9, 16		, A9
		MPY 	.M1 A8, A9		, A13	;A8与A9高16位的乘积
		NOP 	8
		;在移位调整前先保存、计算进位
		MV		.L1 A11			, A5
	||	MV  	.S1 A12			, A4
		SHRU	.S1 A5, 16		, A5
		SHRU	.S1 A4, 16		, A4
		ADD 	.L1 A5, A4		, A5
		ADD 	.L1 A5, A13		, A13

		SHL 	.S1 A11, 16		, A11	;移位调整
		SHL 	.S1 A12, 16		, A12
		ADD 	.L1 A10, A11	, A11
		ADD 	.L1 A11, A12	, A12
		MVK		.S1 val_1		, A0
		STW 	.D1 A13 		, *A0++
		STW 	.D1 A12			, *A0
		B		.S2 END
		NOP 	5
		NOP 	5
		NOP 	5
SIGN:
		MPY		.M1 A8, A9		, A10
		NOP 	5
		SHR 	.S1 A9, 16		, A9
		MPY 	.M1 A8, A9		, A11
		NOP		5
		LDW 	.D1 *A3			, A9
		NOP 	3
		SHR 	.S1 A8, 16		, A8
		MPY 	.M1 A8, A9		, A12
		NOP 	5
		SHR		.S1 A9, 16		, A9
		MPY		.M1 A8, A9		, A13
		;移位前先保存，移位时保留扩展符号
		MV		.L1 A11			, A5
	||	MV  	.S1 A12			, A4
		NOP 	5
		SHR 	.S1 A5, 16		, A5
		SHR 	.S1 A4, 16		, A4
		ADD 	.L1 A5, A4		, A5
		ADD 	.L1 A5, A13		, A13

		SHL 	.S1 A11, 16		, A11	;移位调整
		SHL 	.S1 A12, 16		, A12
		ADD 	.L1 A10, A11	, A11
		ADD 	.L1 A11, A12	, A12
		MVK		.S1 val_1		, A0
		STW 	.D1 A13 		, *A0++
		STW 	.D1 A12			, *A0
END:
		NOP 	5
		NOP 	5
		NOP 	5
		NOP 	5
		.end
