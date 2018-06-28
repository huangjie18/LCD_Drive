#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#define spi_mode 0  //0使用硬件SPI，1使用模拟SPI
#define spi_init 0  //0使用硬件SPI，1使用模拟SPI


//**************************
//SCL -- PA5
//SDA -- PA7
//DC  -- PB2
//RST -- PC6
//**************************
#define LCD_DC  PBout(2) //控制数据还是命令指令
#define LCD_RST PCout(6) //控制oled的复位
#define SDA     PAout(7) 
#define SCL     PAout(5) 

void SPI1_Init(void);			 //初始化SPI1口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI1速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1总线读写一个字节
#endif
