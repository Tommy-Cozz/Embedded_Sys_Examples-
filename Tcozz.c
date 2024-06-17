//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 10/14/2019
//Course: ELEC3371-00
//Description: Write a program in the assembly language that when PA0 is pressed, the LEDs on lower half of PORTD turn on (the upper half off) and 
//  when it is released the LEDs on upper half of PORTD turn on and the lower half turns off. At the beginning, all LEDs are off.
//  Also, display the number of times that PA0 is pressed on the LEDs connected to upper half of PORTE. Expand the program to include PA4 that when pressed,
//  all lights on PORTD turn on and when released, all lights turn off.
//*********************************************************************************************************************************

// Initizalzing count and flag variables to be used in the code(They both are set to 0 to start)
 int count = 0;
 int flag = 0;

 

void main() {
//Initializing
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_0);         //Set PORTA.B0 as input data register
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_4);         //Set PORTA.B4 as input data register
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_5);         //Set PORTA.B5 as input data register
GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_ALL);      //Set PORTD as output data register
GPIO_Digital_Output(&GPIOE_ODR, _GPIO_PINMASK_ALL);      //Set PORTE as output data register


for(;;) {
   while(GPIOA_IDR.B0 == 0 && GPIOA_IDR.B4 == 0) {}             //Set up the intial conditions of the while loop to detect when the button is pressed
   if(GPIOA_IDR.B0 != 0){                                       //Checks if PA0 is pressed
     flag = 1;                                                  //Sets the flag = 1 for future use
     GPIOD_ODR = 255;                                           // Turns on the lower half of the LEDS
     }
     else{
     GPIOD_ODR =65535;}                                         // Detects when PA4 is pressed and turns on Both the HIGH adn LOW outputs
     

     while(GPIOA_IDR.B0 != 0 || GPIOA_IDR.B4 != 0) {}           // Sets up the inital while loop for when PA0 is pressed or PA4 is pressed
     if(flag == 1){                                             // Detects if the flag is set to 1 then goes into the rest of the if statment
     GPIOD_ODR = 65280;                                         // When PA0 is released the uppper half of the lights turn on
     count = count + 1;                                         // Adds one to the count everytime it the program goes throught this if statement
     GPIOE_ODR = (count*256);                                   // Mulitiplies the count time 256 to get to the high register to display on the LED
     flag = 0;                                                  // Resets the flag back to 0
     }
     else {GPIOD_ODR = 0;}                                      // If none of that everything turns off





   }
  }
