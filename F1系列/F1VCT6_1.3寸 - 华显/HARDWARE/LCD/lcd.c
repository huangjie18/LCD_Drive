#include "lcd.h"
#include "delay.h"


//lcd接口初始化
void LCD_GPIO_Init_1(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOD和GPIOE的时钟线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //复用时钟线开
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG,启用SW-DP,因为要使用PB3
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_11;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3
								  |GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //GND
	GPIO_ResetBits(GPIOD,GPIO_Pin_11);  //GND
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);  //GND
	GPIO_SetBits(GPIOB,GPIO_Pin_4);    //VCC
	GPIO_SetBits(GPIOB,GPIO_Pin_3);    //VCC
	LEDK_1 = 0;
	LEDA_1 = 1;
}


/****************写命令函数*******************/
static void LcdWriCommand_1(unsigned char command)
{
	u8 i;
	DC_1 = 0; //4线SPI

	for(i=0;i<8;i++)
	{
		if(command&0x80)
		{
			SDA_1 = 1;
		}
		else
		{
			SDA_1 = 0;
		}
		SCL_1 = 0;
		SCL_1 = 1;

		command<<=1;
	}

}

/****************写数据函数*******************/
static void LcdWriData_1(unsigned char Data)
{
	u8 i;
	DC_1 = 1; //4线SPI

	
	
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
		{
			SDA_1 = 1;
		}
		else
		{
			SDA_1 = 0;
		}
		SCL_1 = 0;
		SCL_1 = 1;
		
		Data<<=1;
	}

}

//LCD初始化函数
void LCD_Init_1(void)
{
	LCD_GPIO_Init_1();  //引脚初始化
	RES_1 = 1;
	delay_ms(100);
	RES_1 = 0; //LCD复位
	delay_ms(100);
	RES_1 = 1;
	delay_ms(120);
	
	LcdWriCommand_1(0x11);
	delay_ms(200);
	
	LcdWriCommand_1(0x36);  //扫描方式
	LcdWriData_1(0x00);
	LcdWriCommand_1(0x3a); 
	LcdWriData_1(0x05); 
	
	LcdWriCommand_1(0xb2); 
	LcdWriData_1(0x0c); 
	LcdWriData_1(0x0c); 
	LcdWriData_1(0x00); 
	LcdWriData_1(0x33); 
	LcdWriData_1(0x33); 
	
	LcdWriCommand_1(0xb7); 
	LcdWriData_1(0x35); 
	
	//---------------------------------ST7789S Power setting--------------------------------------// 
	
	LcdWriCommand_1(0xbb); 
	LcdWriData_1(0x2C); 

	
	LcdWriCommand_1(0xc0); 
	LcdWriData_1(0x2c); 
	
	LcdWriCommand_1(0xc2); 
	LcdWriData_1(0x01); 
	
	LcdWriCommand_1(0xc3); 
	LcdWriData_1(0x0b); 

	
	LcdWriCommand_1(0xc4); 
	LcdWriData_1(0x20); 
	
	LcdWriCommand_1(0xc6); 
	LcdWriData_1(0x0f); 
	
	LcdWriCommand_1(0xd0); 
	LcdWriData_1(0xa4); 
	LcdWriData_1(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	LcdWriCommand_1(0xe0); 
	LcdWriData_1(0xd0); 
	LcdWriData_1(0x06); 
	LcdWriData_1(0x01); 
	LcdWriData_1(0x0e); 
	LcdWriData_1(0x0e); 
	LcdWriData_1(0x08); 
	LcdWriData_1(0x32); 
	LcdWriData_1(0x44); 
	LcdWriData_1(0x40); 
	LcdWriData_1(0x08); 
	LcdWriData_1(0x10); 
	LcdWriData_1(0x0f); 
	LcdWriData_1(0x15); 
	LcdWriData_1(0x19); 
	
	LcdWriCommand_1(0xe1); 
	LcdWriData_1(0xd0); 
	LcdWriData_1(0x06); 
	LcdWriData_1(0x01); 
	LcdWriData_1(0x0f); 
	LcdWriData_1(0x0e); 
	LcdWriData_1(0x09); 
	LcdWriData_1(0x2f); 
	LcdWriData_1(0x54); 
	LcdWriData_1(0x44); 
	LcdWriData_1(0x0f); 
	LcdWriData_1(0x1d); 
	LcdWriData_1(0x1a); 
	LcdWriData_1(0x16); 
	LcdWriData_1(0x19); 
	
	LcdWriCommand_1(0x21);	//display inversion on
	LcdWriCommand_1(0x29);//display on

	delay_ms(120);
	
}

//开显示区函数
void address_1(void)
{             
	LcdWriCommand_1(0x2A);
	LcdWriData_1(0x00);
	LcdWriData_1(0x00);
	LcdWriData_1(0x00);
	LcdWriData_1(0xef);
	
	LcdWriCommand_1(0x2B);
	LcdWriData_1(0x00);
	LcdWriData_1(0x00);//3B
	LcdWriData_1(0x01);
	LcdWriData_1(0x3f);
	


	LcdWriCommand_1(0x2C);
}

static void WriteDAT_1(unsigned char DH,unsigned char DL)		
{
	LcdWriData_1(DH);
	LcdWriData_1(DL);	
}
//测试程序
void display_test_1(void)
{
	u8 i,j;
	address_1();
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT_1(red>>8,red&0xff);
			}
			else if(j<=160)
			{
				WriteDAT_1(green>>8,green&0xff);
			}
			else
			{
				WriteDAT_1(blue>>8,blue&0xff);
			}
		}
	}
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT_1(white>>8,white&0xff);
			}
			else if(j<=160)
			{
				WriteDAT_1(black>>8,black&0xff);
			}
			else
			{
				WriteDAT_1(gray>>8,gray&0xff);
			}
		}
	}
}