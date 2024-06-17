//**************************************************************************************************
// Name: Thomas Cozzarelli
// Date: 12/15/2019
// Course: ELEC3371-00
// Description: Timer 1 is used to turn on and off LEDs connected to PORTD and PORTE every 1, 2, 3, or 4 seconds. 
// Timer 4 is used to turn on and off LEDs connected to PORTB and PORTC every 1, 2, 3, or 4 seconds.
// From there the program communictes using the USART serial port to ask for a user input for timer 1 and 4 and then configures the
// timers according to the inputs, from there another USART should be used to specify the duration of on/off for each set of LEDS.
// From there the USART terminal must see if q or Q or R or r is pressed. If R or r is pressed program must go back to step two and repeat.
// If q or Q is pressed the program will stop.

//**************************************************************************************************
//GLOBAL VARIABLES
int counter;
int prescale1;
int prescale4;
char uart_rd1;
char uart_rd4;
void prescalars();
void PinConfiguration();                                  // Declaration of sub function used for pin configuration
void Timer1Configuration();
void Timer4Configuration();                               // Declaration of sub function used for TIMER1 configuration

int main () {
    PinConfiguration();                                                            //Lines 20-55 get user input from the USART terminals to use later in the code
        while (!UART1_Data_Ready()){
      UART1_Write_Text("Please answer the following questions with numbers 1-4");
      UART1_Write_Text("Enter the number of seconds for timer 1 to run");

      uart_rd1 = UART1_Read();   // read the received data to uart_rd1
       UART1_Write_Text("The amount of seconds timer 1 will run for is:");
       UART1_Write_Text(uart_rd1);

      UART1_Write_Text("Enter the number of seconds for timer 4 to run");
      uart_rd4 = UART1_Read();   // read the received data to uart_rd4
      UART1_Write_Text("The amount of seconds timer 4 will run for is:");
      UART1_Write_Text(uart_rd4);

    }
        Prescalars();
        Timer1Configuration();
        Timer4Configuration();

    if(tim1_sr.UIF==1){
    GPIOD_ODR=~GPIOD_ODR;
    GPIOE_ODR=~GPIOE_ODR;
    if(uart_rd1 = 'r' || 'R'){
    while (!UART1_Data_Ready()){
      UART1_Write_Text("Please answer the following questions with numbers 1-4");
      UART1_Write_Text("Enter the number of seconds for timer 1 to run");

      uart_rd1 = UART1_Read();   // read the received data to uart_rd1
       UART1_Write_Text("The amount of seconds timer 1 will run for is:");
       UART1_Write_Text(uart_rd1);

      UART1_Write_Text("Enter the number of seconds for timer 4 to run");
      uart_rd4 = UART1_Read();   // read the received data to uart_rd4
      UART1_Write_Text("The amount of seconds timer 4 will run for is:");
      UART1_Write_Text(uart_rd4);
    }
    }
    if(uart_rd1 = 'q' || 'Q');                          // Looks for when q or a Q is entered by the user
    return 0;
    }
    }


    if(tim4_SR.UIF==1){                                 //Checks when the timer is 1 then exceutes the code and inverts the outputs of PORTB and PORTC
    GPIOB_ODR=~GPIOB_ODR;
    GPIOC_ODR=~GPIOC_ODR;
    if(uart_rd4 = 'r' || 'R'){
    while (!UART1_Data_Ready()){
      UART1_Write_Text("Please answer the following questions with numbers 1-4");
      UART1_Write_Text("Enter the number of seconds for timer 1 to run");

      uart_rd1 = UART1_Read();                                                     // Read in the data recieved by uart_rd1
       UART1_Write_Text("The amount of seconds timer 1 will run for is:");
       UART1_Write_Text(uart_rd1);

      UART1_Write_Text("Enter the number of seconds for timer 4 to run");
      uart_rd4 = UART1_Read();                                                     // Read in the data recieved by uart_rd4
      UART1_Write_Text("The amount of seconds timer 4 will run for is:");
      UART1_Write_Text(uart_rd4);
    }
    }
    if(uart_rd4 = 'q' || 'Q'){
    return 0;
    }
    }



//**************************************************************************************************
//SUB FUNCTIONS
void PinConfiguration() {
       GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_ALL); // PORTE,PORTB,PORTC, and PORTD as digital output
       GPIO_Digital_Output(&GPIOE_ODR, _GPIO_PINMASK_ALL);
       GPIO_Digital_Output(&GPIOB_ODR, _GPIO_PINMASK_ALL);
       GPIO_Digital_Output(&GPIOC_ODR, _GPIO_PINMASK_ALL);
       GPIOD_ODR=0x0000;                                   // Setting all the ports to 0 so they can modified later in the code
       GPIOE_ODR=0x0000;
       GPIOB_ODR=0x0000;
       GPIOC_ODR=0x0000;
}

void Timer1Configuration(){
        RCC_APB2ENR |= (1 << 11);         // Enable TIMER1 clock. RCC: Clock Configuration Register


        TIM1_CR1 = 0x0000;                // Disable timer until configuration is complete


        TIM1_PSC = prescale1;             // Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /

        TIM1_ARR = 9000;                  // Reload timer count register with this value when count register resets

        TIM1_CR1 = 0x0001;                // Enable TIMER1

}
void Timer4Configuration(){
        RCC_APB1ENR |= (1 << 2);          // Enable TIMER1 clock. RCC: Clock Configuration Register


        TIM4_CR1 = 0x0000;                // Disable timer until configuration is complete


        TIM4_PSC = prescale4;             // Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /

        TIM4_ARR = 9000;                  // Reload timer count register with this value when count register resets

        TIM4_CR1 = 0x0001;                // Enable TIMER1
                                          // Bit 4 of TIM1_CR1 specifies whether the counter count up (BIT4=0) or counts down (BIT4=1)
// In this configuration this counting up is used.
}
//Setting up the prescaling values
void prescalars(){
switch (uart_rd1){
case '1':
prescale1=7999;
break;
case'2':
prescale1=15999;
break;
case'3':
prescale1=23999;
break;
case'4':
prescale1=31999;
break;
default:
prescale1=7999;}

switch (uart_rd4){
case '1':
prescale4=7999;
break;
case'2':
prescale4=15999;
break;
case'3':
prescale4=23999;
break;
case'4':
prescale4=31999;
break;
default:
prescale4=7999;}
}




































