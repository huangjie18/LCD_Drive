#include "lcd.h"
#include "delay.h"


//lcd接口初始化
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOD和GPIOE的时钟线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //复用时钟线开
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG,启用SW-DP,因为要使用PB3
	
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5|GPIO_Pin_3|GPIO_Pin_1;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_SetBits(GPIOD,GPIO_Pin_7);     //VCC
	GPIO_ResetBits(GPIOD,GPIO_Pin_5);  //GND
	
}


/****************写命令函数*******************/
static void LcdWriCommand(unsigned char command)
{
	u8 i;
	DC = 0; //4线SPI

	for(i=0;i<8;i++)
	{
		if(command&0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;
		SCL = 1;

		command<<=1;
	}

}

/****************写数据函数*******************/
static void LcdWriData(unsigned char Data)
{
	u8 i;
	DC = 1; //4线SPI
	
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;
		SCL = 1;
		
		Data<<=1;
	}

}

//LCD初始化函数
void LCD_Init(void)
{
	RES = 1;
	delay_ms(100);
	RES = 0; //LCD复位
	delay_ms(100);
	RES = 1;
	delay_ms(120);
	
	LcdWriCommand(0x11);
	delay_ms(200);
	
	LcdWriCommand(0x36);  //扫描方式
	LcdWriData(0x00);
	LcdWriCommand(0x3a); 
	LcdWriData(0x05); 
	
	LcdWriCommand(0xb2); 
	LcdWriData(0x0c); 
	LcdWriData(0x0c); 
	LcdWriData(0x00); 
	LcdWriData(0x33); 
	LcdWriData(0x33); 
	
	LcdWriCommand(0xb7); 
	LcdWriData(0x35); 
	
	//---------------------------------ST7789S Power setting--------------------------------------// 
	
	LcdWriCommand(0xbb); 
	LcdWriData(0x2C); 

	
	LcdWriCommand(0xc0); 
	LcdWriData(0x2c); 
	
	LcdWriCommand(0xc2); 
	LcdWriData(0x01); 
	
	LcdWriCommand(0xc3); 
	LcdWriData(0x0b); 

	
	LcdWriCommand(0xc4); 
	LcdWriData(0x20); 
	
	LcdWriCommand(0xc6); 
	LcdWriData(0x0f); 
	
	LcdWriCommand(0xd0); 
	LcdWriData(0xa4); 
	LcdWriData(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	LcdWriCommand(0xe0); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0e); 
	LcdWriData(0x0e); 
	LcdWriData(0x08); 
	LcdWriData(0x32); 
	LcdWriData(0x44); 
	LcdWriData(0x40); 
	LcdWriData(0x08); 
	LcdWriData(0x10); 
	LcdWriData(0x0f); 
	LcdWriData(0x15); 
	LcdWriData(0x19); 
	
	LcdWriCommand(0xe1); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0f); 
	LcdWriData(0x0e); 
	LcdWriData(0x09); 
	LcdWriData(0x2f); 
	LcdWriData(0x54); 
	LcdWriData(0x44); 
	LcdWriData(0x0f); 
	LcdWriData(0x1d); 
	LcdWriData(0x1a); 
	LcdWriData(0x16); 
	LcdWriData(0x19); 
	
	LcdWriCommand(0x21);	//display inversion on
	LcdWriCommand(0x29);//display on

	delay_ms(120);
	
}

//开显示区函数
static void address(void)
{             
	LcdWriCommand(0x2A);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0xef);
	
	LcdWriCommand(0x2B);
	LcdWriData(0x00);
	LcdWriData(0x00);//3B
	LcdWriData(0x01);
	LcdWriData(0x3f);

	LcdWriCommand(0x2C);
}

static void WriteDAT(unsigned char DH,unsigned char DL)		
{
	LcdWriData(DH);
	LcdWriData(DL);	
}
//测试程序
void display_test(void)
{
	u8 i,j;
	address();
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT(red>>8,red&0xff);
			}
			else if(j<=160)
			{
				WriteDAT(green>>8,green&0xff);
			}
			else
			{
				WriteDAT(blue>>8,blue&0xff);
			}
		}
	}
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT(white>>8,white&0xff);
			}
			else if(j<=160)
			{
				WriteDAT(black>>8,black&0xff);
			}
			else
			{
				WriteDAT(gray>>8,gray&0xff);
			}
		}
	}
}

/****************************************************************************************/
//0.96寸引脚初始化
void LCD_GPIOInit_0(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD
							|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);//使能GPIOD和GPIOE的时钟线

	
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;				 // 端口配置
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				 // 端口配置
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_4);     //VCC
	BLK_0 = 1;  //背光开
}

/****************写命令函数*******************/
static void LCD_WR_command(unsigned char command)
{
	u8 i;
	CS_0 = 0;
	DC_0 = 0; //4线SPI
	
	for(i=0;i<8;i++)
	{
		if(command&0x80)
		{
			SDA_0 = 1;
		}
		else
		{
			SDA_0 = 0;
		}
		SCL_0 = 0;
		SCL_0 = 1;

		command<<=1;
	}
	CS_0 = 1;
}

