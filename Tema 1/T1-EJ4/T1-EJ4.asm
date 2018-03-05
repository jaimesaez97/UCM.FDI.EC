// EJERCICIO 3
.extern swap
.global start
.EQU N,16
.data
A:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16

.bss

swap:

.text
start:
		LDR R4, =A
		MOV R6, #0	@ R6 <- i
		MOV R7, #0	@ R7 <- j
	b1:
		CMP R6, #N
		BGE b1_end

		MOV R8, #N
		SUB R8, R8, R6	@ R8 <- N - i
	b2:
		CMP R7, R8
		BGE b2_end

		// LLAMADA A SWAP(V[j], V[i])

		ADD R7, R7, #1
		ADD R6, R6, #1	@ ++i
	b2_end:
		MOV R7, #0
		b b1
	b1_end:


		B .
		.end






