// EJERCICIO 2
.global start
.EQU N,10
.data
A:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
B: 	.word 4, 5, 6, 7, 8, 9, 10, 11, 12, 13

.bss
C:	.space 4*N


.text


start:
		LDR R4, =A
		LDR R5, =B
		LDR R9, =C
		MOV R6, #0	@ r2 <- i
	b1:
		CMP R6, #N
		BGE b1_end

		LDR R7, [R4, R6, LSL #2]	@ R7 <- A[i]
		MOV R8, #9
		SUB R8, R8, R6				@ R8 <- (9-i)
		LDR R8, [R5, R8, LSL #2]			@ R8 <- B[(9-i)]

		ADD R0, R7, R8				@ R7 <- A[i] + B[9-i]
		BL abs						@ R0 <- RESULTADO

		STR R0, [R9, R6, LSL #2]	@ C[i] <- ABS
		ADD R6, R6, #1

		B b1

	b1_end:
		B .
		.end

abs:	push{R4-R10, LR}
		//carga registros
		MOV R4, R0				@ R4 <- A[i] + B[9-i]


	if1:
		CMP R4, #0
		BGE if1_end

		MOV R5, #0
		SUB R0, R5, R4

		B if1_end

	if1_end:
		MOV RO, R4


		POP {R4-R10, LR}
		MOV PC, LR

	// subrutinas


