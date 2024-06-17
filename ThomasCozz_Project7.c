 //*********************************************************************************************************************************
//Name: Thomas Cozzarelli
//Group Members: Joe Quinn, Mike Perez
//Date: 11/28/2019
//Course: ELEC3371-00
//Description: Recreate the pong classic from 1972, impliment 3 game modes, a timer for last time scored or reset, implimnet 7 segment display
// with Player 1 and Player 2 scores, and a high score that is shown after the game is over as well.
//*********************************************************************************************************************************
// TFT module connections
unsigned int TFT_DataPort at GPIOD_ODR;
sbit TFT_WR at GPIOE_ODR.B9;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_CS at GPIOE_ODR.B12;
sbit TFT_RS at GPIOE_ODR.B8;
sbit TFT_RST at GPIOE_ODR.B13;
// End TFT module connections
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_PA5);// set port E as a digital output
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_PA4);// set port E as a digital output
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_PB1);// set port E as a digital output
GPIO_Digital_Input(&GPIOB_IDR, _GPIO_PINMASK_PB0);// set port E as a digital output
GPIO_Digital_Input(&GPIOE_IDR,_GPIO_PINMASK_PE6);// set


//Initalizations of all of the paddles and balls
int paddely1 = 0;
int paddely2 = 0;
int paddelx1 = 0;
int paddelx2 = 0;
int ballx = 0;
int bally = 0;




void main() {
// Initialize 240x320 TFT display
TFT_Image(0, 0, 153608, 1);                          //This would be the splash screen image on our Title Screen


TFT_Init_ILI9341(240, 320);                          //This initalizes our main LCD display with the correct width and height
TFT_V_Line(5, 25, 10);                               //This initalizes the first paddle
TFT_V_Line(10, 50, 20);                              //This initalizes the second paddle
TFT_Circle(120, 64, 110);                            //This will initalize the ball in the center of the screen


//Function of the ball moving around











}