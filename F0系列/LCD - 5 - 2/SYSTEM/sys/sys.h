#ifndef __SYS_H
#define __SYS_H	 
#include "stm32f0xx.h" 
#include "delay.h"
//#include "lw_oopc.h"   //类实现
//#include "object.h"    //类实现
#define		uint8		unsigned char
#define		uint16		unsigned int
#define		uint32 		unsigned long
#define     u8          uint8
#define     u16         uint16
#define     u32         uint32
//自己实现的位带操作
typedef struct _16_Bits_struct
{
	u16 bit0 : 1;
	u16 bit1 : 1;
	u16 bit2 : 1;
	u16 bit3 : 1;
	u16 bit4 : 1;
	u16 bit5 : 1;
	u16 bit6 : 1;
	u16 bit7 : 1;
	u16 bit8 : 1;
	u16 bit9 : 1;
	u16 bit10 : 1;
	u16 bit11 : 1;
	u16 bit12 : 1;
	u16 bit13 : 1;
	u16 bit14 : 1;
	u16 bit15 : 1;
}Bits_16_TypeDef;

#define PORT_OUT_GPIOA  ((Bits_16_TypeDef *)(&(GPIOA->ODR)))
#define PORT_OUT_GPIOB  ((Bits_16_TypeDef *)(&(GPIOB->ODR)))
#define PORT_OUT_GPIOF  ((Bits_16_TypeDef *)(&(GPIOF->ODR)))

//PA
#define PAout_0  (PORT_OUT_GPIOA->bit0)
#define PAout_1  (PORT_OUT_GPIOA->bit1)
#define PAout_2  (PORT_OUT_GPIOA->bit2)
#define PAout_3  (PORT_OUT_GPIOA->bit3)
#define PAout_4  (PORT_OUT_GPIOA->bit4)
#define PAout_5  (PORT_OUT_GPIOA->bit5)
#define PAout_6  (PORT_OUT_GPIOA->bit6)
#define PAout_7  (PORT_OUT_GPIOA->bit7)
#define PAout_8  (PORT_OUT_GPIOA->bit8)
#define PAout_9  (PORT_OUT_GPIOA->bit9)
#define PAout_10  (PORT_OUT_GPIOA->bit10)
#define PAout_11  (PORT_OUT_GPIOA->bit11)
#define PAout_12  (PORT_OUT_GPIOA->bit12)
#define PAout_13  (PORT_OUT_GPIOA->bit13)
#define PAout_14  (PORT_OUT_GPIOA->bit14)
#define PAout_15  (PORT_OUT_GPIOA->bit15)

//PB
#define PBout_0  (PORT_OUT_GPIOB->bit0)
#define PBout_1  (PORT_OUT_GPIOB->bit1)

//PF
#define PFout_0  (PORT_OUT_GPIOF->bit0)
#define PFout_1  (PORT_OUT_GPIOF->bit1)
#endif











