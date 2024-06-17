//*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 11/28/2019
//Course: ELEC3371-00
//Description:Write a program which communicates with the USART terminal of the development software using a baud rate of 56,000. 
//The program should accept up to 50 single characters from the USART terminal until '@' button is pressed. Each character must be displayed on one line



//*********************************************************************************************************************************
//Variable Initializations
 void InitializeUSART1();
 unsigned int rcvrd;
 int counter;
 char ch;
 int p = 0;
 
 
 
//Main Function
void main () {
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_10); // Set PORTA as  a input for button PA10
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_9); // Set PORTA as  a input for button PA9
GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_ALL); // Set PORTD as digital output
GPIO_Digital_Output(&GPIOC_ODR, _GPIO_PINMASK_ALL);//set PORTC as digital output
GPIO_Digital_Output(&GPIOE_ODR,_GPIO_PINMASK_ALL);  //set PORTE as digital Output Counter



for(;;) {
                while (!((USART1_SR & (1<<5))== 0x20)){}            // Check RXNE in USART1 Status Register.
                 rcvrd = USART1_DR;                                 // read data from receiver data register
                while (! (USART1_SR & (1<<7)) == 0x80) {}
                USART1_DR = rcvrd;
                p++;                                                // Adds one to the dummy variable p to have a count of how many times data has been entered
                GPIOE_ODR = p*256;                                  // Sets the GPIOE output to the counter number of P times 256
                
                if (ch == 0x40 && p == 50) {                                     // While reading in the data check if @ is pressed then breaks the program
                break;
        }
                

        }

        
}
 
//Sub function used from example given in class
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
