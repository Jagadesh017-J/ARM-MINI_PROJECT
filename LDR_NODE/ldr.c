/*#include <LPC21XX.H>
#include "header.h"
#include "can2_driver.c"

#define led (1<<12)

int main()
{
    CAN2_MSG m1;
    can2_init();
    IODIR0 |= led;    

    /* sending data f
    m1.id = 0x000001AF;
    m1.rtr = 0;        
    m1.dlc = 4;
    m1.byteA = 0x1;
    m1.byteB = 0;

    while(1)
    {
        if(((IOPIN0 >> 17) & 1) == 1)
        {
            can2_tx(m1);    
            delay_s(1);
            IOCLR0 = led;
        }
        else
        {
            IOSET0 = led;
        }
    }
}
	   */


	   #include<LPC21XX.H>

#include"header.h"

#include"can2_driver.c"

int main()
{
	CAN2_MSG m1;
	//m2;
	can2_init();
	/*sending data frame*/
	m1.id=0x000001AF;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0x1;
	m1.byteB=0;
	 if(((IOPIN0>>15)&1)==0)
	 {
	 	can2_tx(m1);//data-frame
		delay_sec(1);	
	 }
}

void delay_sec(u32 sec)
{
	T0PR=15000000-1;
 T0TCR=1;
 while(T0TC<sec);
 T0TCR=3;
 T0TCR=0;
}

