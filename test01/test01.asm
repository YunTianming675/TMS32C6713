		.global _c_int00
		.bss val_1, 8
		.bss val_2, 16
		.bss val_3, 8
		.data
data_1: .word 291, -60000
		.text
_c_int00:
		MVK 	.S1 val_1 		, A0	;A0��RAM��val_1�ĵ�ַ
		MVK 	.S1 val_2		, A1	;address val_2
		MVK 	.S1 data_1		, A3	;
		LDW 	.D1 *A3++		, A2	;��A3��ַ���ֵ�ŵ�A2
		NOP		5
		STW 	.D1 A2 			, *A0++ ;��A2��ֵ�ŵ�A0�ĵ�ַ
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
		;�ж�A8�Ƿ����з�����
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
		;�ж�A9�Ƿ����з�����
		SHR		.S1 A9, 31		, A10
		CMPEQ	.L1 A10, A11	, A6
		STW 	.D1 A6			, *A0
		NOP 	5
		LDW 	.D1T2 *A0		, B0
		NOP 	5
	[B0]B		.S2 SIGN
		NOP 	5

		;MPYID   .M1 A8, A9		, A5:A4
		MPY 	.M1 A8, A9		, A10	;A8��A9��16λ�ĳ˻�
		NOP 	8
		SHRU	.S1 A9, 16		, A9
		MPY 	.M1 A8, A9		, A11	;A8��16λ��A9��16λ�ĳ˻�
		NOP 	8
		LDW 	.D1 *A3			, A9	;���½����ּ��ص�A9
		NOP 	5
		SHRU	.S1 A8, 16		, A8
		MPY 	.M1 A8, A9 		, A12	;A8��16λ��A9��16λ�ĳ˻�
		NOP 	8
		SHRU	.S1 A9, 16		, A9
		MPY 	.M1 A8, A9		, A13	;A8��A9��16λ�ĳ˻�
		NOP 	8
		;����λ����ǰ�ȱ��桢�����λ
		MV		.L1 A11			, A5
	||	MV  	.S1 A12			, A4
		SHRU	.S1 A5, 16		, A5
		SHRU	.S1 A4, 16		, A4
		ADD 	.L1 A5, A4		, A5
		ADD 	.L1 A5, A13		, A13

		SHL 	.S1 A11, 16		, A11	;��λ����
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
		;��λǰ�ȱ��棬��λʱ������չ����
		MV		.L1 A11			, A5
	||	MV  	.S1 A12			, A4
		NOP 	5
		SHR 	.S1 A5, 16		, A5
		SHR 	.S1 A4, 16		, A4
		ADD 	.L1 A5, A4		, A5
		ADD 	.L1 A5, A13		, A13

		SHL 	.S1 A11, 16		, A11	;��λ����
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
