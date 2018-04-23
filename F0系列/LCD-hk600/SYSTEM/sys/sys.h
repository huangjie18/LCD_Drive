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
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
////IO?úμ??·ó3é?
//#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
//#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
//#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
//#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
//#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
//#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
//#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

//#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
//#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
//#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
//#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
//#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
//#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
// 
//#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //ê?3? 
//#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ê?è? 

//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //ê?3? 
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //ê?è? 

//#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //ê?3? 
//#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //ê?è? 

//#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //ê?3? 
//#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //ê?è? 

//#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //ê?3? 
//#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //ê?è?

//#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //ê?3? 
//#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //ê?è?

//#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //ê?3? 
//#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //ê?è? 

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
//F0系列没有位带操作
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
////IO口地址映射
//#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
//#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
//#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
//#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
//#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
//#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
//#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
//#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
//#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

//#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
//#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
//#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
//#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
//#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
//#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
//#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
//#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
// 
////IO口操作,只对单一的IO口!
////确保n的值小于16!
//#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
//#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

//#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
//#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

//#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
//#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

//#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
//#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

//#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
//#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

//#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
//#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
//#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

//#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
//#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入


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











