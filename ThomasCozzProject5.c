  //*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Date: 12/07/2019
//Course: ELEC3371-00
//Description:Something neat s



//*********************************************************************************************************************************
//GLOBAL VARIABLES
int counter;
void PinConfiguration();    // Letting the program know it will use a sub function of this name in the pin configuration
void Timer1Configuration(); // Letting the program know it will use a sub function of this name in the TIMER1 functions.
void InitializeUSART1();    // Letting the progrma know it will use a sub funcion to start up the USART.
unsigned int rcvrd;


//MAIN FUNCTIONS
void main () {
        PinConfiguration();
        Timer1Configuration();
        InitializeUSART1();
        

 // Checking timer status register to perform an action
while(!TIM1_SR.UIF){}          // Wait until timer update flag is set, meaning the count val was reached
  if (TIM1_SR.UIF == 1) { // If you have multiple timers, can use IF to check status register
  TIM1_SR.UIF = 0;                  // Clear this flag which will reset the timer
  GPIOD_ODR= ~GPIOD_ODR;  // Toggle LEDs
  GPIOE_ODR= ~GPIOE_ODR;
  }
 for(;;) {
          printf("Enter a number 1 through 4");
                while (!((USART1_SR & (1<<5))== 0x20)){}            // Check RXNE in USART1 Status Register.
                 rcvrd = USART1_DR;                                  //read data from receiver data register
                while (! (USART1_SR & (1<<7)) == 0x80) {}
                USART1_DR = rcvrd;                                  // transmit the received data
        }
  
  
  
  
  
}

//**************************************************************************************************
//SUB FUNCTIONS
void PinConfiguration() {
        GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_ALL);
        GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_ALL);
}

void Timer1Configuration(){
        RCC_APB2ENR |= (1 << 11);   // Enable TIMER1 clock
        RCC_APB1ENR |= (1 << 11);   //Enable the Timer 4 clock
        
        TIM1_CR1 = 0x0000;          // Disable timers until configuration is complete
        
        TIM4_CR4 = 0x0000;
        
        TIM1_PSC = 7999;
        
        TIM4_PSC = 7999;          // Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /
                                            //                     7999 (Value in TIMx_PSC) + 1) = 9000
        TIM1_ARR = 9000;
        
        TIM4_ARR = 9000;        // Reload timer count register with this value when count register resets
                                                // to 0 after counting from zero to this value
        TIM1_CR1 = 0x0001; 
        TIM4_CR4 = 0x0001;        // Enable Timer1 & Timer 4


}

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