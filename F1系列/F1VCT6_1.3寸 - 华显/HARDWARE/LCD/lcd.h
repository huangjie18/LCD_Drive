#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//串口定义说明
/****************************************
MCU标号    LCD    MCU实际引脚
PB7       LEDK      PB7
PB6       LEDA      PB6
PB5       GND       PB5
PB4       VCC       PB4
PB3       IOVCC     PB3
PB2       CS        PB2
PB1       RESET     PB1
PB0       SCL       PB0
CS        SDA       PD7
RS        GND       PD11
RW        RS        PD5
RD        GND       PD4

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
#define  gray      0x8400  //RGB各50%

#define LEDK_1      PBout(7)
#define LEDA_1      PBout(6)
#define GND_1       PBout(5)
#define VCC_1       PBout(4)
#define IOVCC_1     PBout(3)
#define CS_1        PBout(2)
#define RES_1       PBout(1)
#define SCL_1       PBout(0)
#define SDA_1       PDout(7)
#define RS_1        PDout(5)
#define DC_1        RS_1

void LCD_Init_1(void);//初始化
void LCD_GPIO_Init_1(void); //LCD接口初始化
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);	
void Lcd_Initialize(void);   //IC9326
void LCD_Clear(void);

//IC4551必须要的
void Lcd_Initialize_4551(void);
void address(void);
void SLEEPEXIT(void);
void SLEEPON(void);
void display_test_1(void); //测试程序
#endif
