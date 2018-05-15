#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//���ڶ���˵��
/****************************************
MCU         LCD

//1.3��
PB7   -     DC   
PB5   -     RES    
PB3   -     SDA   
PB1   -     SCL   
PD7   -     VCC   
PD5   -     GND   
 
//0.96��
PE12  -     BLK
PE14  -     CS
PD8   -     DC
PD10  -     RES
PB12  -     SDA
PB14  -     SCL
PC4   -     VCC
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

//1.3��
#define DC   PBout(7)
#define RES  PBout(5)
#define SDA  PBout(3)
#define SCL  PBout(1)
//0.96��
#define BLK_0  PEout(12)
#define CS_0   PEout(14)
#define DC_0   PDout(8)
#define RES_0  PDout(10)
#define SDA_0  PBout(12)
#define SCL_0  PBout(14)
#define VCC_0  PCout(4)

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

void LCD_Init(void);//��ʼ��1.3������ST7789V����
void LCD_Init_1(void);
void LCD_GPIO_Init(void); //LCD�ӿڳ�ʼ��
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);	
void Lcd_Initialize(void);   //IC9326
void LCD_Clear(void);

//IC4551����Ҫ��
void Lcd_Initialize_4551(void);
void SLEEPEXIT(void);
void SLEEPON(void);
void display_test(void);//���Գ���

//0.96����
void LCD_GPIOInit_0(void); //���ų�ʼ����ST7735S����
void LCD_Init_0(void); //0.96����
void display_rgb(void); //��ʾ��ɫ
void display_test_1(void);
#endif
