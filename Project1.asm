_main:
;CozzarelliThomas_Project1.c,14 :: 		void main() {
SUB	SP, SP, #4
;CozzarelliThomas_Project1.c,20 :: 		MOV R0, #0                ;Quotient
MOV	R0, #0
;CozzarelliThomas_Project1.c,21 :: 		MOV R1, #169
MOV	R1, #169
;CozzarelliThomas_Project1.c,22 :: 		MOV R2, #13
MOV	R2, #13
;CozzarelliThomas_Project1.c,23 :: 		MOV R3, #0                ;Remainder
MOV	R3, #0
;CozzarelliThomas_Project1.c,24 :: 		CMP R1,R2
CMP	R1, R2
;CozzarelliThomas_Project1.c,25 :: 		BLT BREAK
BLT	BREAK
;CozzarelliThomas_Project1.c,26 :: 		LABEL2:
LABEL2:
;CozzarelliThomas_Project1.c,27 :: 		SUB R1,R1,R2              ; R1 = R1-R2
SUB	R1, R1, R2, LSL #0
;CozzarelliThomas_Project1.c,28 :: 		ADD R0,R0, #1             ; R0 = R0 +1
ADD	R0, R0, #1
;CozzarelliThomas_Project1.c,29 :: 		CMP  R1,R2                ;Seeing what R1-R2 equals
CMP	R1, R2
;CozzarelliThomas_Project1.c,30 :: 		BGE LABEL2                ;Conditional statement checking if R0 is greater than or equal to R2, and if yes it goes to LABEL 2
BGE	LABEL2
;CozzarelliThomas_Project1.c,31 :: 		ADD R3,R3,R1              ;Sets R3 as the new storage for the remainder
ADD	R3, R1
;CozzarelliThomas_Project1.c,32 :: 		BREAK:
BREAK:
;CozzarelliThomas_Project1.c,34 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
