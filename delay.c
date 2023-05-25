#include "delay.h"

void delay_ms(u16 ms)
{
    unsigned int i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i)	;   //14T per loop
    }
	while(--ms);
}

void delay30us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 87;
	while (-- i);
}

void delay10us()		
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 27;
	while (-- i);
}

void delay180ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 8;
	j = 145;
	k = 99;
	do
	{
		do
		{
			while (--k);
		} 
        while (--j);
	} 
    while (--i);
}

void delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	}
    while (--i);
}

void delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}

void delay1000ms()
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void delay500us()		                  //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do{
		while (--j);
	} while (--i);
}

void delay70us()		//@11.0592MHz
{
	unsigned char i;

	i = 191;
	while (--i);
}

void delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 135;
	while (--i);
}
