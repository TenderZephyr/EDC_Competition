#ifndef __OLED_IIc_H
#define __OLED_IIc_H			  	 

void OLED_IIC_Start();
void OLED_IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void O_IIC_Wait_Ack();

#endif