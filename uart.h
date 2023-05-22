#ifndef __uart_H
#define __uart_H

#include <config.h>

void Delay1s();
void Send_Byte1(u8 dat);
void Send_String(u8 *dat);
void UartInit(void);
void Send_text();

#endif