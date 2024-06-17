//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 11/28/2019
//Course: ELEC3371-00
//Description: Write a program which communicates with the USART terminal of the development software using a baud rate of 56,000.
// The program should accept up to 50 single characters from the USART terminal until '@' button is pressed. Each character must be displayed on one line
// From there sort the inputs read in based on their ACSII values and return them to the USART terminal to
// be displayed. Next as characters are entered after each keystroke it must be displayed on the LEDS on PORTE
//*********************************************************************************************************************************

//Inizilzing Variables to be used in the program
char uart_rd;
void InitializeUSART1();
unsigned int rcvrd;
int counter=0;
int pine=0;
int i = 0;
int n= 0;
char array1[50];

void main() {
UART1_Enable();
GPIO_Digital_Output(&GPIOE_ODR, _GPIO_PINMASK_ALL); // Set port E as a digital output
GPIOE_CRH=0x33333333333;
  UART1_Init(56000);                             // Initialize UART module at 56000 bps
  Delay_ms(100);                                 // Wait for UART module to stabilize


  while (counter!=50){                           // Loops until count is equal to 50 or an @ is read
    if (UART1_Data_Ready()) {                    // Checks if the UART is actually recieving the data
      uart_rd = UART1_Read();                    // Reads in the data revieced by the UART serial port
      array1[counter]=uart_rd;
      UART1_Write(uart_rd);                      // Sends the data inputed via the UART serial port
      GPIOE_ODR=counter;
    counter++;                                   // Increases the counter by 1 each time through loop

    }
    if (uart_rd = 0x40){
    break;
   }
   for ( i=0; i<counter; ++i){                   // Sorts the inputs inside array[] based on its ascii value
       for(n= i + 1; n<counter; n++){

              if (array1[i] > array1[n]){        // Checks if the array is greater than the base array to make sure it has reached its limit
              pine = array1[i];                  // Sets the dummy variable pine then from there just using a swap function to interchange the arrays
              array1[i] = array1[n];
              array1[n]= pine;
                                      }
                                  }
                            }
  }
  for (i=0; i<counter; ++i){
      UART1_Write(array1[i]);                    // Send the data to the UART terminal after being sorted
                          }
}
// Sub function to set up the USART terminal
 void InitializeUSART1(){                 // Sub function which initializes the registers to enable USART1
        RCC_APB2ENR |= 1;                 // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
        AFIO_MAPR=0X0F000000;             // Do not mask PA9 and PA10 (becaue we are using for USART)
        RCC_APB2ENR |= 1<<2;              // Enable clock for GPIOA
        GPIOA_CRH &= ~(0xFF << 4);        // Clear PA9, PA10
        GPIOA_CRH |= (0x0B << 4);         // USART1 Tx (PA9) output push-pull
        GPIOA_CRH |= (0x04 << 8);         // USART1 Rx (PA10) input floating
        RCC_APB2ENR |= 1<<14;             // enable clock for USART1
        USART1_BRR=0X00000506;            // Set baud rate to 56000
        USART1_CR1 &= ~(1<<12);           // Force 8 data bits. M bit is set to 0.
        USART1_CR2 &= ~(3<<12);           // Force 1 stop bit
        USART1_CR3 &= ~(3<<8);            // Force no flow control and no DMA for USART1
        USART1_CR1 &= ~(3<<9);            // Force no parity and no parity control
        USART1_CR1 |= 3<<2;               // RX, TX enable
        USART1_CR1 |= 1<<13;              // USART1 enable
        Delay_ms(100);                    // Wait for USART to complete configuration and enable.
        }






































