#include "reg51.h"
#include "oled.h"

#define OLED_CMD  0			//д����
#define OLED_DATA 1			//д����
#define OLED_MODE 0

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1

sbit OLED_SCL=P2^0;			// OLED SCLK ����
sbit OLED_SDIN=P2^1;		// OLED SDA	 ����	
/**********************************************
//IIC Start
**********************************************/
void OLED_IIC_Start()
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void OLED_IIC_Stop()
{
OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void O_IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
	O_IIC_Wait_Ack();	
    Write_IIC_Byte(0x00);			//write command
	O_IIC_Wait_Ack();	
    Write_IIC_Byte(IIC_Command); 
	O_IIC_Wait_Ack();	
    OLED_IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	O_IIC_Wait_Ack();	
    Write_IIC_Byte(0x40);			//write data
	O_IIC_Wait_Ack();	
    Write_IIC_Byte(IIC_Data);
	O_IIC_Wait_Ack();	
    OLED_IIC_Stop();
}
