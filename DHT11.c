#include "DHT11.h"
#include "intrins.h"
#include "GPIO.h"
#include "oled.h"
#include "delay.h"

sbit DHT11_DQ = P1^2;

void dht11_gpio_OUT()
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin = GPIO_Pin_2;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����?
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);   //��ʼ��
}

u8 DHT11_Init(void)
{
	
	DHT11_DQ = 1;
	DHT11_Rst();	  
	return DHT11_Check();	
}


void DHT11_Rst(void)	   
{ 

	DHT11_DQ = 1;
	delay10us();
	DHT11_DQ = 0; 	
	delay_ms(25);  
	DHT11_DQ = 1; 	
	delay30us();  
}

//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
u8 DHT11_Check(void) 	   
{   
	u8 retry = 0;

	while (!DHT11_DQ && retry < 100)    //�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����?
	{
		retry ++;
		_nop_();
	}
	if(retry >= 100)
	{
		return 1;
	}
	else
	{
		retry = 0;
	} 
    while (DHT11_DQ && retry < 100)     //�жϴӻ����� 80us �ĸߵ�ƽ�Ƿ������������������������ݽ���״̬
	{
		retry ++;
		_nop_();
	};	 
	if(retry >= 100)return 1;	    
	return 0;
}

//��DHT11��ȡһ���ֽ�
//����ֵ������������

u8 DHT11_Read_Byte(void)    
{        
    u8 i,temp;
	unsigned char data_byte=0; 
	u8 retry=0;

	for(i = 0; i < 8; i ++)//接收8bit的数据 
	{ 
//		while(!DHT11_DQ);//等待50us的低电平开始信号结束
		while (!DHT11_DQ&&retry<50)//等待50us的低电平开始信号结束
		{
			retry++;
			_nop_();
		};
		retry=0; 
		delay30us();//等待40us 
		temp=0;//时间为26us-28us表示接收的为数据'0' 
		if(DHT11_DQ==1) 
			temp=1; //如果26us-28us之后还为高电平则表示接收的数据为'1' 
//		while(DHT11_DQ);//等待数据信号高电平'0'为26us-28us'1'为70us
		while (DHT11_DQ&&retry<100)//等待数据信号高电平'0'为26us-28us'1'为70us
		{
			retry++;
			_nop_();
		};
		data_byte<<=1;//接收的数据为高位在前右移 
		data_byte|=temp; 
	} 
	return data_byte;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��

u8 DHT11_Read_Data(u8 *humi)      //u8 *temp,u8 *humi
{        
	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check() == 0)
	{
		for(i=0;i<5;i++)					//��ȡ40λ����
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi = buf[0];
			//*temp=buf[2];
		}
		
		return 1;
	}
	
	// else
	return 0;
	
}