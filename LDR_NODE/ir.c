#include<LPC21XX.H>

#include"header.h"
#include"delay.h"
#include"lcd_header.h"

int main()
{
	CAN2_MSG m1;
	//m2;
	INTI();
	can2_init();
	/*sending data frame*/
	m1.id=0x0000011C;//ldr
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0x1;
	m1.byteB=0;

	STR("jaga ");
	delay_ms(1000);

	while(1)
	{
		CMD(0x01);
		
	 if(((IOPIN0>>15)&1)==1)
	 {
	 STR(" DARK ");
	 m1.byteA=0x1;			  
	 	//can2_tx(m1);//data-frame
		delay_ms(1000);	
	 }
	 else
	 {
	 STR(" LIGHT ");
	 m1.byteA=0x00;
	 //can2_tx(m1);//data-frame
		delay_ms(1000);
	 }
	  can2_tx(m1)
	 }
	 }


