// EJERCICIO 3


.global start
.EQU N,4
.data

@DA IGUAL EL ARRAY QUE METAMOS: SABEMOS QUE MAXIMO TENDRA 160B:
@ 10 structs de 16 bytes (2 num, 2*6 nota, 2 media)

A: 	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16	@ matriz tam 4x4
B: 	.word 1, 2, 3, 4											@ vector tam 4

.bss
C: 	.space (4*N)*(4*N)

.text
abs_escalar:

		PUSH {r4-r10, PC}
		MOV R4, R0	@ r4 <- =A
		MOV R5, R1	@ r5 <- =B
		MOV R6, R2  @ r6 <- n
		MOV R7, #0	@ r7 <- j
		MOV R10, #0	@ r10 <- C[i]
	b2:
		CMP R7, #N
		BGE b2_end

		@ no hay que sumarle a la direccion
		@ base de A i * NCOLUMNAS porque lo
		@ hemos adaptado al pasarlo por par.

		LDR R0, [R4, R7, LSL #2]	@ r8 <- A[i][j]
		BL abs
		MOV R8, R0					@ r8 <- abs(A[i][j])

		LDR R0, [R5, R7, LSL #2]	@ r9 <- B[j]
		BL abs
		MOV R9, R0			@ r9 <- abs(B[i])

		MUL R11, R9, R8		@ r9 <- abs(A[i][j])*abs(B[i])
		ADD R10, R10, R11	@ r10 <- r10 += abs(A[i][j])*abs(B[i])

		ADD R7, R7, #1
		B b2
	b2_end:

		POP {r4-r10, PC}
		BX LR

start:

		LDR R4, =A
		LDR R5, =B
		LDR R6, =C
		MOV R7, #0		@ r7 <- i
	b1:
		CMP R7, #N
		BGE b1_end

		MOV R9, #N
		MUL R8, R9, R7	@ R8 <- (i * nColumnas)
		ADD R0, R4, R8	@ r0 <- =A adaptada
		MOV R1, R5		@ r1 <- =B
		MOV R2, #N		@ r2 <- n
		BL abs_escalar

		STR R0, [R6, R7, LSL #2]	@ r0 -> C[i]

		ADD R7, R7, #1
		B b1

	b1_end:
		B .
		.end






