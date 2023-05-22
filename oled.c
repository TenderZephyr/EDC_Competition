#include "reg51.h"
#include <oled.h>
#include <oledfont.h>  	//ȡģ���ֿ�
#include "OLED_IIc.h"

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

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	   

sbit OLED_SCL = P2^0;			// OLED SCLK ����
sbit OLED_SDIN = P2^1;		// OLED SDA	 ����	

void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
	}
	else 
		{
			Write_IIC_Command(dat);	
		}
}
//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	    
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
/*void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}*/
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			//	OLED_ShowChar(x+(size2/2)*t,y,' ',size2);//�˾�Ϊԭ�䣬��λ�������ص�(size2 = 8 ʱ��size/2 = 4,�ַ�����Ϊ6���أ����ص�)
				if(size2 == 8) OLED_ShowChar(x+(size2/2+2)*t,y,' ',size2);//�˾�Ϊ�޸ľ�,�����������ȴ���1�ص�����				@�����ٳ�	
				else if(size2 == 16) OLED_ShowChar(x+(size2/2)*t,y,' ',size2);//�˾�Ϊ�޸ľ�,�����������ȴ���1�ص����� 		@�����ٳ�
				continue;
			}else enshow=1; 
		}
	// 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); //�˾�Ϊԭ�䣬��λ�������ص�(size2 = 8 ʱ��size/2 = 4,�ַ�����Ϊ6���أ����ص�)
			if(size2 == 8) 	OLED_ShowChar(x+(size2/2+2)*t,y,temp+'0',size2);//�˾�Ϊ�޸ľ�,�����������ȴ���1�ص�����		 		@�����ٳ�	
			else if(size2 == 16) 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);//�˾�Ϊ�޸ľ�,�����������ȴ���1�ص�����		@�����ٳ�
		
	}
} 
//��ʾһ���ַ���
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
    }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
	}					
}

//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  

void OLED_Display(float Temp, u8 vH, int vLx, unsigned int warn)
{
			OLED_ShowCHinese(0 ,0,8);					//(x,y,��)
			OLED_ShowCHinese(18,0,7);					//��
			OLED_ShowChar(36,1,':',8);				//�¸���ʼΪ42(x,y,':',size ��С8λ �¸�x+6)
			OLED_ShowNum(42,0,Temp/1,2,16); // 42+2*8
			OLED_ShowChar(58,1,'.',8);   //58+6
			OLED_ShowNum(64,0,Temp*10,1,16); // 64+8  ��ʾһλ�ȿ�ȡС��  28.5*10-->285-->len=1-->5
			OLED_ShowString(72,0,"'C",16);		
			
			OLED_ShowCHinese(0 ,2,9);					//ʪ
			OLED_ShowCHinese(18,2,7);					//��
			OLED_ShowChar(36,3,':',8);				//�¸���ʼΪ42	
			OLED_ShowNum(42,2,vH,2,16); // 42+2*8
			//OLED_ShowString(42,2,humidity[],16);	//OLED_ShowChar(42,2,humidity,16);   //78+4*8//OLED_ShowFloat(42,2,humidity,2);  //85   42+8*2
			OLED_ShowChar(58,2,'%',16);	
			
			OLED_ShowCHinese(0 ,4,4);					
			OLED_ShowCHinese(18,4,5);			
			OLED_ShowCHinese(36,4,6);					
			OLED_ShowCHinese(54,4,7);		
			OLED_ShowChar(72,5,':',8);	
			OLED_ShowNum(78,4,vLx,4,16);   //78+4*8
			OLED_ShowString(110,4,"LX",16);			
			
			OLED_ShowCHinese(0 ,6,0);				//��	�ӵ�0�У�ռ��0-15����16�У���   ��0ҳ��ռ0-1ҳ��0-16�����أ���Hzk[0]:������
			OLED_ShowCHinese(18,6,1);				//ǰ  �ӵ�18�У���2�У�ռ��18-33�У�����0ҳ��ռ0-1ҳ��0-16�����أ���Hzk[1]:��ǰ��
			OLED_ShowCHinese(36,6,2);				//״	�ӵ�36�У���2�У�ռ��36-51�У�����0ҳ��ռ0-1ҳ��0-16�����أ���Hzk[2]:��ģ��
			OLED_ShowCHinese(54,6,3);				//̬	�ӵ�54�У���2�У�ռ��54-69�У�����0ҳ��ռ0-1ҳ��0-16�����أ���Hzk[3]:��ʽ��
			OLED_ShowChar(72,7,':',8);		// �ӵ�72�����ء���1ҳ����8�����أ���ʼ��ʾ��СΪ6*8���ص��ַ���:��   ��6
		
			if(warn != 1)															//�ж�����0���Ǿ���1
			{
				OLED_ShowCHinese(78,6,10);				//��
				OLED_ShowCHinese(96,6,11);				//��
			}
			else
			{
				OLED_ShowCHinese(78,6,12);				//��
				OLED_ShowCHinese(96,6,13);				//��
			}
}