                           /* i2c_eeprom.h */
#define __I2C_EEPROM_H__

void i2c_eeprom_write(u8,u8,u8);
u8   i2c_eeprom_read(u8,u8);
void i2c_eeprom_page_write(u8 slaveAddr,u8 wBuffStartAddr,u8 *p,u8 nBytes);
void i2c_eeprom_seq_read(u8 slaveAddr,u8 rBuffStartAddr,u8 *p,u8 nBytes);

void i2c_eeprom_write(u8 slaveAddr,u8 wBuffAddr,u8 dat)
{
  i2c_start();			   
  i2c_write(slaveAddr<<1); 
	i2c_write(wBuffAddr);    
	i2c_write(dat);   	
	i2c_stop();
	delay1_ms(10);
}			 

u8 i2c_eeprom_read(u8 slaveAddr,u8 rBuffAddr)
{
	u8 dat;
	i2c_start();	
  i2c_write(slaveAddr<<1); 
	i2c_write(rBuffAddr);   
	i2c_restart();	
	i2c_write(slaveAddr<<1|1);
  dat=i2c_nack();	
	i2c_stop();
	return dat;
}
