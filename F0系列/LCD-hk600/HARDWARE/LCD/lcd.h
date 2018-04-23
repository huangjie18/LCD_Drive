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


//创建实例


void LCD_Init(void);
void display_rgb(unsigned int dat);
void LCD_GPIO_Init(void);
#endif

