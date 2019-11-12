
unsigned short int Checker=0;
unsigned short int Counter=0;
Sbit R1 at PORTB.B0;
Sbit R2 at PORTB.B1;
Sbit R3 at PORTB.B2;
Sbit C1 at PORTB.B3;
Sbit C2 at PORTB.B4;
Sbit C3 at PORTB.B5;

void main(void)
{


                     ADCON0=6;
                     TrisA=0;  // PORTA AS OUTPUT
                     PORTA=0;
                     TrisB=0b00111000; // PORTB b0..b2 O/P | b3..b6 I/P

                     while(1)
                      {
                      
                      if ( Counter == 4 )    // 4 Digits entered and Wrong Password
                       {
                       Counter = 0;
                       PORTA.b1 = 1;     // Turn on Red Led
                       delay_ms(5000);  // 5 sec delay
                       PORTA.b1 = 0;   // Turn off Red Led
                       }
                      PORTB = 1; // R1 = 1, R2 = 0 , R3 = 0
                      if (R1 == 1 && C1 == 1 )
                       {
                       Checker = 0;
                       Counter++;
                       }
                      if (R1 == 1 && C2 == 1 )
                       {
                       Checker = 0;
                       Counter++;
                       }
                       if (R1 == 1 && C3 == 1 )
                       {
                       Checker = 0;
                       Counter++;
                       }

                       PORTB=2; // R1 = 0, R2 = 1 , R3 = 0
                      if (R2 == 1 && C1 == 1 )
                       {
                       Checker = 0;
                       Counter++;
                       }
                      if (R2 == 1 && C2 == 1 )
                       {
                       if (Checker == 2)
                       Checker = 3;
                       else
                       {
                       Checker = 0;
                       Counter++;
                       }
                       }
                       if (R2 == 1 && C3 == 1 )
                       {
                       if ( Checker == 1 )
                       Checker = 2;
                       else
                       {
                       Checker = 0;
                       Counter++;
                       }
                       }


                       PORTB=4; // R1 = 0, R2 = 0 , R3 = 1
                       if (R3 == 1 && C1 == 1 )
                       {
                       if (Checker == 3)
                       {
                        Checker = 4; // Password is right
                        PORTA.b0 = 1; // Turn on Green Led
                        delay_ms(10000); // 10 sec delay
                        PORTA.b0 = 0; // Turn off Green Led
                       }
                       else
                       { Checker = 0;
                         Counter++;
                       }
                       }
                       if (R3 == 1 && C2 == 1 )
                       {
                        Checker = 1;
                       
                       }
                       if (R3 == 1 && C3 == 1 )
                       {
                       Checker = 0;
                       Counter++;
                       }
                         
                      }

}
