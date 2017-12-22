#ifndef __LCD_H
#define __LCD_H
#include "sys.h"
#include "stdlib.h"

#define LCD_ID  4551   //定义IC
#define red  0x001f
#define black 0x0000
#define white 0xffff
#define blue  0x07e0
#define green 0xf800


#define RST PBout(15)
#define RS  PDout(10)
#define WR  PDout(9)
#define RD  PDout(8)
#define DB0 PEout(15)
#define DB1 PEout(14)
#define DB2 PEout(13)
#define DB3 PEout(12)
#define DB4 PEout(11)
#define DB5 PEout(10)
#define DB6 PEout(9)
#define DB7 PEout(8)
#define CS  PEout(7)
#define LCD_CS  CS    //片选使能   0为选中；1为不选中
#define LCD_RD  RD   //读操作     0：读操作使能；1：不进行读操作
#define LCD_WR  WR   //写操作     0：写操作使能；1：不进行写操作
#define LCD_RS  RS   //命令或数据，0：命令；1：数据；

/*****************函数声名***********************************/
void LCD_Init(void);
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);
void LCD_Clear(void);
void LCD_WR_DATA8(char VH,char VL);
void SLEEPEXIT(void);
void RAM_address(void);
#endif
