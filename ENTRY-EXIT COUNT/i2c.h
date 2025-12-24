
#define __I2C_H__

#define __I2C_DEFINES_H__

#define SCL_EN  0x00000010
#define SDA_EN  0x00000040

#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)

#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6


#include "types.h"
void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_write(u8);
u8   i2c_read(void);
u8 i2c_ack(void);
u8 i2c_nack(void);
u8 i2c_masterack(void);

void init_i2c(void)
{
	  PINSEL0|=SCL_EN|SDA_EN;
	 I2SCLL=LOADVAL;
	 I2SCLH=LOADVAL;
	 I2CONSET=1<<I2EN_BIT; 
}	

void i2c_start(void)
{
  I2CONSET=1<<STA_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<STA_BIT;
}	

void i2c_restart(void)
{
	I2CONSET=1<<STA_BIT;
	I2CONCLR=1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<STA_BIT;
}	

void i2c_write(u8 dat)
{
	I2DAT=dat;	
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
}	

void i2c_stop(void)
{
	I2CONSET=1<<STO_BIT;	
	I2CONCLR = 1<<SI_BIT;	
}

u8 i2c_nack(void)
{	
	I2CONSET = 0x00; 
  I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}

u8 i2c_masterack(void)
{	
	I2CONSET = 0x04; 
  I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 0x04;
 	return I2DAT;
}	
