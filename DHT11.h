#ifndef _DHT11_H
#define _DHT11_H

#include "delay.h"

//��������
void dht11_gpio_OUT();
u8 DHT11_Init(void);                       //DHT11��ʼ�� 
void DHT11_Rst(void);                      //��λDHT11
u8 DHT11_Check(void);                      //�ȴ�DHT11�Ļ�Ӧ
u8 DHT11_Read_Byte(void);                 //��DHT11��ȡһ���ֽ�
u8 DHT11_Read_Data(u8 *humi);    //��DHT11��ȡһ������

#endif