#include "led.h"
#include "stdlib.h"
#include "delay.h"
/*
文件说明：该LCD驱动适合正点原子F1和F4开发板使用
文件使用：适合8线并口传输，只需要修改LCD_Init初始驱动
		  接线按照lcd.h里的定义接
// */
//void LCD_Writ_Bus(char data_1, char data_2)  //并行数据写入函数
//{
//	//下面是由于芯片引脚和lcd的数据传输引脚相反，所以需要把传输数据颠倒顺序再传输
//	u16 i, j, addr2 = 0, addr3 = 0, temp2, temp3;
//	for (i = 0; i <= 7; i++)
//	{
//		addr2 = addr2 << 1;
//		addr2 = addr2 | (data_1 & 1);
//		data_1 = data_1 >> 1;
//	}
//	for (j = 0; j <= 7; j++)
//	{
//		addr3 = addr3 << 1;
//		addr3 = addr3 | (data_2 & 1);
//		data_2 = data_2 >> 1;
//	}
//	addr2 = addr2 << 8; //因为用的芯片引脚是高八位，所以左移8位
//	addr3 = addr3 << 8;

//	CS = 0;
//	WR = 1;
//	temp2 = (GPIOE->IDR & 0xff00);

//#if defined STM32F40_41xxx
//	GPIOE->BSRRH = temp2;  //对GPIOE全部输出为0
//	GPIOE->BSRRL = addr2;  //GPIOE输出数据
//	WR = 0;  //写操作使能
//	WR = 1;  //写操作失能
//	CS = 1;

//	CS = 0;
//	WR = 1;
//	temp3 = (GPIOE->IDR & 0xff00);
//	GPIOE->BSRRH = temp3;
//	GPIOE->BSRRL = addr3;
//	WR = 0;
//	WR = 1;
//	CS = 1;   //关闭片选使能

//#elif defined STM32F10X_HD
//	GPIOE->BSRR = temp2 << 16;
//	GPIOE->BSRR = addr2;
//	WR = 0;  //写操作使能
//	WR = 1;  //写操作失能
//	CS = 1;

//	CS = 0;
//	WR = 1;
//	temp3 = (GPIOE->IDR & 0xff00);
//	GPIOE->BSRR = temp3 << 16;
//	GPIOE->BSRR = addr3;
//	WR = 0;
//	WR = 1;
//	CS = 1;   //关闭片选使能
//#endif
//}

