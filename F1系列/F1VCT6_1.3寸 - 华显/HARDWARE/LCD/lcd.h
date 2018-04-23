#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//���ڶ���˵��
/****************************************
MCU���    LCD    MCUʵ������
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
#define  gray      0x8400  //RGB��50%

#define LEDK      PBout(7)
#define LEDA      PBout(6)
#define GND       PBout(5)
#define VCC       PBout(4)
#define IOVCC     PBout(3)
#define CS        PBout(2)
#define RES       PBout(1)
#define SCL       PBout(0)
#define SDA       PDout(7)
#define RS        PDout(5)
#define DC        RS

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
void display_test(void); //���Գ���
#endif
