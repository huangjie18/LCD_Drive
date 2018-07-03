#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//���ڶ���˵��
/****************************************
MCU���    LCD    MCUʵ������

D0   -     BLK   (PD14)
D2   -     DC    (PD0)
D4   -     RES   (PE7)
D6   -     SDA   (PE9)
D8   -     SCL   (PE11)
D10  -     VCC   (PE13)
D12  -     GND   (PE15)
****************************************/
#define  saomiao   0x68
#define  red       0xf800
#define  green     0x07e0
#define  blue      0x001f
#define  black     0x0000
#define  white     0xFFFF
#define  purple    0xf81f
#define  yellow    0xffe0
#define  cyan      0x07ff
#define  orange    0xfc08
#define  gray      0x8400  //RGB��50%


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

#define BLK  PDout(14)
#define DC   PDout(0)
#define RES  PEout(7)
#define SDA  PEout(9)
#define SCL  PEout(11)

void LCD_Init(void);//��ʼ��
void LCD_GPIO_Init(void); //LCD�ӿڳ�ʼ��
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);	
void Lcd_Initialize(void);   //IC9326
void LCD_Clear(void);

//IC4551����Ҫ��
void Lcd_Initialize_4551(void);
void address(void);
void SLEEPEXIT(void);
void SLEEPON(void);
void display_test(u16 color); //���Գ���
#endif
