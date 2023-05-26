#include <uart.h>
#include "delay.h"

#define u8 unsigned char
#define u32 unsigned int

void Send_Byte1(u8 dat)
{
    IE2 = 0;
	S2BUF=dat;
	while(!(S2CON & 0x02));
	S2CON &= 0xFD;
    IE2 = 1;
}
void Send_String(u8 *dat)
{
	while(*dat)
	{
		Send_Byte1(*dat++);
	}
}


void UartInit(void)		//9600bps@12MHz  
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xC7;			//设置定时初始值
	T2H = 0xFE;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
}


void Send_text()
{
    Send_String("AT\r\n");

    delay1000ms();
    Send_String("AT+CMGF=1\r\n");

    delay1000ms();
    Send_String("AT+CSMP=17,167,2,25\r\n");
    delay1000ms();
    Send_String("AT+CSCS=\"UCS2\"\r\n");
    delay1000ms();
    Send_String("AT+CMGS=\"00310037003800370036003000370038003600370036\"\r\n");
    delay1000ms();
    Send_String("4ED35E936709706B707E98848B66");
    delay1000ms();
    Send_Byte1(0x1A); 
    delay1000ms();
    delay1000ms();
    delay1000ms();
    delay1000ms();
    delay1000ms();                //TODO  reduce delay? 
}