void LCD_Writ_Bus(char data_1,char data_2)
{
	u16 i,temp1,temp2;
	CS = 0;
	WR = 1;
	for(i=0;i<8;i++)
	{
		temp1 = (data_2>>i)&1;
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
	
	WR = 0;

	WR = 1;
	
	for(i=0;i<8;i++)
	{
		temp1 = (data_2>>i)&1;
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
	WR = 0;

	WR = 1;
}
void LCD_WR_DATA8(char VH, char VL) //发送数据-8位参数
{
	LCD_RS = 1;
	LCD_Writ_Bus(VH, VL);
}
/***************************写数据**********************************************/
void LCD_WR_DATA(int da)
{
	LCD_RS = 1;
	LCD_Writ_Bus(da >> 8, da);
}
/***************************写命令**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg >> 8, reg);
}
/****************************写命令和数据**********************************************/
void LCD_WR_REG_DATA(int reg, int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}


/****************初始化命令*******************/
void LCD_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;//重新定义一个结构体

	//开启时钟线，stm32有，单片机没有
#ifdef STM32F40_41xxx   //判断芯片类型
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	//对结构体的变量进行初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
	                              GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#elif defined  STM32F10X_HD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	//对结构体的变量进行初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
	                              GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#endif
	RST = 0;
	delay_ms(20);
	RST = 1;
	delay_ms(10);


	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delay_ms(5);
	LCD_CS = 0; //打开片选使能

	//下面是初始代码，不需要知道全部细节，一般由厂家提供
	//需要修改时要参考数据手册,初始化程序不一样显示效果也不一样

	LCD_WR_REG_DATA(0x0000, 0x0001);
	LCD_WR_REG_DATA(0x002B, 0x0002);
	delay_ms(20);
	LCD_WR_REG_DATA(0x0007, 0x0000); 
	LCD_WR_REG_DATA(0x0012, 0x0000);  
	delay_ms(20);
	
	LCD_WR_REG_DATA(0x0060, 0x3500);  
	delay_ms(20);

	LCD_WR_REG_DATA(0x0008, 0x0405);
	LCD_WR_REG_DATA(0x0091, 0x0600);  
	LCD_WR_REG_DATA(0x0092, 0x0700); 
	LCD_WR_REG_DATA(0x0098, 0x0747);  
	LCD_WR_REG_DATA(0x0001, 0x0000);  

	LCD_WR_REG_DATA(0x0030, 0x0002);  
	LCD_WR_REG_DATA(0x0031, 0x0606);  
	LCD_WR_REG_DATA(0x0032, 0x0607);  
	LCD_WR_REG_DATA(0x0035, 0x0001);
	LCD_WR_REG_DATA(0x0036, 0x0911);
	LCD_WR_REG_DATA(0x0037, 0x0605);
	LCD_WR_REG_DATA(0x0038, 0x0504);
	LCD_WR_REG_DATA(0x0039, 0x0707);
	LCD_WR_REG_DATA(0x003c, 0x0101);
	LCD_WR_REG_DATA(0x003d, 0x1a16);
 


	LCD_WR_REG_DATA(0x0010, 0x5aC0);  
	LCD_WR_REG_DATA(0x0011, 0x0247);  
	delay_ms(20); // Delay 50ms 
	LCD_WR_REG_DATA(0x0012, 0x111a);  
	LCD_WR_REG_DATA(0x0013, 0x1303);
	LCD_WR_REG_DATA(0x0029, 0x0016);
	delay_ms(20); // Delay 50ms 
	
	
	LCD_WR_REG_DATA(0x0001, 0x0000);  
	LCD_WR_REG_DATA(0x0002, 0x0700);
	LCD_WR_REG_DATA(0x0003, 0x1030);
	LCD_WR_REG_DATA(0x0061, 0x0001);
	delay_ms(20); // Delay 50ms
	
	LCD_WR_REG_DATA(0x0090, 0x0018);  
	LCD_WR_REG_DATA(0x0092, 0x0000); 
	LCD_WR_REG_DATA(0x0080, 0x0000);
	LCD_WR_REG_DATA(0x0081, 0x0000);
	LCD_WR_REG_DATA(0x0082, 0x018F);  
	LCD_WR_REG_DATA(0x0083, 0x0000);  

	LCD_WR_REG_DATA(0x0084, 0x0000);	  
	LCD_WR_REG_DATA(0x0085, 0x018F);	 
	LCD_WR_REG_DATA(0x0050, 0x0000);		 
	LCD_WR_REG_DATA(0x0051, 0x00EF);	 
	LCD_WR_REG_DATA(0x0052, 0x0000);	 
	LCD_WR_REG_DATA(0x0053, 0x018F);	 
	LCD_WR_REG_DATA(0x0010, 0x5DC0);	 
	LCD_WR_REG_DATA(0x0007, 0x0001);
	delay_ms(50);
	LCD_WR_REG_DATA(0x0007, 0x0021);	
	delay_ms(50);
	LCD_WR_REG_DATA(0x0007, 0x0023);
	delay_ms(50);
	LCD_WR_REG_DATA(0x0007, 0x0033);
	delay_ms(50);
	LCD_WR_REG_DATA(0x0007, 0x0133);
	delay_ms(50);

	LCD_WR_REG_DATA(0x0020, 0x0000);
	LCD_WR_REG_DATA(0x0021, 0x0000);
	LCD_WR_REG(0x0022);
}

/*************************三色函数**********************************************/
//9225是特殊的，需要用这个
//void LCD_Clear()
//{
//	u8 i,j;
//	LCD_WR_REG_DATA(0x36,0x00af);     //horizontal address  水平地址高八位
//	LCD_WR_REG_DATA(0x37,0x0000);	  //horizontal address  水平地址低八位
//	LCD_WR_REG_DATA(0x38,0x00db);	  //vertical address    垂直地址高八位
//	LCD_WR_REG_DATA(0x39,0x0000);     //vertical address    垂直地址高八位
//
//	LCD_WR_REG_DATA(0x20,0x0000);    //GRAM address set   设置地址计数器的初始值
//	LCD_WR_REG_DATA(0x21,0x0000);
//
//	LCD_WR_REG(0x22);
//
//	RS = 1;  //写数据
//	CS = 0;
//	for (i = 0; i < 220; i++)
//	{
//		if(i<73)
//		 {
//			for(j=0;j<176;j++)
//			 {
//				LCD_WR_DATA(red);
//			 }
//		 }
//		 else if(i<146)
//		 {
//			 for(j=0;j<176;j++)
//			 {
//				 LCD_WR_DATA(blue);
//			 }
//		 }
//		 else
//		 {
//			 for(j=0;j<176;j++)
//			 {
//				 LCD_WR_DATA(green);
//			 }
//		 }
//
//	}
//
//}
void LCD_Clear()
{
	u16 i, j;

	RS = 1;  //写数据
	CS = 0;
	for (i = 0; i < 133; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(red);
		}
	}
	for (i = 0; i < 133; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(green);
		}
	}
	for (i = 0; i < 134; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_WR_DATA(blue);
		}
	}

}

void LCD_SET_WIN(void)
{	
	LCD_WR_REG_DATA(0x0050,0x0000);//水平起始位置
	LCD_WR_REG_DATA(0x0051,0x00EF);//水平终止位置
	LCD_WR_REG_DATA(0x0052,0x0000);//垂直起始位置
	LCD_WR_REG_DATA(0x0053,0x018F);//垂直终止位置
	LCD_WR_REG(0x0022);//LCD_WriteCMD(GRAMWR);
}	