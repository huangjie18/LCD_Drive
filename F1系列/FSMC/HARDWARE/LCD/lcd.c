#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ս��STM32F103������V3
//2.4��/2.8��/3.5��/4.3��/7�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963��		    
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/7/4
//�汾��V2.9
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2�޸�˵��
//֧����SPFD5408������,�����Һ��IDֱ�Ӵ�ӡ��HEX��ʽ.����鿴LCD����IC.
//V1.3
//�����˿���IO��֧��
//�޸��˱�����Ƶļ��ԣ�������V1.8���Ժ�Ŀ�����汾��
//����1.8�汾֮ǰ(������1.8)��Һ��ģ��,���޸�LCD_Init������LCD_LED=1;ΪLCD_LED=1;
//V1.4
//�޸���LCD_ShowChar������ʹ�û��㹦�ܻ��ַ���
//�����˺�������ʾ��֧��
//V1.5 20110730
//1,�޸���B505Һ������ɫ�����bug.
//2,�޸��˿���IO�������������÷�ʽ.
//V1.6 20111116
//1,�����LGDP4535Һ��������֧��
//V1.7 20120713
//1,����LCD_RD_DATA����
//2,���Ӷ�ILI9341��֧��
//3,����ILI9325�Ķ�����������
//4,����LCD_Scan_Dir����(����ʹ��)	  
//6,�����޸��˲���ԭ���ĺ���,����Ӧ9341�Ĳ���
//V1.8 20120905
//1,����LCD��Ҫ�������ýṹ��lcddev
//2,����LCD_Display_Dir����,֧�����ߺ������л�
//V1.9 20120911
//1,����RM68042������ID:6804��������6804��֧�ֺ�����ʾ����ԭ�򣺸ı�ɨ�跽ʽ��
//����6804��������ʧЧ���Թ��ܶ෽�������У���ʱ�޽⡣
//V2.0 20120924
//�ڲ�Ӳ����λ�������,ILI9341��ID��ȡ�ᱻ�����9300,�޸�LCD_Init,���޷�ʶ��
//�����������IDΪ9300/�Ƿ�ID��,ǿ��ָ������ICΪILI9341��ִ��9341�ĳ�ʼ����
//V2.1 20120930
//����ILI9325����ɫ��bug��
//V2.2 20121007
//����LCD_Scan_Dir��bug��
//V2.3 20130120
//����6804֧�ֺ�����ʾ
//V2.4 20131120
//1,����NT35310��ID:5310����������֧��
//2,����LCD_Set_Window����,�������ô���,�Կ������,�Ƚ�����,���Ǹú����ں���ʱ,��֧��6804.
//V2.5 20140211
//1,����NT35510��ID:5510����������֧��
//V2.6 20140504
//1,����ASCII 24*24�����֧��(���������û������������)  
//2,�޸Ĳ��ֺ�������,��֧��MDK -O2�Ż�
//3,���9341/35310/35510,дʱ������Ϊ���,�����ܵ�����ٶ�
//4,ȥ����SSD1289��֧��,��Ϊ1289ʵ����̫����,������Ҫ1us...��ֱ����.���ʺ�F4ʹ��
//5,����68042��C505��IC�Ķ���ɫ������bug.
//V2.7 20140710
//1,����LCD_Color_Fill������һ��bug. 
//2,����LCD_Scan_Dir������һ��bug.
//V2.8 20140721
//1,���MDKʹ��-O2�Ż�ʱLCD_ReadPoint��������ʧЧ������.
//2,����LCD_Scan_Dir����ʱ���õ�ɨ�跽ʽ��ʾ��ȫ��bug.
//V2.9 20141130
//1,������SSD1963 LCD��֧��.
//2,����LCD_SSD_BackLightSet����
//3,ȡ��ILI93XX��Rxx�Ĵ�������
//////////////////////////////////////////////////////////////////////////////////	 

#define LCD_WriteReg  LCD_WR_REG_DATA

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 
  
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

