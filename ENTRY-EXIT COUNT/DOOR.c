#include <LPC21xx.h>


#include "Delay.h"
#include "LCD HEADER.h"
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"


#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13
#define LED5 15                                                                                                    


signed char total=0;

void EXT0_CONF(void);

void EXT0_ISR() __irq
{
		
	delay1_ms(200);  	
	if(total<10)
	total++;
	i2c_eeprom_write(0x50,0X00,total);
	EXTINT=0X01;
	VICVectAddr=0;
}

void EXT1_ISR() __irq
{
	delay1_ms(200); 
	if(total>0)
	total--;
	i2c_eeprom_write(0x50,0X00,total);
	 EXTINT=0X02;
	 
	VICVectAddr=0;
}

void EXT0_CONF(void)
{
	VICIntSelect=0;
	VICVectCntl0=0x20|14;
	VICVectAddr0=(int)EXT0_ISR;

	VICVectCntl1=0x20|15;
	VICVectAddr1=(int)EXT1_ISR;
}



int main()
{
	PINSEL1|=0X01;
	PINSEL0|=0X20000000;
	IODIR0|=(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
	IOSET0|=(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5); 
 	INTI();//lcd
	init_i2c();
	EXT0_CONF();
	EXTMODE=0X03;
	EXTPOLAR=0X03;
	total=i2c_eeprom_read(0X50,0X00);
	VICIntEnable=1<<14|1<<15; 
	STR("V24CE9J3");
	
	while(1)
	{
	        CMD(0xc0);
			STR("COUNT:");
            INTEGER(total);
			if(total>10)
			total=0;

		if(total<=1)
		{
			IOCLR0|=1<<LED1;
			IOSET0|=(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
		}
		else if(total==0)
		{
			IOSET0|=(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
		}
		else if(total<=3)
		{
			IOCLR0|=(1<<LED1)|(1<<LED2)|(1<<LED3);
			IOSET0|=(1<<LED4)|(1<<LED5);
		}
		else if(total>=5)
		{
			IOCLR0|=(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
		}
			
	}


}
