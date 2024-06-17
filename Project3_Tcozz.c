//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 11/21/2019
//Course: ELEC3371-00
//Description: Write a program in the Assembly language that turns on PORTE LED's according
//to the values for two numbers that you specify in two variables in your program  The program must start by displaying the smaller number and incrementing 
//it by 1 every second until it reaches the larger number. Then,it will decrement the value displayed every second until it reaches the lower number. 
//This process must be repeated indefinitely. From there the program will also display the smaller number on portC, from there the numbers will also be clocked in using the clocks
//falling edge making it so the numbers cannot be equal and the program can continue indefinetly.
//*********************************************************************************************************************************
// Initizalzing count and random number variables to be used in the code
int A=16;
int B=8;
int C=0x0000;
int D=0x0000;

void main() {
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_0); // Set PORTB0 as digital input increases by 1 for port C
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_1); // Set PORTB1 as digital input increases by 1 for port D
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_4); // Set PORTB4 as digital input decreases by 1 for port C
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_5); // Set PORTB5 as digital input decreases by 1 for port D
GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_ALL); // Set PORTD as digital output
GPIO_Digital_Output(&GPIOC_ODR, _GPIO_PINMASK_ALL);//set PORTC as digital output


if (A>B){       // compares the two inputs and sets the higher input to port D and the lower to port C
D=A;              //These next lines just swap the different variables based on the if statement to be used in later functions
C=B;
}
else{
D=B;
C=A;
}
GPIOD_ODR=D;
GPIOC_ODR=C;
   for(;;){
   while(GPIOB_IDR.B0==0 && GPIOB_IDR.B1==0 || GPIOB_IDR.B4==0 && GPIOB_IDR.B5==0){}   // infinite while looop to check if any button is pressed
  if(GPIOB_IDR.B0==1 && (GPIOC_ODR+1)!=GPIOD_ODR){              //when B0 is pressed and C+1 is less than D, C is increased by 1
   GPIOC_ODR=GPIOC_ODR+1;
   }

  if(GPIOB_IDR.B1==1 && (GPIOC_ODR-1)!=0){                    // when B1 is pressed then if C-1 is not 0, it will decrease C by 1
   GPIOC_ODR=GPIOC_ODR-1;
   }

   if(GPIOB_IDR.B4==1){                                     //when B4 is pressed, D is increased by 1
   GPIOD_ODR=GPIOD_ODR+1;
   }
   if(GPIOB_IDR.B5==1 && (GPIOD_ODR-1)>GPIOC_ODR){            // when B5 is pressed and D-1 is greater than C, D is decreased by 1
   GPIOD_ODR=GPIOD_ODR-1;
   }
   while((GPIOB_IDR.B0!=0 && GPIOB_IDR.B1!=0) || (GPIOB_IDR.B4!=0 && GPIOB_IDR.B5!=0)){} //an infinite while loop to detect when these buttons are pressed

   }
  }
  
  asm //Assembly will start here
  
  