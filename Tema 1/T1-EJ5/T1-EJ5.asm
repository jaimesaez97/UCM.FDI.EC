// EJERCICIO 3

.extern computo_media
.global start
.EQU N,6
.data

@DA IGUAL EL ARRAY QUE METAMOS: SABEMOS QUE MAXIMO TENDRA 160B:
@ 10 structs de 16 bytes (2 num, 2*6 nota, 2 media)

A : .word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
.text

start:

		LDR R4, =A
		MOV R5, #0			@ r5 <- i
		MOV R6, #0			@ r6 <- direccion a leer

	b1:
		CMP R5, #10			@ leo 10 datos

		LDR R1, [R4, R6]	@ r1 <- datos[i].num
		ADD R6, R6, #2		@ he leido CHAR(2B)

		LDR R0, [R4, R6]	@ r0 <- datos[i].nota[0]

		BL computo_media
		@ r0 <- media

		ADD R6, R6, #14		@ he leido NNOTAS (14B)

		STR R0, [R4, R6]	@ r0 -> datos[i].media

		ADD R5, R5, #1	@ ++i
		B b1

	b1_end:


		B .
		.end






