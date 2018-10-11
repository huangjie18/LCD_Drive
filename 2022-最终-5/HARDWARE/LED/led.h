#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(3)// PB3
#define RCK  PBout(13)
#define SCK  PBout(14)
#define SEG  PBout(15)

#define ES1_A  PDin(8)
#define ES1_B  PDin(9)
#define ES2_A  PDin(10)
#define ES2_B  PDin(11)
#define ES3_A  PDin(12)
#define ES3_B  PDin(13)
#define ES4_A  PDin(14)
#define ES4_B  PDin(15)

void LED_Init(void);//初始化
void LED_Def(void);		//灯灭
void LED_bright(void);  //灯亮
void LED_bright_one(u8 *data_led);  //一个595写数据函数	

#endif