/****************写数据函数*******************/
static void LCD_WR_para(unsigned char Data)
{
	u8 i;
	CS_0 = 0;
	DC_0 = 1; //4线SPI

	
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
		{
			SDA_0 = 1;
		}
		else
		{
			SDA_0 = 0;
		}
		SCL_0 = 0;
		SCL_0 = 1;
		
		Data<<=1;
	}
	CS_0 = 1;
}

//初始化程序
void LCD_Init_0(void)
{
	RES_0 = 1;
	delay_ms(100);
	RES_0 = 0; //LCD复位
	delay_ms(100);
	RES_0 = 1;
	delay_ms(120);
	
	
	LCD_WR_command(0x11); //Sleep out //0x11
	delay_ms (120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	LCD_WR_command(0xB1);
	LCD_WR_para(0x05);//05
	LCD_WR_para(0x3a);//3a
	LCD_WR_para(0x3a);//3a
	LCD_WR_command(0xB2);
	LCD_WR_para(0x05);//05
	LCD_WR_para(0x3a);//3a
	LCD_WR_para(0x3a);//3a
	LCD_WR_command(0xB3);
	LCD_WR_para(0x05);//05
	LCD_WR_para(0x3a);//3a
	LCD_WR_para(0x3a);//3a
	LCD_WR_para(0x05);//05
	LCD_WR_para(0x3a);//3a
	LCD_WR_para(0x3a);//3a
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	LCD_WR_command(0xB4); //Dot inversion
	LCD_WR_para(0x03);
	//------------------------------------ST7735S Power Sequence-----------------------------------------//
	LCD_WR_command(0xC0);
	LCD_WR_para(0x62);//62
	LCD_WR_para(0x02);//02
	LCD_WR_para(0x04);//04
	LCD_WR_command(0xC1);
	LCD_WR_para(0xC0);//c0
	LCD_WR_command(0xC2);
	LCD_WR_para(0x0D);//0d
	LCD_WR_para(0x00);//00
	LCD_WR_command(0xC3);
	LCD_WR_para(0x8D);//8d
	LCD_WR_para(0x6A);//6a
	LCD_WR_command(0xC4);
	LCD_WR_para(0x8D);//8d
	LCD_WR_para(0xEE);//
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	LCD_WR_command(0xC5); //VCOM
	LCD_WR_para(0x12);

	LCD_WR_para(0x03);
	LCD_WR_para(0x36);
	LCD_WR_para(0xc8);
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_command(0xE0);
	LCD_WR_para(0x03);
	LCD_WR_para(0x1B);
	LCD_WR_para(0x12);
	LCD_WR_para(0x11);
	LCD_WR_para(0x3F);
	LCD_WR_para(0x3A);
	LCD_WR_para(0x32);
	LCD_WR_para(0x34);
	LCD_WR_para(0x2F);
	LCD_WR_para(0x2B);
	LCD_WR_para(0x30);
	LCD_WR_para(0x3A);
	LCD_WR_para(0x00);
	LCD_WR_para(0x01);
	LCD_WR_para(0x02);
	LCD_WR_para(0x05);
	LCD_WR_command(0xE1);
	LCD_WR_para(0x03);
	LCD_WR_para(0x1B);
	LCD_WR_para(0x12);
	LCD_WR_para(0x11);
	LCD_WR_para(0x32);
	LCD_WR_para(0x2F);
	LCD_WR_para(0x2A);
	LCD_WR_para(0x2F);
	LCD_WR_para(0x2E);
	LCD_WR_para(0x2C);
	LCD_WR_para(0x35);
	LCD_WR_para(0x3F);
	LCD_WR_para(0x00);
	LCD_WR_para(0x00);
	LCD_WR_para(0x01);
	LCD_WR_para(0x05);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_command(0xFC); //Enable Gate power save mode
	LCD_WR_para(0x8C);
	LCD_WR_command(0x3A); //65k mode
	LCD_WR_para(0x05);
	LCD_WR_command(0x36); //65k mode//36
	LCD_WR_para(0x60);//
	LCD_WR_command(0x29); //Display on   
	delay_ms(20);
}
static void LCD_WR_data(u8 data1,u8 data2)
{
	LCD_WR_para(data1);
	LCD_WR_para(data2);
}
/**********************显示三色*******************/
void display_rgb(void)
{
  u16 i,j,k=0;
  LCD_WR_command(0x2a);              //Horizontal Address Start Position
  LCD_WR_para(0x00);
  LCD_WR_para(0x01);
  LCD_WR_para(0x00);
  LCD_WR_para(0xA0);
  LCD_WR_command(0x2b);              //Vertival Address end Position
  LCD_WR_para(0x00);
  LCD_WR_para(0x1A);
  LCD_WR_para(0x00);
  LCD_WR_para(0x69);
  LCD_WR_command(0x2c);
  
  
	
	for(i=0;i<21;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(0xFF,0x00);}	//R
	}
	
	


	for(i=21;i<50;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(0x00,0XF0);}	//G
	}

	for(i=50;i<80;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(0x07,0xFf);}	//B
	}
 }