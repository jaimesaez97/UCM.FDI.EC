
	.equ COEF1, 3483
	.equ COEF2, 11718
	.equ COEF3, 1183

	.text
// Descomentar e implementar estas funciones
	.extern gaussian
	.global rgb2grayARM
	.global apply_gaussianARM
	.global div16384
	.global rowToColumnARM
rgb2grayARM:
		PUSH {r4-r10, LR}
		MOV R4, R0			@ r4 <- =pixelRGB
		MOV R10, #0

		LDRB R5, [R4]		@ r5 <- pixelRGB->R
		LDRB R6, [R4, #1]	@ r6 <- pixelRGB->G
		LDRB R7, [R4, #2]	@ r7 <- pixelEGB->B

		LDR R8, =COEF1
		MUL R9, R8, R5		@ r9 <- (pixelRGB->R * 3483)
		ADD R10, R10, R9

		LDR R8, =COEF2
		MUL R9, R8, R6		@ r9 <- (pixelRGB->G * 11718)
		ADD R10, R10, R9

		LDR R8, =COEF3
		MUL R9, R8, R7		@ r9 <- (pixelEGB->B * 1183)
		ADD R10, R10, R9

		@ r0 <- pixel[]
		MOV R0, R10
		BL div16384

		@ r0 <- pixel[]/16384

		POP {r4-r10, LR}
		BX LR

div16384:
		MOV R0, R0, ASR #14
		BX LR


apply_gaussianARM:
		PUSH {r4-r10, LR}
		MOV R4, R0			@ r4 <- =im1
		MOV R5, R1			@ r5 <- =im26
		MOV R6, R2			@ r6 <- width
		MOV R7, R3			@ r7 <- heigth

		MOV R8, #0			@ r8 <- i
		MOV R9, #0			@ r9 <- j
	b1:
		CMP R8, R7
		BGE	b1_end			@ while (i < height)
	b2:
		CMP R9, R6
		BGE b2_end			@ while (j < width)

		MOV R0, R4			@ NO NECESARIO -> EN R0 YA ESTÁ =im1
		MOV R1, R6			@ r1 <- width
		MOV R2, R7			@ r2 <- height
		MOV R3, R8			@ r3 <- i
		SUB SP, SP, #4
		STR R9, [SP, #0]	@ PILA[0] <- j

		BL gaussian			@ r0 <- unsigned char

		ADD SP, SP, #4

		MUL R10, R8, R6		@ r10 <- (i * width)
		ADD R10, R10, R9	@ r10 <- (i * width + j)

		STRB R0, [R5, R10]	@ im2[i * width + j] = gaussian()

		ADD R9, R9, #1
		B b2

	b2_end:
		MOV R9, #0			@ j=0
		ADD R8, R8, #1		@ ++i
		B b1
	b1_end:
		POP {r4-r10, LR}
		BX LR

rowToColumnARM:
		PUSH {r4-r11}
		MOV R4, R0			@ r4 <- =im1
		MOV R5, R1			@ r5 <- =im2
		MOV R6, R2			@ r6 <- width
		MOV R7, R3			@ r7 <- heigth

		MOV R8, #0			@ r8 <- i
		MOV R9, #0			@ r9 <- j
	b3:
		CMP R8, R7
		BGE	b3_end			@ while (i < height)
	b4:
		CMP R9, R6
		BGE b4_end			@ while (j < width)

		MOV R10, #0
		MUL R10, R8, R6		@ r10 <- (i * width)
		ADD R10, R10, R9	@ r10 <- (i * width + j)

		MOV R11, #0
		MUL R11, R9, R7		@ r11 <- (j * width)
		ADD R11, R11, R8	@ r11 <- (j * width + i)


		LDRB R11, [R4, R11]	@ r11 <- im1[(j * width + i)]

		STRB R11, [R5, R10]	@ r11 -> im2[(i * width + j)]

		ADD R9, R9, #1
		B b4

	b4_end:
		MOV R9, #0			@ j=0
		ADD R8, R8, #1		@ ++i
		B b3
	b3_end:
		POP {r4-r11}
		BX LR


