void delay_sec(unsigned int);
void delay_ms(unsigned int);
void delay_microsec(unsigned int);
void delay1_ms(unsigned int ms);
void delay_sec(unsigned int sec)
{
	T0PR=15000000-1;
	T0TCR=0X01;
	while(T0TC<sec);
	T0TCR=0X03;
	T0TCR=0X00;
}

void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}

void delay_microsec(unsigned int sec)
{
	T0PR=15-1;
	T0TCR=0X01;
	while(T0TC<sec);
	T0TCR=0X03;
	T0TCR=0X00;
}
void delay1_ms(unsigned int ms)
{
	T1PR=15000-1;
	T1TCR=0X01;
	while(T1TC<ms);
	T1TCR=0X03;
	T1TCR=0X00;
}
