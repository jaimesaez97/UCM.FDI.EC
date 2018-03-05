/*-----------------------------------------------------------------
		Workspace ejercicios 1 - 5
*---------------------------------------------------------------*/

// EJERCICIO 1
.global start
.EQU N,32
.data
A:	.word 1, 2, 3, 4, 5, 6 @hasta 32

.bss
B:	.space 4*N


.text

start:
		LDR r0, =A
		LDR r1, =B
		MOV R2, #0	@ r2 <- i
	b1:
		CMP R2, #32
		BGE b1_end

		LDR R3, [R0, R2, LSL #2]	@ R3 <- A[i]
		AND R4, R3, #0x00000001
	if1:
		CMP R4, #0
		BNE else1

		ADD R3, R3, #5	@ A[i] += 5
		B if1_end

	else1:
		MOV R4, #2
		MUL R5, R3, R4
		MOV R3, R5

	if1_end:
		STR R3, [R1, R2, LSL #2]
		ADD R2, R2, #1
		B b1

	b1_end:
		B .
		.end
