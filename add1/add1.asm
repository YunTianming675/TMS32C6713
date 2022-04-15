		.global _c_int00
		.bss x, 8
		.bss y, 8
		.data
dx_1:	.word 45, 36
		.text
_c_int00:
			MVK	.S1 x, A0
			MVK .S1 y, A1
			MVK .S1 dx_1, A3
			LDW .D1 *A3++, A2
			NOP 5
			
			STW .D1 A2, *A0++
			NOP 5
			
			LDW .D1 *A3, A2
			NOP 5
			
			STW .D1 A2, *A0
			NOP 5
			
			MVK .S1 x, A0
			LDW .D1 *A0++, A8
			NOP 5
			
			LDW .D1 *A0, A9
			ADD .L1 A8, A9, A10
			STW .D1 A10, *A1++
			MPY .M1 A8, A9, A11
			STW .D1 A11, *A1
			NOP 5
			.end