//The assembly Part
/*
void main() {

//INITIALIZATIONS
RCC_APB2ENR |= 1 << 2;          // Enable GPIOA clock - necessary to use GPIOA
RCC_APB2ENR |= 1 << 5;          // Enable GPIOD clock - necessary to use GPIOD
RCC_APB2ENR |= 1 << 6;          // Enable GPIOE clock - necessary to use GPIOE
GPIOA_CRL = 0x44444444;         // Configure GPIOA as an input
GPIOA_CRH = 0x44444444;
GPIOD_CRL = 0x33333333;         // Configure GPIOD as an output for LED's
GPIOD_CRH = 0x33333333;
GPIOE_CRH = 0x33333333;         // Configure GPIOE as an output for LED's


//**************************************************************************************************
//ASSEMBLY
        asm{
        LABEL1:
                 MOVW        R0, #LO_ADDR(RCC_APB2ENR+0)  ; Load the lower two bytes of R0 with the lower

                 MOVT        R0, #HI_ADDR(RCC_APB2ENR+0)  ; Load the upper two bytes of R0 with the upper

                 LDR         R1, [R0]                     ; Loads content of R0 (RCC_APB2ENR) in R1. Load contents

                 MOV         R2, #0x0020                  ; Set bit 5 of R2 to 1 (0010 0000)
                 ORRS        R1, R1, R2                   ; Write a 1 in bit 5 of R1
                 STR         R1, [R0]                     ; Store results of previous operation in RCC_APB2ENR


                 MOV         R3, #0x33333333              ; Save value for GPIO_CRL and GPIO_CRH in R3
                                                          ; defines all pins of PORTD as output GPIO
                 MOVW        R0, #LO_ADDR(GPIOD_CRL+0)    ; Load lower two bytes of R0 with the lower two bytes of

                 MOVT        R0, #HI_ADDR(GPIOD_CRL+0)    ; Load upper two bytes of R0 with the upper two bytes of

                 STR         R3, [R0]                     ; Store the value of R3 in GPIOD_CRL
                 MOVW        R0, #LO_ADDR(GPIOD_CRL+0)    ; Load lower two bytes of R0 with the lower two bytes of

                 MOVT        R0, #HI_ADDR(GPIOD_CRH+0)    ; Load upper two bytes of R0 with the upper two bytes of

                 STR         R3, [R0]                     ; Store the value in R3 in GPIOD_CRH (PORTD)
                 MOV         R4, #0xFFFFFFFF              // Move R4 to 0x0000
                 BL          LABEL2                       ; Go to LABEL2

        LABEL2:
                 MOVW        R0, #LO_ADDR(GPIOD_ODR+0)    ; Load lower two bytes of R0 with the lower two bytes of
                                                          ; the address for register GPIOD_ODR (PORTD)
                 MOVT        R0, #HI_ADDR(GPIOD_ODR+0)    ; Load upper two bytes of R0 with the upper two bytes of
                                                          ; the address for register GPIOD_ODR (PORTD)
                 STR         R4, [R0]                     ; Store the value R4 in GPIOD_ODR (PORTD)

                 MOVW        R1, #LO_ADDR(GPIOA_IDR+0)    ; Load lower two bytes of R0 with the lower two bytes of
                                                          ; the address for register GPIOA_IDR (PORTA)
                 MOVT        R2, #HI_ADDR(GPIOA_IDR+0)    ; Load upper two bytes of R0 with the upper two bytes of
                                                          ; the address for register GPIOA_IDR (PORTA)

                 STR         R5, [R1]                     ; Store the value of R5 in GPIOA_IDR (PORTA/L)
                 STR         R6, [R2]                     ; Store the value of R6 in GPIOA_IDR (PORTA/H)

                 TST         R6, #0                       ; Compare input of PA4 (High) to 0
                 BNE         PA4Press                     ; Go to PA4Press if PA4 has been pressed

                 TST         R5, #0                       ; Compare the input of PA0 (LOW) to 0
                 BNE         LABEL3                       ; If PA0 is not equal to 0 (button pressed) go to LABEL3
                 BEQ         LABEL2                       ; If PA0 is equal to 0 (button not pressed) go to LABEL2

        LABEL3:
                 MOVT        R0, #HI_ADDR(GPIOE_ODR+0)    ; Load higher two bytes of R5 with the higher two bytes of address
                                                          ; for register GPIOE. The function returns the higher half of address.
                 STR         R7, [R0]                     ; Store the value of R7 in GPIOE_ODR (PORTE/H)
                 ADD         R7, #0x00000100              ; Add 0100 to PORTE every time PA0 is pressed

                 MOV         R4, #0x00FF                  // Move GPIOD to light up PORTD/L and turn off PORTD

                 TST         R5, #1                       ; Compare R5 (PA0) to 1
                 BNE         LABEL4                       ; If PA0 is not equal to 1 (button released) go to LABEL4

        LABEL4:
                 MOV         R4, #0xFF00                  // Move GPIOD to light up PORTD/H and turn off PORTD

                 TST         R6, #0                       ; Compare input of PA4 (High) to 0
                 BNE         PA4Press                     ; Go to PA4Press if PA4 has been pressed

                 TST         R5, #0                       ; Compare the input of PA0 (LOW) to 0
                 BNE         LABEL3                       ; If PA0 is not equal to 0 (button pressed) go to LABEL3
                 BEQ         LABEL2                       ; If PA0 is equal to 0 (button not pressed) go to LABEL2

        PA4Press:
                 MOV         R4, #0xFFFFFFFF              // Move GPIOD to light up PORTD
                 MOVW        R0, #LO_ADDR(GPIOD_ODR+0)    ; Load lower two bytes of R0 with the lower two bytes of
                                                          ; the address for register GPIOD_ODR (PORTD)
                 MOVT        R0, #HI_ADDR(GPIOD_ODR+0)    ; Load upper two bytes of R0 with the upper two bytes of
                                                          ; the address for register GPIOD_ODR (PORTD)
                 STR         R4, [R0]                     ; Store the value R4 in GPIOD_ODR (PORTD)

                 TST         R6 , #0                      ; Compare input of PA4 to 0
                 BNE         PA4Press                     ; Go to PA4Press if PA4 has been pressed

                 TST         R5, #0                       ; Compare the input of PA0 to 0
                 BNE         LABEL3                       ; If PA0 is not equal to 0 (button pressed) go to LABEL3
                 BEQ         LABEL2                       ; If PA0 is equal to 0 (button not pressed) go to LABEL2
                 }
}
*/
