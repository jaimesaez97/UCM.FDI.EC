// EJERCICIO 3
.global start
.EQU N,4
.data
A:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16

.bss
B:	.space (4*N)*(4*N)


.text


start:
		LDR R4, =A
		LDR R5, =B
		MOV R6, #0	@ R6 <- i
		MOV R7, #0  @ R7 <- j

	b1: CMP R6, #N
		BGE b1_end

	b2: CMP R7, #N
		BGE b2_end

		MOV R10, #N

		MUL R8, R6, R10	@ R8 <- i * NCOLUMNAS
		ADD R8, R8, R7	@ R8 <- j + (i * NCOLUMNAS)

		MUL R9, R7, R10	@ R9 <- j * NCOLUMNAS
		ADD R9, R9, R6	@ R9 <- i + (j * NCOLUMNAS)

		LDR R0, [R4, R8, LSL #2]
		STR R0, [R5, R9, LSL # 2]

		ADD R7, R7, #1
		B b1

	b2_end:
		ADD R6, R6, #1
		MOV R7, #0
		B b1

	b1_end:
		B .
		.end






