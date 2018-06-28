#ifndef __LCD_H
#define __LCD_H
#include "sys.h"
#include "stdlib.h"

//#define LCD_ID  9326  //����IC9326,4551,5420
#define red  0x001f
#define black 0x0000
#define white 0xffff
#define blue  0x07e0
#define green 0xf800

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
#define LCD_CS  CS    //Ƭѡʹ��   0Ϊѡ�У�1Ϊ��ѡ��
#define LCD_RD  RD   //������     0��������ʹ�ܣ�1�������ж�����
#define LCD_WR  WR   //д����     0��д����ʹ�ܣ�1��������д����
#define LCD_RS  RS   //��������ݣ�0�����1�����ݣ�

/*****************��������***********************************/
void LCD_Init(u16 LCD_ID);
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);
void LCD_Clear(u16 LCD_ID);
void LCD_WR_DATA8(char VH,char VL);
void SLEEPEXIT(void);
void SLEEPON(void);
void LCD_Read(void); //��
#endif
