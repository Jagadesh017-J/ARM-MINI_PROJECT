#include<LPC21XX.H>
#include<string.h>
#include"uart.h"

void delay_seconds(unsigned char s)
{
T0PR=15000000-1;
T0TCR=0X01;
while(T0TC<s);
T0TCR=0X03;
T0TCR=0X00;
}

/*void can2_init(void);
typedef unsigned int u32;
typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}message;
void can2_tx(message);*/
unsigned char member[3][15];
unsigned char temp[15];
unsigned char UART0_RX(void)
{
while(((U0LSR>>0)&1)==0);
return U0RBR;
}
int main()
{
   char read;
	int i,j;
	//message m1;
	
	//can2_init();
	UART0_CONFIGURE();
	uart_str("ready");
	for(i=0;i<3;i++)
	{
		for(j=0;j<12;j++)
			temp[j]=UART0_RX();
		/*temp[j]='\n';
		temp[j+1]='\r';*/
		temp[j]='\0';
		read=U0RBR;
		
		//strcpy(temp,member[i]);
		strcpy(member[i],temp);
		uart_str("ok");
		UART0_TX('\r');
		UART0_TX('\n');
		uart_str(member[i]);
			UART0_TX('\r');
		UART0_TX('\n');
		
	}
	while(1)
	{
	/*m1.id=0x000001AF;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=DISTANCE;
	m1.byteB=0;

	*/	 for(j=0;j<12;j++)
			temp[j]=UART0_RX();
			temp[j]='\0';
			read=U0RBR;
	
			uart_str(temp);
			UART0_TX('\r');
		UART0_TX('\n');
		for(i=0;i<3;i++)
		{
			if(strcmp(temp,member[i])==0)	
			{
				if(i==0)
				{
				uart_str("member1");
				UART0_TX('\r');
		UART0_TX('\n');
		}
				//m1.byteA=1
				else if(i==1)
				{
				//m1.byteA=2
				 uart_str("member2");
				 UART0_TX('\r');
		UART0_TX('\n');
		}
				else if(i==2)
				{
				//m1.byteA=3
				uart_str("member3" );
				UART0_TX('\r');
		UART0_TX('\n');

		}
			}
		}
	//can2_tx(m1);
	}
}


/*void can2_init(void)
{
	PINSEL1|=0x00014000;//P0.23-->RD2 & P0.24-->TD2
	VPBDIV=1; //PCLK=60MHz
	C2MOD=0x1; //CAN2 into Reset  Mode 
	AFMR=0x2; //accept all receiving messages(data/remote)	
	C2BTR=0x001C001D; //B125Kbps @ PLCK=60MHz(BRP=Pclk/bit rate*16)
	C2MOD=0x0; //CAN1 into Normal Mode
}
void can2_tx(CAN2_MSG m1)
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
 */
