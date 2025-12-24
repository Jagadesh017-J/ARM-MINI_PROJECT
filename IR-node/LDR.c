#include<LPC21XX.H>
#include"delay.h"
#define LED 1<<2 
#define LDR 3 
void can2_init(void);
typedef unsigned int u32;
typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}message;
void UART0_TX(unsigned char data)
{
while(((U0LSR>>5)&1)==0);
U0THR=data;
}



void uart_str(char *s)
{
while(*s)
{
UART0_TX(*s++);
}
}
void can2_tx(message);
int main()
{
message m1;
can2_init();

        m1.id=0x000001AF;//ir
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteB=0;
while(1)
{
if(((IOPIN0>>3)&1)==0)
{
m1.byteA=0;

delay_milliseconds(500);
}
else if((IOPIN0>>3)&1)
{
m1.byteA=1;
uart_str("Test off");
delay_milliseconds(500);
}
can2_tx(m1);
delay_seconds(3);
}
}

  
void can2_init(void)
{
	PINSEL1|=0x00014000;//P0.23-->RD2 & P0.24-->TD2
	VPBDIV=1; //PCLK=60MHz
	C2MOD=0x1; //CAN2 into Reset  Mode 
	AFMR=0x2; //accept all receiving messages(data/remote)	
	C2BTR=0x001C001D; //B125Kbps @ PLCK=60MHz(BRP=Pclk/bit rate*16)
	C2MOD=0x0; //CAN1 into Normal Mode
}
void can2_tx(message m1)
{
    C2TID1=m1.id;
	C2TFI1=(m1.dlc<<16);	
	if(m1.rtr==0) //if data frame
	{
		C2TFI1&=~(1<<30);//RTR=0
		C2TDA1=m1.byteA; //lower 4bytes of data
		C2TDB1=m1.byteB; //upper 4bytes of data
	}
	else
	{
		C2TFI1|=(1<<30); //RTR=1
	}
	C2CMR=(1<<0)|(1<<5);
	while((C2GSR&(1<<3))==0);//wait for data Xmission.
}
 

