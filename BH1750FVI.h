#ifndef __BH1750FVI_H
#define __BH1750FVI_H

#include  <config.h>	
#include  <math.h>                                          //Keil library  
#include  <stdio.h>                                         //Keil library	
#include  <INTRINS.H>

void  Single_Write_BH1750(u8 REG_Address);                  //����д������
u8 Single_Read_BH1750(u8 REG_Address);                      //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_BH1750();                               //�����Ķ�ȡ�ڲ��Ĵ�������
void Init_BH1750(void);
void BH1750_Start();                    //��ʼ�ź�
void BH1750_Stop();                     //ֹͣ�ź�
void BH1750_SendACK(bit ack);           //Ӧ��ACK
bit  BH1750_RecvACK();                  //��ack
void BH1750_SendByte(u8 dat);           //IIC�����ֽ�д
u8 BH1750_RecvByte(); 
u16 Receive_Data();                     //IIC�����ֽڶ�

#endif  