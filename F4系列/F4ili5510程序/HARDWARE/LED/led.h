#ifndef __LCD_H
#define __LCD_H
#include "sys.h"
#include "stdlib.h"

#define LCD_ID  5420   //定义IC9326,4551,5420
#define red  0x001f
#define black 0x0000
#define white 0xffff
#define blue  0x07e0
#define green 0xf800




#define LCD_CS    PGout(12)
#define LCD_RS    PFout(12)
#define LCD_WR    PDout(5)
#define LCD_RD    PDout(4)
#define LCD_DB0   PDout(14)
#define LCD_DB1   PDout(15)
#define LCD_DB2   PDout(0)
#define LCD_DB3   PDout(1)
#define LCD_DB4   PEout(7)
#define LCD_DB5   PEout(8)
#define LCD_DB6   PEout(9)
#define LCD_DB7   PEout(10)
#define LCD_DB8   PEout(11)
#define LCD_DB9   PEout(12)
#define LCD_DB10  PEout(13)
#define LCD_DB11  PEout(14)
#define LCD_DB12  PEout(15)
#define LCD_DB13  PDout(8)
#define LCD_DB14  PDout(9)
#define LCD_DB15  PDout(10)
#define LCD_BL    PBout(15)

#define LCD_DB0_IN   PDin(14)  //0
#define LCD_DB1_IN   PDin(15)  //0
#define LCD_DB2_IN   PDin(0)   //0
#define LCD_DB3_IN   PDin(1)   //0
#define LCD_DB4_IN   PEin(7)   //0
#define LCD_DB5_IN   PEin(8)   //0
#define LCD_DB6_IN   PEin(9)   //0
#define LCD_DB7_IN   PEin(10)  //0
#define LCD_DB8_IN   PEin(11)  //1
#define LCD_DB9_IN   PEin(12)  //1
#define LCD_DB10_IN  PEin(13)  //0
#define LCD_DB11_IN  PEin(14)  //1
#define LCD_DB12_IN  PEin(15)  //1
#define LCD_DB13_IN  PDin(8)   //0
#define LCD_DB14_IN  PDin(9)   //1
#define LCD_DB15_IN  PDin(10)  //1

extern u16 LCD_id;
/*****************函数声名***********************************/
void GPIO_5510_Init(void);  //5510 IO初始化
void LCD_Init(void);
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(int data);
void LCD_Clear(void);
void LCD_IN(void);
void LCD_OUT(void);
u16 LCD_Read(u16 LCD_Reg); //读
#endif
