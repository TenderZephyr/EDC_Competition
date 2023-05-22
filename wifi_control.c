#include <wifi_control.h>
#include "string.h"
#include <intrins.h>
#include "delay.h"

/**
  * @brief  uart send one byte of data
  * @param  dat: Data to be sent
  * @retval none
  */
void send_b (unsigned char dat)
{
	SBUF = dat;
	while (!TI);
	TI = 0;
}

/**
  * @brief  uart send one string of data
  * @param  *dat��String pointer data to be sent
  * @retval none
  */
void send_s (unsigned char *dat)
{
	while (*dat)
	{
		send_b(*dat++);
	}
}

/*
  * @brief  stc15 uart initialize
  * @param  none
  * @retval none
*/

void uinit()				//115200bps@12.000MHz   
{		
	SCON = 0x50;
    //S1_USE_P36P37();		//set uart I/O
	AUXR |= 0x40;		
	AUXR &= 0xFE;		
	TMOD &= 0x0F;		
	TL1 = 0xE6;		
	TH1 = 0xFF;		
	ET1 = 0;		
	TR1 = 1;		
}

/**
  * @brief  esp8266 initialize
  * @param  none
  * @retval none
  */
void ESP8266_ModeInit (void)
{
 	// send_string("AT+CWJAP=jia,12345678\r\n"); 		//connect WiFi,parameter respectively represent wifi name and password
	// delay1000ms();
	// delay1000ms();
	// delay1000ms();
	// delay1000ms();
	// delay1000ms();
	// connect onenet device��parameter respectively represent device ID��product ID��Authentication information
	send_s("AT+IOTCFG=1074548325,598148,123\r\n");    
	delay1000ms();
	//delay1000ms();	
}

void wifi_control_init (void)
{
	uinit();
	ESP8266_ModeInit();
	ES=1;
}

/**
  * @brief  send temperature data
  * @param  float temp
  * @retval none
  */
void  senddatatemp (float temp)
{
	char buf[50];		//create an array to hold the data
	memset(buf, 0, sizeof(buf));		//clear cache
	sprintf(buf, "AT+IOTSEND=1,temp,%.1f\r\n", temp);  //put the data into an array
	send_s(buf);		//send data stream
}

/**
  * @brief  send humidity data
  * @param  float humi
  * @retval none
  */
void  senddatahumi (int humi)     
{
	char buf[50];		         //create an array to hold the data
	memset(buf, 0, sizeof(buf));		//clear cache
	sprintf(buf, "AT+IOTSEND=1,humi,%d\r\n", humi);		//put the data into an array
	send_s(buf);		//send data stream
}

/**
  * @brief  send smoke judge data
  * @param  int smoke
  * @retval none
  */
void  senddatasmoke (int smoke)  
{
	char buf[50];		//create an array to hold the data
	memset(buf, 0, sizeof(buf));		//clear cache
	sprintf(buf, "AT+IOTSEND=1,smoke,%d\r\n", smoke);		//put the data into an array
	send_s(buf);		//send data stream
}

/**
  * @brief  send illumination intensity data
  * @param  float beam
  * @retval none
  */
void  senddatabeam (int beam)  
{
	char buf[50];		//create an array to hold the data
	memset(buf, 0, sizeof(buf));		//clear cache
	sprintf(buf, "AT+IOTSEND=1,beam,%d\r\n", beam);		//put the data into an array
	send_s(buf);		//send data stream
}

void senddatas(float temp, int humi, int smoke, int lx)    
{
	wifi_control_init();			
	senddatatemp(temp);		//send temperature date to onenet
	delay180ms();//delay1000ms();
	senddatahumi(humi);	//send humidity date to onenet
	delay180ms();//delay1000ms();
	senddatasmoke(smoke);		//send smoke judge date to onenet
	delay180ms();//delay1000ms();
	senddatabeam(lx);	//send illumination intensity data to onenet
	delay180ms();//delay1000ms();		
}