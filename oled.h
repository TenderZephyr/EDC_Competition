#ifndef __OLED_H
#define __OLED_H			  	 

#define  u8 unsigned char 
#define  u32 unsigned int
//-----------------OLED�˿ڶ���----------------  					   

void delay_ms(unsigned int ms);

//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_Display(float vTemp,u8 vH, int vLx,unsigned int warn);

#endif  
