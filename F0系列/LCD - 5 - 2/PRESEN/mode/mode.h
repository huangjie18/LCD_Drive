#ifndef __MODE_H
#define __MODE_H
#include "sys.h"
#include "lcd.h"

#define  beijing  blue
#define  hengping		 //���������ʾ
//#define  shuping		 //����������ʾ  �����ͺ���ֻ�ܶ���һ��
#define  zimo    16		 //������ģ��С
#define  list1_start    0	  //������ʾ��������
#define  list1_end      15
#define  list2_start    16
#define  list2_end      31
#define  list3_start    32
#define  list3_end      47
#define  list4_start    48
#define  list4_end      63
#define  list5_start    64
#define  list5_end      79
#define  list6_start    80
#define  list6_end      95 
#define chu  1




extern uint8 xend,yend;

void  hunxiang(uint16 bk);    //��ʾ���캯��
void  huisheng(uint16 bk);    //��ʾ��������
void  biandiao(uint16 bk);    //��ʾ�������
void  dipingtisheng(uint16 bk);  //��ʾ��Ƶ��������
void  gaopingtisheng(uint16 bk);  //��ʾ��Ƶ��������
void  ganshikaiguang(uint16 bk);
void xianshi(uint8 *c,const uint8 (*p)[16],uint8 num,uint16 bk);
void diaoyong(uint8 list_start,uint8 list_end,uint8 num,uint16 bk,const uint8 (*p)[16]);

#endif