#if  FSMC_Enable
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{   
	LCD->LCD_REG=regval;//д��Ҫд�ļĴ������	 
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{	 
	LCD->LCD_RAM=data;		 
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{
	vu16 ram;			//��ֹ���Ż�
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	u8 i,j;
	u16 LCD_DATA;
	
	LCD->LCD_REG = LCD_Reg;		//д��Ҫд�ļĴ������
	
	i = (LCD_RegValue>>13)&0x01;
	j = (LCD_RegValue>>15)&0x01;
	LCD_DATA = LCD_RegValue;
	LCD_DATA = LCD_DATA&0x5fff;
	LCD_DATA = LCD_DATA|(j<<13);
	LCD_DATA = LCD_DATA|(i<<15);
	
	LCD->LCD_RAM = LCD_DATA;//д������	
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������		  
	return LCD_RD_DATA();		//���ض�����ֵ
} 
//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//дʮ��λGRAM
}
#else
/***************************д��������******************************************/
void LCD_Writ_Bus(char data_1,char data_2)
{
	u8 i;
	u8 temp1;
	LCD_CS = 0;
	LCD_WR = 1;
	
	for(i=0;i<8;i++)
	{
		temp1 = (data_1>>i)&0x01;
		switch(i)
		{
			case 0: DB8 = temp1;break;
			case 1: DB9 = temp1;break;
			case 2: DB10 = temp1;break;
			case 3: DB11 = temp1;break;
			case 4: DB12 = temp1;break;
			case 5: DB13 = temp1;break;
			case 6: DB14 = temp1;break;
			case 7: DB15 = temp1;break;
		}
	}
	for(i=0;i<8;i++)
	{
		temp1 = (data_2>>i)&0x01;
		switch(i)
		{
			case 0: DB0 = temp1;break;
			case 1: DB1 = temp1;break;
			case 2: DB2 = temp1;break;
			case 3: DB3 = temp1;break;
			case 4: DB4 = temp1;break;
			case 5: DB5 = temp1;break;
			case 6: DB6 = temp1;break;
			case 7: DB7 = temp1;break;
		}
	}
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;

}
/***************************д����**********************************************/
void LCD_WR_DATA(int da)   
{
    LCD_RS=1;
	LCD_Writ_Bus(da>>8,da);
}
/***************************д����**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg>>8,reg);
}
/****************************д���������**********************************************/
void LCD_WR_REG_DATA(int reg,int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
#endif
	 




//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
			 




void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD 
	| RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	#if FSMC_Enable
	#else
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//FSMC_NOE   RD
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//FSMC_NWE     WR
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	//FSMC_NE1     CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
    GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	//FSMC_A10     RS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
    GPIO_Init(GPIOG, &GPIO_InitStructure);
	#endif

}

void Lcd_Initialize_5420(void)
{
	u16 data;
	LCD_RST = 0;  //��λ
	delay_ms(200);
	LCD_RST = 1;
	delay_ms(20);
	
	
	#if FSMC_Enable

	#else
	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delay_ms(5);
	LCD_CS = 0;
	#endif
	
	
	
	LCD_WriteReg(0x0000, 0x0000); 
	LCD_WriteReg(0x0001, 0x0100); 
	LCD_WriteReg(0x0002, 0x0100); 
	LCD_WriteReg(0x0003, 0x1030); 
	LCD_WriteReg(0x0008, 0x0808); 
	LCD_WriteReg(0x0009, 0x0001); 
	LCD_WriteReg(0x000B, 0x0010); 
	LCD_WriteReg(0x000C, 0x0000); 
	LCD_WriteReg(0x000F, 0x0000); 
	LCD_WriteReg(0x0007, 0x0001); 
//--------------- Panel interface control 1~6 ---------------//

	LCD_WriteReg(0x0010, 0x0011);	//0x0012 0010
	LCD_WriteReg(0x0011, 0x0200);	//0x0202
	LCD_WriteReg(0x0012, 0x0300);	//
	LCD_WriteReg(0x0020, 0x021E);	//
	LCD_WriteReg(0x0021, 0x0202);	//
	LCD_WriteReg(0x0022, 0x0100);	//
	LCD_WriteReg(0x0090, 0x8000);	//


//--------------- Power control 1~6 ---------------//
	LCD_WriteReg(0x0100, 0x17B0); 
	LCD_WriteReg(0x0101, 0x0147);
	LCD_WriteReg(0x0102, 0x0138);

	LCD_WriteReg(0x0103, 0x3000);

	LCD_WriteReg(0x0107, 0x0000);
	LCD_WriteReg(0x0110, 0x0001);
	LCD_WriteReg(0x0280, 0x0000); // NVM write / read
	LCD_WriteReg(0x0281, 0x0000); // Vcom high voltage 1//0000
	LCD_WriteReg(0x0282, 0x0000); // Vcom high voltage 2


//--------------- Gamma 2.2 control ---------------//

	
	LCD_WriteReg(0x0300, 0x1011);	//0x0101	
	LCD_WriteReg(0x0301, 0x2524);	//0x0024
	LCD_WriteReg(0x0302, 0x2F20);	//0x1326
	LCD_WriteReg(0x0303, 0x202F);	//0x2313
	LCD_WriteReg(0x0304, 0x2325);	//0x2400
	LCD_WriteReg(0x0305, 0x1110);	//0x0100
	LCD_WriteReg(0x0306, 0x0e04);	//0x1704
	LCD_WriteReg(0x0307, 0x040e);	//0x0417
	LCD_WriteReg(0x0308, 0x0005);	//0x0007
	LCD_WriteReg(0x0309, 0x0003);	//0x0105
	LCD_WriteReg(0x030A, 0x0F04);	//0x0F05
	LCD_WriteReg(0x030B, 0x0F00);	//0x0F01
	LCD_WriteReg(0x030C, 0x000F);	//0x010F
	LCD_WriteReg(0x030D, 0x040F);	//0x050F
	LCD_WriteReg(0x030E, 0x0300);	//0x0501
	LCD_WriteReg(0x030F, 0x0500);	//0x0700
	LCD_WriteReg(0x0400, 0x3500);
	LCD_WriteReg(0x0401, 0x0001);	//0x0001
	LCD_WriteReg(0x0404, 0x0000);	//0x0000



//--------------- Partial display ---------------//
	LCD_WriteReg(0x0201, 0x0000);
	LCD_WriteReg(0x0200, 0x0000);
	LCD_WriteReg(0x0210, 0x0000); 
	LCD_WriteReg(0x0211, 0x00EF); 
	LCD_WriteReg(0x0212, 0x0000); 
	LCD_WriteReg(0x0213, 0x018F);
 
	LCD_WriteReg(0x0500, 0x0000);
	LCD_WriteReg(0x0501, 0x0000);
	LCD_WriteReg(0x0502, 0x0000);
	LCD_WriteReg(0x0503, 0x0000);
	LCD_WriteReg(0x0504, 0x0000);
	LCD_WriteReg(0x0505, 0x0000);
	LCD_WriteReg(0x0600, 0x0000); 
	LCD_WriteReg(0x0606, 0x0000); 
	LCD_WriteReg(0x06F0, 0x0000); 
//--------------- Orise mode ---------------//
	LCD_WriteReg(0x07F0, 0x5420);
	LCD_WriteReg(0x07de, 0x0000);
	LCD_WriteReg(0x07F2, 0x00df);
	LCD_WriteReg(0x07F3, 0x088e);	//0x288A
	LCD_WriteReg(0x07F4, 0x0022);
	LCD_WriteReg(0x07F5, 0x0001);	//
	LCD_WriteReg(0x07F0, 0x0000);
	LCD_WriteReg(0x0007, 0x0173); // Display on

	delay_ms(150);
}



//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void LCD_Init(void)
{ 					
 	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//ʹ��FSMCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTB,D,E,G�Լ�AFIO���ù���ʱ��

	
 	//PORTD�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12����������� A0	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure); 

//	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
//  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
//  readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
//  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//  readWriteTiming.FSMC_CLKDivision = 0x00;
//  readWriteTiming.FSMC_DataLatency = 0x00;
//  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
//    

//	writeTiming.FSMC_AddressSetupTime = 0x00;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
//  writeTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
//  writeTiming.FSMC_DataSetupTime = 0x03;		 ////���ݱ���ʱ��Ϊ4��HCLK	
//  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
//  writeTiming.FSMC_CLKDivision = 0x00;
//  writeTiming.FSMC_DataLatency = 0x00;
//  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

//   readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns	
//  readWriteTiming.FSMC_AddressHoldTime = 15;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
//  readWriteTiming.FSMC_DataSetupTime = 60;			//���ݱ���ʱ��Ϊ60��HCLK	=6*60=360ns
//  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//  readWriteTiming.FSMC_CLKDivision = 0x00;
//  readWriteTiming.FSMC_DataLatency = 0x00;
//  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	writeTiming.FSMC_AddressSetupTime =0x05;	      //��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x0;	 //��ַ����ʱ�䣨A		
  writeTiming.FSMC_DataSetupTime = 0x05;		 //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0;
  writeTiming.FSMC_DataLatency = 0;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
  
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // ��дʹ�ò�ͬ��ʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &writeTiming; //��дʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1 
		
 
	delay_ms(50); 					// delay 50 ms 
 
//	LCD_Clear(WHITE);
}  






void LCD_Clear_5420(void)
{
	u16 i, j;
	LCD_WriteReg(0x0210, 0x0000);	//X_Start);	//x start
	LCD_WriteReg(0x0211, 0x00ef);	//X_End);		//x end
	LCD_WriteReg(0x0212, 0x0000);	//Y_Start);	//y start
	LCD_WriteReg(0x0213, 0x018f);	//Y_End);		//y end
	LCD_WriteReg(0x0201, 0x0000);	//Y_Start);	//y addres
	LCD_WriteReg(0x0200, 0x0000);	//X_Start);	//x addres

	LCD_WR_REG(0x0202);
	

	for (i = 0; i < 133; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(RED);
		}
	}
	for (i = 0; i < 133; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(GREEN);
		}
	}
	for (i = 0; i < 134; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(BLUE);
		}
	}
}



















