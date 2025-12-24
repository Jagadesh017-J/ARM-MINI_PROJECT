void INTI(void);
void DATA(unsigned char);
void CMD(unsigned char);
void STR(unsigned char*);
void INTEGER(signed char );
void FLOAT(float );
void BINARY(unsigned char );
void LCD_SCROLL(unsigned char*,unsigned char);
void LCD_ROTATE(unsigned char*,unsigned char);


#define DP 0xff<<23
#define RS 1<<8
#define E 1<<9


void INTI(void)
{
IODIR0|=RS|E;
IODIR1|=DP;
CMD(0X01);
CMD(0X02);
CMD(0X0C);
CMD(0X38);
CMD(0X80);
}

void CMD(unsigned char cmd)
{
//IOCLR0=RS|E;
IOCLR1=DP;
IOSET1=cmd<<23;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}

void DATA(unsigned char data)
{
//IOCLR0=RS|E;
IOCLR1=DP;
IOSET1=data<<23;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}


void STR(unsigned char*s)
{
while(*s)
{
DATA(*s++);
}
}

void LCD_ROTATE(unsigned char*s,unsigned char data )
{
unsigned char i,n,j;
for(n=0;s[n];n++);
j=n;
for(i=0;i<16;i++)
{
 CMD(0X01);
 CMD(data+i);
 STR(s);
 if((16-j)<i)
 {
 CMD(0X01);
 STR(s+(--n));
 }
 delay_ms(500);

}

}

void INTEGER(signed char num)
{
unsigned char var[20];
signed char i=0;
if(num==0){
DATA('0');
return;
}
if(num<0)
{
DATA('-');
num=-num;
}
while(num>0)
{
var[i++]=(num%10);
num=num/10;
}
for(i=--i;i>=0;i--)
DATA(var[i]+48);
}


void FLOAT(float data )
{
unsigned int temp=(int)data;
INTEGER(temp);
DATA('.');
temp=(data-temp)*100;
INTEGER(temp);
}

void BINARY(unsigned char num )
{
signed char i;
for(i=7;i>=0;i--)
DATA(((num>>i)&1)+48);
}

void LCD_SCROLL(unsigned char*s,unsigned char data)
{
  unsigned char i;
  for(i=0;i<16;i++)
  {
  CMD(0X01);
  CMD(data++);
  STR(s);
  delay_ms(500);
  }

}
