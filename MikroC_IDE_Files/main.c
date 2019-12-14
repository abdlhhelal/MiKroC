 //Lcd pinout settings
sbit LCD_RS at RC5_bit;
sbit LCD_EN at RC7_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;
//Pin direction
sbit LCD_RS_Direction at TRISC5_bit;
sbit LCD_EN_Direction at TRISC7_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;
int vref = 5 ; // its your applied voltage change if 3.3 or 3.7 etc
int tmp;   // intialzie variable int as tmp
int temp_celcius;
char tmp1[3]; // intialize char to store a string of 3 chars
void main() {


LCD_Init(); //Intializes the LCD modules
DElay_ms(20);
//ADC_Init(); // Initializes the ADC Module for ADC Conversions
Delay_ms(20);

LCD_OUT(1,1, " Learning ");// LCD Will display at row 1 column 1 Learning.
LCD_OUT(2,2, "Microcontrollers"); // LCD Will display at row column 2 Microcontrollers.
Delay_ms(1000); // Will display this for 2 seconds
Lcd_Cmd(_LCD_CLEAR); // Will clear LCD for new valuse to be displayed
while(1) // Needed for operations its an internal loop which keeps on executing
{
tmp = ADC_Read(0); // ADC read from pin AN 0
Delay_ms(50);

temp_celcius = ((( tmp * vref )/ 10)-1) ;
delay_ms(20);

IntToStr(temp_celcius, tmp1);// will convert values of tmp to tmp1
delay_ms(20);

// Now we can display this string on LCD

Lcd_Cmd(_LCD_CLEAR); // Precaution clear for readings to be displayed

LCD_OUT(1,1, "Temp = ");
LCD_OUT(1,10,tmp1); // I changed column number to display result after above helping string
Delay_ms(300); // Keep displaying same value for 0.5 sec

Lcd_Cmd(_LCD_CLEAR); // Then clear LCD for new values
}
}