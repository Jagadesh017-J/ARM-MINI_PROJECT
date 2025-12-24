void delay_milliseconds(unsigned int ms)
{
T0PR=60000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0x03;
T0TCR=0x00;
}
void delay_seconds(unsigned int ms)
{
T0PR=60000000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0x03;
T0TCR=0x00;
}
void delay_microseconds(unsigned int ms)
{
T0PR=60-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0x03;
T0TCR=0x00;
}

