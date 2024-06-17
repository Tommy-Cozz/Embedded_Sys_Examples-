_main:
;TommyCozzarelli_Project4.c,21 :: 		void main() {
;TommyCozzarelli_Project4.c,22 :: 		UART1_Enable();
BL	_UART1_Enable+0
;TommyCozzarelli_Project4.c,23 :: 		GPIO_Digital_Output(&GPIOE_ODR, _GPIO_PINMASK_ALL); // Set port E as a digital output
MOVW	R1, #65535
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
BL	_GPIO_Digital_Output+0
;TommyCozzarelli_Project4.c,24 :: 		GPIOE_CRH=0x33333333333;
MOV	R1, #858993459
MOVW	R0, #lo_addr(GPIOE_CRH+0)
MOVT	R0, #hi_addr(GPIOE_CRH+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,25 :: 		UART1_Init(56000);                             // Initialize UART module at 56000 bps
MOVW	R0, #56000
BL	_UART1_Init+0
;TommyCozzarelli_Project4.c,26 :: 		Delay_ms(100);                                 // Wait for UART module to stabilize
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_main0:
SUBS	R7, R7, #1
BNE	L_main0
NOP
NOP
NOP
;TommyCozzarelli_Project4.c,29 :: 		while (counter!=50){                           // Loops until count is equal to 50 or an @ is read
MOVW	R0, #lo_addr(_counter+0)
MOVT	R0, #hi_addr(_counter+0)
LDRSH	R0, [R0, #0]
CMP	R0, #50
IT	EQ
BEQ	L_main3
;TommyCozzarelli_Project4.c,30 :: 		if (UART1_Data_Ready()) {                    // Checks if the UART is actually recieving the data
BL	_UART1_Data_Ready+0
CMP	R0, #0
IT	EQ
BEQ	L_main4
;TommyCozzarelli_Project4.c,31 :: 		uart_rd = UART1_Read();                    // Reads in the data revieced by the UART serial port
BL	_UART1_Read+0
MOVW	R3, #lo_addr(_uart_rd+0)
MOVT	R3, #hi_addr(_uart_rd+0)
STRB	R0, [R3, #0]
;TommyCozzarelli_Project4.c,32 :: 		array1[counter]=uart_rd;
MOVW	R1, #lo_addr(_counter+0)
MOVT	R1, #hi_addr(_counter+0)
LDRSH	R2, [R1, #0]
MOVW	R1, #lo_addr(_array1+0)
MOVT	R1, #hi_addr(_array1+0)
ADDS	R1, R1, R2
UXTB	R0, R0
STRB	R0, [R1, #0]
;TommyCozzarelli_Project4.c,33 :: 		UART1_Write(uart_rd);                      // Sends the data inputed via the UART serial port
MOV	R0, R3
LDRB	R0, [R0, #0]
BL	_UART1_Write+0
;TommyCozzarelli_Project4.c,34 :: 		GPIOE_ODR=counter;
MOVW	R2, #lo_addr(_counter+0)
MOVT	R2, #hi_addr(_counter+0)
LDRSH	R1, [R2, #0]
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,35 :: 		counter++;                                   // Increases the counter by 1 each time through loop
MOV	R0, R2
LDRSH	R0, [R0, #0]
ADDS	R0, R0, #1
STRH	R0, [R2, #0]
;TommyCozzarelli_Project4.c,37 :: 		}
L_main4:
;TommyCozzarelli_Project4.c,38 :: 		if (uart_rd = 0x40){
MOVS	R1, #64
MOVW	R0, #lo_addr(_uart_rd+0)
MOVT	R0, #hi_addr(_uart_rd+0)
STRB	R1, [R0, #0]
;TommyCozzarelli_Project4.c,51 :: 		}
L_main3:
;TommyCozzarelli_Project4.c,52 :: 		for (i=0; i<counter; ++i){
MOVS	R1, #0
SXTH	R1, R1
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRH	R1, [R0, #0]
L_main13:
MOVW	R0, #lo_addr(_counter+0)
MOVT	R0, #hi_addr(_counter+0)
LDRSH	R1, [R0, #0]
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
LDRSH	R0, [R0, #0]
CMP	R0, R1
IT	GE
BGE	L_main14
;TommyCozzarelli_Project4.c,53 :: 		UART1_Write(array1[i]);                    // Send the data to the UART terminal after being sorted
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
LDRSH	R1, [R0, #0]
MOVW	R0, #lo_addr(_array1+0)
MOVT	R0, #hi_addr(_array1+0)
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
BL	_UART1_Write+0
;TommyCozzarelli_Project4.c,52 :: 		for (i=0; i<counter; ++i){
MOVW	R1, #lo_addr(_i+0)
MOVT	R1, #hi_addr(_i+0)
LDRSH	R0, [R1, #0]
ADDS	R0, R0, #1
STRH	R0, [R1, #0]
;TommyCozzarelli_Project4.c,54 :: 		}
IT	AL
BAL	L_main13
L_main14:
;TommyCozzarelli_Project4.c,55 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_InitializeUSART1:
;TommyCozzarelli_Project4.c,57 :: 		void InitializeUSART1(){                 // Sub function which initializes the registers to enable USART1
;TommyCozzarelli_Project4.c,58 :: 		RCC_APB2ENR |= 1;                 // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #1
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,59 :: 		AFIO_MAPR=0X0F000000;             // Do not mask PA9 and PA10 (becaue we are using for USART)
MOV	R1, #251658240
MOVW	R0, #lo_addr(AFIO_MAPR+0)
MOVT	R0, #hi_addr(AFIO_MAPR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,60 :: 		RCC_APB2ENR |= 1<<2;              // Enable clock for GPIOA
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #4
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,61 :: 		GPIOA_CRH &= ~(0xFF << 4);        // Clear PA9, PA10
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
LDR	R1, [R0, #0]
MOVW	R0, #61455
ANDS	R1, R0
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,62 :: 		GPIOA_CRH |= (0x0B << 4);         // USART1 Tx (PA9) output push-pull
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #176
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,63 :: 		GPIOA_CRH |= (0x04 << 8);         // USART1 Rx (PA10) input floating
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #1024
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,64 :: 		RCC_APB2ENR |= 1<<14;             // enable clock for USART1
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #16384
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,65 :: 		USART1_BRR=0X00000506;            // Set baud rate to 56000
MOVW	R1, #1286
MOVW	R0, #lo_addr(USART1_BRR+0)
MOVT	R0, #hi_addr(USART1_BRR+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,66 :: 		USART1_CR1 &= ~(1<<12);           // Force 8 data bits. M bit is set to 0.
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
LDR	R1, [R0, #0]
MVN	R0, #4096
ANDS	R1, R0
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,67 :: 		USART1_CR2 &= ~(3<<12);           // Force 1 stop bit
MOVW	R0, #lo_addr(USART1_CR2+0)
MOVT	R0, #hi_addr(USART1_CR2+0)
LDR	R1, [R0, #0]
MVN	R0, #12288
ANDS	R1, R0
MOVW	R0, #lo_addr(USART1_CR2+0)
MOVT	R0, #hi_addr(USART1_CR2+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,68 :: 		USART1_CR3 &= ~(3<<8);            // Force no flow control and no DMA for USART1
MOVW	R0, #lo_addr(USART1_CR3+0)
MOVT	R0, #hi_addr(USART1_CR3+0)
LDR	R1, [R0, #0]
MVN	R0, #768
ANDS	R1, R0
MOVW	R0, #lo_addr(USART1_CR3+0)
MOVT	R0, #hi_addr(USART1_CR3+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,69 :: 		USART1_CR1 &= ~(3<<9);            // Force no parity and no parity control
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
LDR	R1, [R0, #0]
MVN	R0, #1536
ANDS	R1, R0
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,70 :: 		USART1_CR1 |= 3<<2;               // RX, TX enable
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #12
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,71 :: 		USART1_CR1 |= 1<<13;              // USART1 enable
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #8192
MOVW	R0, #lo_addr(USART1_CR1+0)
MOVT	R0, #hi_addr(USART1_CR1+0)
STR	R1, [R0, #0]
;TommyCozzarelli_Project4.c,72 :: 		Delay_ms(100);                    // Wait for USART to complete configuration and enable.
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_InitializeUSART116:
SUBS	R7, R7, #1
BNE	L_InitializeUSART116
NOP
NOP
NOP
;TommyCozzarelli_Project4.c,73 :: 		}
L_end_InitializeUSART1:
BX	LR
; end of _InitializeUSART1
