#include "config.h"
#include "GPIO.h"

//uart & iic header file
#include <uart.h>

//imporrt module
#include "oled.h"   
#include "DS18B20.h"   
#include "MQ_2.h"
#include "DHT11.h"
#include "BH1750FVI.h"
#include "wifi_control.h"

//define functional function
void fFan(int i);                 //turn on or close fan
void fBuzzer(int i);              //turn on or close buzzer
void init();                      //initialize module

//define global variable
float mTemp = 25.0;                       //max temperature
int vK;                                   //MQ-2
float vTemp;                              //tenperature variable
u8 vH,temp;                                    //huminity
int vLx;                                  //light
int flagMSM = 0;                          //flag for message sending
unsigned int warn = 0;                  

//define pin
sbit buzzer = P0^3;                       //define buzzer's pin
sbit fan = P2^5;                          //define fan's pin

//define I/O output mode
void GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin = GPIO_Pin_2|GPIO_Pin_3;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化
    
	GPIO_InitStructure.Pin = GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_HighZ;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化  

    // GPIO_InitStructure.Pin = GPIO_Pin_5;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	// GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	// GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化  
}

void main()
{
    //initialize all module

    GPIO_Init();
    init();  
    DHT11_Init();
    dht11_gpio_OUT();
	OLED_Init();
    OLED_Clear(); 
    UartInit();
    
    while(1)
    {
        vTemp = DS18B20_ReadT();
        vLx = Receive_Data();
        vK = Smoke1();
        DHT11_Read_Data(&vH);  

        OLED_Display(vTemp, vH, vLx, warn);
        senddatas(vTemp, vH, warn, vLx);

        if((vK == 0) && (vTemp >= mTemp))
        {   
            if(flagMSM == 0)
            {
                Send_text();
                flagMSM ++;
            }
            fFan(0);
            fBuzzer(0);
            warn = 1;
        }
        else
        {
            fFan(1);
            fBuzzer(1);
            flagMSM = 0;
            warn = 0;
        }  
    }
}

//Function to initialize
void init()
{
    fFan(1);
    fBuzzer(0);
}

// Function to turn on fan
void fFan(int i)
{
    fan = i;                //i == 0, fan open, i == 1, fan close
}

//Function to open buzzer
void fBuzzer(int i)
{
    buzzer = i;
}
