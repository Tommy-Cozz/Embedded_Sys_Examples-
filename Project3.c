//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 12/15/2019
//Course: ELEC3371-01
//Description: DIplay the smaller number and incriment it by one every second until it reaches the larger number. From there it will decrement
// the value displayed every second until it reaches the lower number. This must be repeated. From there display the smaller number on PORTC and the 
// higher number on PORTD. Using the push buttons on PORTB have two which will increas/decrease the smaller number and two which increase and decrease the larger number.
// Clock in the data on the falling edge.
//**********************************************************************************************************************************
void main() {

int firstB = 1;
int secondB = 15;
int topNumber;                   // Passes values from secondB into here
int bottomNumber;                // Passes values from firstB into here
int trackE;                      // Used for incrementing port e
int scanB;                       // Check to see if button is pressed

int incrementTop = 0;            // Increments port D
int decrementTop = 0;            // Decrements port D
int incrementBottom = 0;         // Increments port C
int decrementBottom = 0;         // Decrements port C
int pine=1;                      // Set to 0 for counting down and 1 for counting up
int k;                           // Dummy variable used in the for loop

GPIO_DIGITAL_INPUT(&GPIOB_BASE,_GPIO_PINMASK_0);GPIO_D
IGITAL_INPUT(&GPIOB_BASE,_GPIO_PINMASK_1);
GPIO_DIGITAL_INPUT(&GPIOB_BASE,_GPIO_PINMASK_2);
GPIO_DIGITAL_INPUT(&GPIOB_BASE,_GPIO_PINMASK_5);
GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_ALL);
GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_ALL);
GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_ALL);

       if(secondB > firstB){                                // Compares the two values
        topNumber = secondB;                                // Stores secondB into topNumber
        bottomNumber = firstB;}                             // Stores secondB value into bottomNumber

        else if (secondB < firstB) {
        bottomNumber = secondB;
        topNumber = firstB;}

       trackE = bottomNumber;
       GPIOE_ODR = trackE * 256;
       GPIOC_ODR = bottomNumber;                            // Stores value in port C
       GPIOD_ODR = topNumber;                               // Stores value in port D

         while(1)                                           // Just sets an infinite loop
         {
         for(k=0;k<10;k++)
         {
//----------------------------------------------------------------------------------------------------------------
         if(GPIOB_IDR.B0 == 0 && incrementTop == 1){         // Checks state of button PB0
                   topNumber = topNumber + 1;                // Increments port D
                   incrementTop = 0;
                   GPIOD_ODR = topNumber;}                   // Stores the new value in portD

         if(GPIOB_IDR.B0 == 1){incrementTop = 1;}            // When PB0 is pressed



if(GPIOB_IDR.B1 == 0 && decrementTop == 1){                  // Checks state of button PB1
                        topNumber = topNumber - 1;           // Decrements port D
                        decrementTop = 0;
                        GPIOD_ODR = topNumber;}              // Displays the new value
if(GPIOB_IDR.B1 == 1){decrementTop = 1;}                     // Checks for when PB1 is being pressed



if(GPIOB_IDR.B2 == 0 && incrementBottom == 1){               // Cecks state of button PB2
      bottomNumber = bottomNumber + 1;                       // Increments port C
      incrementBottom = 0;
      GPIOC_ODR = bottomNumber;}                             // Stores value in port C
if(GPIOB_IDR.B2  == 1){incrementBottom = 1;}                 // Checks state of button PB2


if(GPIOB_IDR.B5 == 0 && decrementBottom == 1){               // Checks if the PB5 is pressed or not
      bottomNumber = bottomNumber - 1;                       // Decrements port C
      decrementBottom = 0;
      GPIOC_ODR = bottomNumber;}                             // Stores value on port C
if(GPIOB_IDR.B5 == 1){decrementBottom = 1;}                  // Checks stae of button PB5

                                                             // To increment PORT E in between the lower and higher number

         Delay_ms(1000);}                                    // Delays by 1000 milliseconds
         if ( pine == 1 )
         {
         trackE = trackE + 1;                                // Increments port E
         GPIOE_ODR = trackE * 256;}                          // Stored in port E
         else {
         trackE = trackE -1;                                 // Decrements trackE
         GPIOE_ODR = trackE *256;}                           // Stored in port E

         if (trackE>=topNumber){minecraft=0;}
         if (trackE<=bottomNumber){minecraft=1;}
  }
  }




































