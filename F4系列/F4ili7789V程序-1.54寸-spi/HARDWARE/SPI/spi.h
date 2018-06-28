#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#define spi_mode 0  //0ʹ��Ӳ��SPI��1ʹ��ģ��SPI
#define spi_init 0  //0ʹ��Ӳ��SPI��1ʹ��ģ��SPI


//**************************
//SCL -- PA5
//SDA -- PA7
//DC  -- PB2
//RST -- PC6
//**************************
#define LCD_DC  PBout(2) //�������ݻ�������ָ��
#define LCD_RST PCout(6) //����oled�ĸ�λ
#define SDA     PAout(7) 
#define SCL     PAout(5) 

void SPI1_Init(void);			 //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
#endif
