#ifndef  __7735R_H
#define  __7735R_H
#include "sys.h"


/*********************************************
PA0  --   D2
PA1  --   D1
PA2  --   D0
PA3	 --	  D3
PA4  --   D4
PA5  --   D5
PA6  --   D6
PA7  --   D7
PA8  --   WR
PA9  --   BK 
PA10 --   
PA11 --
PA12 --
PA13 --
PA14 --

PB0  --   CS
PB1  --   RS

*********************************************/

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
#define  fontcolor      orange	  //字体颜色



void TFT_Init(void);
void LCD_WR_command(unsigned char addr1);
void LCD_WR_para(unsigned char para);
void LCD_WR_data(unsigned char data_1,unsigned char data_2);
void display_pic(u16 bk);
void showshuzi(u8 x,u8 y,u16 num,u16 bk);
u32 mypow(u8 m,u8 n);
void LCD_qu(u8 x,u8 y,u8 xend,u8 yend);
void showchar(u8 x,u8 y,u8 num,u16 bk);
void qingqu(u8 x,u8 y,u16 bk);
void SetBkColor(u8 y,u16 bk);//设置选中背景色

void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);//画点函数
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color); //快速填充
#endif

