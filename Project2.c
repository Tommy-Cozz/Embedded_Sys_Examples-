//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 10/14/2019
//Course: ELEC3371-00
//Description: This program ...
//*********************************************************************************************************************************

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
   while(GPIOA_IDR.B0 != 0){            // Detects when the PA0 button is pressed
     count = count + 1;
     GPIOE_ODR = (count+256);

  GPIOD_ODR = 255;


  while(GPIOA_IDR.B0 == 0){             // Detects when the PA0 button is released

  GPIOD_ODR = 65280;



   }
  }
 }
}