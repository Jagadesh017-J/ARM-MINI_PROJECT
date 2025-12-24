 #include<LPC21XX.H>
 void delay_sec(unsigned int );
 void delay_milli_sec(unsigned int );
 void delay_ms(unsigned int );
 
 void delay_sec(unsigned int sec )
 {
 T0PR=60000000-1;
 T0TCR=1;
 while(T0TC<sec);
 T0TCR=3;
 T0TCR=0;
 }

 void delay_milli_sec(unsigned int sec )
 {
 T0PR=60000-1;
 T0TCR=1;
 while(T0TC<sec);
 T0TCR=3;
 T0TCR=0;
 }

 void delay_ms(unsigned int sec )
 {
 T0PR=60000-1;
 T0TCR=1;
 while(T0TC<sec);
 T0TCR=3;
 T0TCR=0;
 }

