
void INTI();
void CMD(unsigned char);
void DATA(unsigned char);
void STR(unsigned char*);
void INTEGER(unsigned char );
void FLOAT(float );
void BINARY(unsigned char );



#define DP 0xff<<23
#define RS 1<<18
#define E 1<<19


void INTI()
{
IODIR1|=DP|RS|E;
CMD(0X01);
CMD(0X02);
CMD(0X0C);
//CMD(0X0f);
CMD(0X38);
CMD(0x80);
}

void CMD(unsigned char cmd)
{
IOCLR1=DP;
IOCLR1=RS;
IOSET1=cmd<<23;

IOSET1=E;
delay_ms(2);
IOCLR1=E;

//IOCLR1=DP;
//IOCLR1=RS;
//IOSET1=(cmd&0xf)<<27;
//
//IOSET1=E;
//delay_ms(2);
//IOCLR1=E;

}

void DATA(unsigned char data)
{
IOCLR1=DP;
IOSET1=RS;
IOSET1=data<<23;

IOSET1=E;
delay_ms(2);
IOCLR1=E;

//IOCLR1=DP;
//IOSET1=RS;
//IOSET1=(data&0x0f)<<27;
//
//IOSET1=E;
//delay_ms(2);
//IOCLR1=E;

}


void STR(unsigned char*s)
{
while(*s)
{
DATA(*s++);
}
}


void INTEGER(unsigned char num)
{
unsigned char var[20];
signed char i=0;
if(num=='0')
DATA('0');
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
unsigned char i;
for(i=7;i>=0;i--)
DATA(((num>>i)&1)+48);
}

/* void SPL(unsigned char bytes )
{
unsigned char i;
CMD(0X40);
for(i=0;i<bytes;i++)
DATA(spl_lut[1]);
}  */


