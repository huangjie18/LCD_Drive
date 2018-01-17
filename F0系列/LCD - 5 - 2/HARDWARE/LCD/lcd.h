#ifndef  __LCD_H
#define  __LCD_H
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
/* 宏定义  ------------------------------------------------------------------*/
#define Elect_color  black    //选中后的画笔颜色
#define Common_color blue     //普通画笔颜色
#define gui_elect    red      //色条颜色
#define gui_Noelect  black    //色条清除颜色
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
#define  fontcolor      red	  //字体颜色
#define BK_ON()  GPIO_SetBits(GPIOA,GPIO_Pin_9);  //背光开
#define BK_OFF() GPIO_ResetBits(GPIOA,GPIO_Pin_9); //背光关
#define list_y1_start   0
#define list_y2_start   18
#define list_y3_start   36
#define list_y4_start   54
#define list_y5_start   72
#define list_y6_start   90
#define list_y7_start   108
#define list_y1_end     17
#define list_y2_end     35
#define list_y3_end     53
#define list_y4_end     71
#define list_y5_end     89
#define list_y6_end     107
#define list_y7_end     127
/* 函数申明 ------------------------------------------------------------------*/
void LCD_Init(void);
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
void rgb(void);
void address(void);

#endif

