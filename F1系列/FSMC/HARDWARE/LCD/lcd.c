#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 战舰STM32F103开发板V3
//2.4寸/2.8寸/3.5寸/4.3寸/7寸 TFT液晶驱动	  
//支持驱动IC型号包括:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963等		    
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/7/4
//版本：V2.9
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2修改说明
//支持了SPFD5408的驱动,另外把液晶ID直接打印成HEX格式.方便查看LCD驱动IC.
//V1.3
//加入了快速IO的支持
//修改了背光控制的极性（适用于V1.8及以后的开发板版本）
//对于1.8版本之前(不包括1.8)的液晶模块,请修改LCD_Init函数的LCD_LED=1;为LCD_LED=1;
//V1.4
//修改了LCD_ShowChar函数，使用画点功能画字符。
//加入了横竖屏显示的支持
//V1.5 20110730
//1,修改了B505液晶读颜色有误的bug.
//2,修改了快速IO及横竖屏的设置方式.
//V1.6 20111116
//1,加入对LGDP4535液晶的驱动支持
//V1.7 20120713
//1,增加LCD_RD_DATA函数
//2,增加对ILI9341的支持
//3,增加ILI9325的独立驱动代码
//4,增加LCD_Scan_Dir函数(慎重使用)	  
//6,另外修改了部分原来的函数,以适应9341的操作
//V1.8 20120905
//1,加入LCD重要参数设置结构体lcddev
//2,加入LCD_Display_Dir函数,支持在线横竖屏切换
//V1.9 20120911
//1,新增RM68042驱动（ID:6804），但是6804不支持横屏显示！！原因：改变扫描方式，
//导致6804坐标设置失效，试过很多方法都不行，暂时无解。
//V2.0 20120924
//在不硬件复位的情况下,ILI9341的ID读取会被误读成9300,修改LCD_Init,将无法识别
//的情况（读到ID为9300/非法ID）,强制指定驱动IC为ILI9341，执行9341的初始化。
//V2.1 20120930
//修正ILI9325读颜色的bug。
//V2.2 20121007
//修正LCD_Scan_Dir的bug。
//V2.3 20130120
//新增6804支持横屏显示
//V2.4 20131120
//1,新增NT35310（ID:5310）驱动器的支持
//2,新增LCD_Set_Window函数,用于设置窗口,对快速填充,比较有用,但是该函数在横屏时,不支持6804.
//V2.5 20140211
//1,新增NT35510（ID:5510）驱动器的支持
//V2.6 20140504
//1,新增ASCII 24*24字体的支持(更多字体用户可以自行添加)  
//2,修改部分函数参数,以支持MDK -O2优化
//3,针对9341/35310/35510,写时间设置为最快,尽可能的提高速度
//4,去掉了SSD1289的支持,因为1289实在是太慢了,读周期要1us...简直奇葩.不适合F4使用
//5,修正68042及C505等IC的读颜色函数的bug.
//V2.7 20140710
//1,修正LCD_Color_Fill函数的一个bug. 
//2,修正LCD_Scan_Dir函数的一个bug.
//V2.8 20140721
//1,解决MDK使用-O2优化时LCD_ReadPoint函数读点失效的问题.
//2,修正LCD_Scan_Dir横屏时设置的扫描方式显示不全的bug.
//V2.9 20141130
//1,新增对SSD1963 LCD的支持.
//2,新增LCD_SSD_BackLightSet函数
//3,取消ILI93XX的Rxx寄存器定义
//////////////////////////////////////////////////////////////////////////////////	 

#define LCD_WriteReg  LCD_WR_REG_DATA

//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
  
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

#if  FSMC_Enable
//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(u16 regval)
{   
	LCD->LCD_REG=regval;//写入要写的寄存器序号	 
}
//写LCD数据
//data:要写入的值
void LCD_WR_DATA(u16 data)
{	 
	LCD->LCD_RAM=data;		 
}
//读LCD数据
//返回值:读到的值
u16 LCD_RD_DATA(void)
{
	vu16 ram;			//防止被优化
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   
//写寄存器
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	u8 i,j;
	u16 LCD_DATA;
	
	LCD->LCD_REG = LCD_Reg;		//写入要写的寄存器序号
	
	i = (LCD_RegValue>>13)&0x01;
	j = (LCD_RegValue>>15)&0x01;
	LCD_DATA = LCD_RegValue;
	LCD_DATA = LCD_DATA&0x5fff;
	LCD_DATA = LCD_DATA|(j<<13);
	LCD_DATA = LCD_DATA|(i<<15);
	
	LCD->LCD_RAM = LCD_DATA;//写入数据	
}	   
//读寄存器
//LCD_Reg:寄存器地址
//返回值:读到的数据
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//写入要读的寄存器序号		  
	return LCD_RD_DATA();		//返回读到的值
} 
//LCD写GRAM
//RGB_Code:颜色值
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//写十六位GRAM
}
#else
/***************************写数据总线******************************************/
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
/***************************写数据**********************************************/
void LCD_WR_DATA(int da)   
{
    LCD_RS=1;
	LCD_Writ_Bus(da>>8,da);
}
/***************************写命令**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg>>8,reg);
}
/****************************写命令和数据**********************************************/
void LCD_WR_REG_DATA(int reg,int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
#endif
	 




//当mdk -O1时间优化时需要设置
//延时i
void opt_delay(u8 i)
{
	while(i--);
}
//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
			 




void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD 
	| RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
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
	LCD_RST = 0;  //复位
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



//初始化lcd
//该初始化函数可以初始化各种ILI93XX液晶,但是其他函数是基于ILI9320的!!!
//在其他型号的驱动芯片上没有测试! 
void LCD_Init(void)
{ 					
 	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//使能FSMC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//使能PORTB,D,E,G以及AFIO复用功能时钟

	
 	//PORTD复用推挽输出  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE复用推挽输出  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12复用推挽输出 A0	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD复用推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure); 

//	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
//  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
//  readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
//  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//  readWriteTiming.FSMC_CLKDivision = 0x00;
//  readWriteTiming.FSMC_DataLatency = 0x00;
//  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
//    

//	writeTiming.FSMC_AddressSetupTime = 0x00;	 //地址建立时间（ADDSET）为1个HCLK  
//  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
//  writeTiming.FSMC_DataSetupTime = 0x03;		 ////数据保存时间为4个HCLK	
//  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
//  writeTiming.FSMC_CLKDivision = 0x00;
//  writeTiming.FSMC_DataLatency = 0x00;
//  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

//   readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
//  readWriteTiming.FSMC_AddressHoldTime = 15;	 //地址保持时间（ADDHLD）模式A未用到	
//  readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
//  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//  readWriteTiming.FSMC_CLKDivision = 0x00;
//  readWriteTiming.FSMC_DataLatency = 0x00;
//  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime =0x05;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x0;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 0x05;		 //数据保存时间为6ns*9个HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0;
  writeTiming.FSMC_DataLatency = 0;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
  
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // 读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &writeTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
		
 
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



















