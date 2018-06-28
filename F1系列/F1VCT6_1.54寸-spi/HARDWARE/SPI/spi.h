#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#define spi_mode 0  //0ʹ��Ӳ��SPI��1ʹ��ģ��SPI
#define spi_init 0  //��ʼ��ģʽ��0ʹ��Ӳ��spiģʽ

#define LCD_DC  PBout(2) //�������ݻ�������ָ��
#define LCD_RST PCout(6) //����oled�ĸ�λ
#define SCL PBout(13) 
#define SDA PBout(15)
 
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif