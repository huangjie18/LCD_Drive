#include "lcd.h"
#include "delay.h"




//函数定义
static void ST7789_Init_16(void); //16位的1.3寸屏
static void LcdWriCommand(unsigned char command);
static void LcdWriData(unsigned char Data);
static void address(void);
static void WriteDAT(unsigned char DH,unsigned char DL);
static void delayms(int count);
//函数实现
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4
	| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	

}

/****************LCD初始化命令*******************/
void LCD_Init(void)
{
	LCD_GPIO_Init(); //LCD引脚初始化
	GPIO_SetBits(GPIOB,GPIO_Pin_1);  //背光开
//	GPIO_SetBits(GPIOA,GPIO_Pin_12);  //开机
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5); //SCL=1
	GPIO_SetBits(GPIOA,GPIO_Pin_7); //SDA=1
	GPIO_SetBits(GPIOB,GPIO_Pin_0); //CS=1
	GPIO_SetBits(GPIOA,GPIO_Pin_3); //DC=1
	ST7789_Init_16();   //7789驱动初始化代码
}
/****************写命令函数*******************/
static void LcdWriCommand(unsigned char command)
{
	int i;
	GPIO_ResetBits(GPIOA,GPIO_Pin_3); //DC=0
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); //CS=0
	GPIO_ResetBits(GPIOA,GPIO_Pin_5); //SCL=0
	GPIO_ResetBits(GPIOA,GPIO_Pin_7); //SDA=0
	GPIO_SetBits(GPIOA,GPIO_Pin_5); //SCL=1
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5); //SCL=0
		if(command&0x80)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_7); //SDA=1
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_7); //SDA=0
		}
		
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //SCL=1

		command<<=1;
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_0); //CS=1
	
}
/****************写数据函数*******************/
static void LcdWriData(unsigned char Data)
{
	int i;
	GPIO_SetBits(GPIOA,GPIO_Pin_3); //DC=1
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); //CS=0
	GPIO_ResetBits(GPIOA,GPIO_Pin_5); //SCL=0
	GPIO_SetBits(GPIOA,GPIO_Pin_7); //SDA=1
	GPIO_SetBits(GPIOA,GPIO_Pin_5); //SCL=1
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5); //SCL=0
		if(Data&0x80)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_7); //SDA=1
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_7); //SDA=0
		}
		
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //SCL=1
		
		Data<<=1;
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_0); //CS=1
}

/****************16IC初始化*******************/
static void ST7789_Init_16(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
	delay_ms(500);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	delay_ms(500);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
	
	
	delay_ms(300);
	
	LcdWriCommand(0x11);
	delay_ms(300);
	
	LcdWriCommand(0x36);
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
	
	LcdWriCommand(0x3A);//
	LcdWriData(0x05);//RGB 18-bit
	
	LcdWriCommand(0x29);//display on
	
	delay_ms(200);

}

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
void display_rgb(unsigned int dat)
{	unsigned int i,j;
	address();

	for(i=0;i<240;i++)		//64
	{		
		for (j=0;j<240;j++) //128
		{WriteDAT(dat>>8,dat); }
	}	
}

/****************24IC初始化*******************/
static void delayms(int count)
{
	int i,j;
    for(i=0;i<count;i++)		
    for(j=0;j<400;j++);	
}