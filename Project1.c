
 //-------------------------------------------------------------------------------------
 // Name: Thomas Cozzarelli
 // Date: 9/23/2019
 // Course: ELEC 3371
 // Description: create a program to do division by successive subtraction on two bytes
 // ------------------------------------------------------------------------------------

 

int x;


void main() {

  
  
  //Asembly
  asm{
                MOV R0, #0                ;Quotient
                MOV R1, #169
                MOV R2, #13
                MOV R3, #0                ;Remainder
                CMP R1,R2
                    BLT BREAK
      LABEL2:
                SUB R1,R1,R2              ; R1 = R1-R2
                ADD R0,R0, #1             ; R0 = R0 +1
                CMP  R1,R2                ;Seeing what R1-R2 equals
                BGE LABEL2                ;Conditional statement checking if R0 is greater than or equal to R2, and if yes it goes to LABEL 2
                ADD R3,R3,R1              ;Sets R3 as the new storage for the remainder
      BREAK:
      }
}