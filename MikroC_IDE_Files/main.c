typedef enum state_e        // enum function used down!
{
 MotorHold,
 MotorOnLeft1,
 MotorOnLeft2,
 MotorOnLeft3,
 MotorOnRight1,
 MotorOnRight2,
 MotorOnRight3,
 MotorUndefined
 }state_t;
 void Temp_read();

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

int tmp;               /* variables used down! */
int temp_celcius=0;
char tmp1[7]; // used for intToStr function
void main() {
            int i;

            int result;
            long mVolt;
            //char VoltChr[7]; //used in case if we want to display the voltage on lcd
            state_t motor_state = MotorUndefined; // to force entering if statement
            TRISA.B4 =1;  // making TRISA.B4 input to fix an issue with pcb
            TRISB &=~(0x81); // RB0,RB7 Output (LED,BUZZER) PB0 , PB7
            PORTB.F0=0;  // BUZZER OFF
            PORTB.F7=0; // RED_LED OFF
            TRISC.B6=0; // RB6 OUTPUT (RW)
            PORTC.F6=0;  // FORCE WRITE MODE FOR LCD
            TRISC.B0=0; // RB0 OUTPUT( EN)
            PORTC.F0=1; // FORCE ENABLE MODE FOR L293D

delay_ms(50);
LCD_Init(); //Intializes the LCD modules
DElay_ms(20);
ADC_Init(); // Initializes the ADC Module
Delay_ms(20);

/*LCD_OUT(1,1, "Embedded");
delay_ms(1);
LCD_OUT(2,2, "Project");
Delay_ms(300);
Lcd_Cmd(_LCD_CLEAR);
delay_ms(1);       */
PWM1_init(5000); //Intializes the PWM module
PWM2_init(5000);
while(1)
{
while(temp_celcius < 50)
{




/*tmp = ADC_Read(0); // ADC read from RA0

temp_celcius = (( tmp>>1)-1) ; // temp *5 / 10 = 2 = shifting 1 time to right

intToStr(temp_celcius,tmp1[]);// will convert values of tmp to tmp1  */

/*LCD_OUT(2,1, "Temp=           ");
delay_ms(1);
LCD_OUT(2,10,&tmp1[4]);
delay_ms(1);  */

result = ADC_Read(4);
mVolt= (((long)result *5000)>>10 ); // mVolt Calculation 50000 / 1023 = shifting 10 times to right
//longToStr(mVolt,VoltChr);    // in case if we want to display the voltage on lcd
//LCD_OUT(1,1,VoltChr);


 // there's an enum declared to avoid entering the if statement twice without changing states
 if ( mVolt >= 2400 && mVolt <= 2600 && motor_state!=MotorHold)
{   motor_state=MotorHold;
  PWM1_Stop();
  PWM2_Stop();
  Lcd_Cmd(_LCD_CLEAR);
delay_ms(1);
  LCD_Out(1,1,"Motor Hold");
  delay_ms(1);
}
else if (mVolt > 2600 && mVolt <= 3400 && motor_state!=MotorOnLeft1)
{
motor_state=MotorOnLeft1;
PWM1_Set_Duty(33);
PWM1_Start();
PWM2_Stop();
Lcd_Cmd(_LCD_CLEAR);
delay_ms(1);
LCD_Out(1,1,"MotorOnLeft+");
delay_ms(1);
}

  
else if (mVolt > 3400 && mVolt <= 4200 && motor_state!=MotorOnLeft2)
{
motor_state=MotorOnLeft2;
PWM1_Set_Duty(66);
PWM1_Start();
PWM2_Stop();
Lcd_Cmd(_LCD_CLEAR);
delay_ms(1);
LCD_Out(1,1,"MotorOnLeft++");
delay_ms(1);
}
  
else if (mVolt > 4200 && motor_state!=MotorOnLeft3)
{
motor_state=MotorOnLeft3;
PWM1_Set_Duty(100);
PWM1_Start();
PWM2_Stop();
Lcd_Cmd(_LCD_CLEAR);
delay_ms(1);
LCD_Out(1,1,"MotorOnLeft+++");
delay_ms(1);
}
  
  
else if ( mVolt >= 1600 && mVolt < 2400 && motor_state!=MotorOnRight1)
{ motor_state=MotorOnRight1;
  PWM2_Set_Duty(33);
  PWM2_Start();
  PWM1_Stop();
  Lcd_Cmd(_LCD_CLEAR);
  delay_ms(1);
  LCD_Out(1,1,"MotorOnRight+");
  delay_ms(1);
}
else if ( mVolt >= 800 && mVolt <1600 && motor_state!=MotorOnRight2)
{ motor_state=MotorOnRight2;
  PWM2_Set_Duty(66);
  PWM2_Start();
  PWM1_Stop();
  Lcd_Cmd(_LCD_CLEAR);
  delay_ms(1);
  LCD_Out(1,1,"MotorOnRight++");
  delay_ms(1);
}
else if ( mVolt < 800 && motor_state!=MotorOnRight3)
{ motor_state=MotorOnRight3;
  PWM2_Set_Duty(100);
  PWM2_Start();
  PWM1_Stop();
  PWM2_Start();
  Lcd_Cmd(_LCD_CLEAR);
  delay_ms(1);
  LCD_Out(1,1,"MotorOnRight+++");
  delay_ms(1);
  
}
 Temp_read();

}

do{

 Lcd_Cmd(_LCD_CLEAR);
 delay_ms(1);
 LCD_OUT(1,1,"There's a fire");
 LCD_OUT(2,1,"Motor Shutdown");
 delay_ms(1);
 PORTB.F0=1;
 PORTB.F7^=1;
 PWM1_STOP();
 PWM2_STOP();
 delay_ms(100);
 tmp = ADC_Read(0); // ADC read from RA0

 temp_celcius = (( tmp>>1)-1) ; // temp *5 / 10 = 2 = shifting 1 time to right
  motor_state = MotorUndefined;


}while(temp_celcius >50);
 Lcd_Cmd(_LCD_CLEAR);
 delay_ms(1);
 }
 }
 void Temp_read()
 {
 tmp = ADC_Read(0); // ADC read from RA0

temp_celcius = (( tmp>>1)-1) ; // temp *5 / 10 = 2 = shifting 1 time to right

intToStr(temp_celcius,tmp1);// will convert values of tmp to tmp1
 LCD_OUT(2,1, "Temp=");
delay_ms(1);
LCD_OUT(2,10,&tmp1[4]);
delay_ms(1);


 }