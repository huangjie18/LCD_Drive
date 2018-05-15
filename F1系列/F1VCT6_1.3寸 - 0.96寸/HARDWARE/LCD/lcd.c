#include "lcd.h"
#include "delay.h"


//lcd�ӿڳ�ʼ��
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);//ʹ��GPIOD��GPIOE��ʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //����ʱ���߿�
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //�ر�JTAG,����SW-DP,��ΪҪʹ��PB3
	
	//GPIOD��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_5|GPIO_Pin_3|GPIO_Pin_1;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_SetBits(GPIOD,GPIO_Pin_7);     //VCC
	GPIO_ResetBits(GPIOD,GPIO_Pin_5);  //GND
	
}

//lcd�ӿڳ�ʼ��
void LCD_GPIO_Init_1(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOD��GPIOE��ʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //����ʱ���߿�
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //�ر�JTAG,����SW-DP,��ΪҪʹ��PB3
	//GPIOD��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_11;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3
								  |GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //GND
	GPIO_ResetBits(GPIOD,GPIO_Pin_11);  //GND
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);  //GND
	GPIO_SetBits(GPIOB,GPIO_Pin_4);    //VCC
	GPIO_SetBits(GPIOB,GPIO_Pin_3);    //VCC
	LEDK_1 = 0;
	LEDA_1 = 1;
}

/****************д�����*******************/
static void LcdWriCommand(unsigned char command)
{
	u8 i;
	DC = 0; //4��SPI

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
/****************д�����*******************/
//����
static void LcdWriCommand_1(unsigned char command)
{
	u8 i;
	DC_1 = 0; //4��SPI

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

/****************д���ݺ���*******************/
//����
static void LcdWriData_1(unsigned char Data)
{
	u8 i;
	DC_1 = 1; //4��SPI

	
	
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

/****************д���ݺ���*******************/
static void LcdWriData(unsigned char Data)
{
	u8 i;
	DC = 1; //4��SPI
	
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

//LCD��ʼ������
void LCD_Init(void)
{
	RES = 1;
	delay_ms(100);
	RES = 0; //LCD��λ
	delay_ms(100);
	RES = 1;
	delay_ms(120);
	
	LcdWriCommand(0x11);
	delay_ms(200);
	
	LcdWriCommand(0x36);  //ɨ�跽ʽ
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


//���Գ�ʼ��
void LCD_Init_1(void)
{
	LCD_GPIO_Init_1();
	RES_1 = 1;
	delay_ms(100);
	RES_1 = 0; //LCD��λ
	delay_ms(300);
	RES_1 = 1;
	delay_ms(120);
	
	LcdWriCommand_1(0x11);
	delay_ms(200);
	
	LcdWriCommand_1(0x36);  //ɨ�跽ʽ
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

//����ʾ������
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
//���Գ���
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
//0.96�����ų�ʼ��
void LCD_GPIOInit_0(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD
							|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);//ʹ��GPIOD��GPIOE��ʱ����

	
	//GPIOD��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;				 // �˿�����
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				 // �˿�����
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_4);     //VCC
	BLK_0 = 1;  //���⿪
}

/****************д�����*******************/
static void LCD_WR_command(unsigned char command)
{
	u8 i;
	CS_0 = 0;
	DC_0 = 0; //4��SPI
	
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

/****************д���ݺ���*******************/
static void LCD_WR_para(unsigned char Data)
{
	u8 i;
	CS_0 = 0;
	DC_0 = 1; //4��SPI

	
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

//��ʼ������
void LCD_Init_0(void)
{
	RES_0 = 1;
	delay_ms(100);
	RES_0 = 0; //LCD��λ
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
	LCD_WR_para(0x68);//
	LCD_WR_command(0x29); //Display on   
	delay_ms(20);
}
static void LCD_WR_data(u8 data1,u8 data2)
{
	LCD_WR_para(data1);
	LCD_WR_para(data2);
}
/**********************��ʾ��ɫ*******************/
void display_rgb(void)
{
  u16 i,j,k=0;
	//B006�ͺŵĿ���
  LCD_WR_command(0x2a);              //Horizontal Address Start Position
  LCD_WR_para(0x00);
  LCD_WR_para(0x00);
  LCD_WR_para(0x00);
  LCD_WR_para(0xA0);
  LCD_WR_command(0x2b);              //Vertival Address end Position
  LCD_WR_para(0x00);
  LCD_WR_para(0x1A-2);
  LCD_WR_para(0x00);
  LCD_WR_para(0x69);
  LCD_WR_command(0x2c);
  
	
//  LCD_WR_command(0x2a);              //Horizontal Address Start Position
//  LCD_WR_para(0x00);
//  LCD_WR_para(0x00);
//  LCD_WR_para(0xff);
//  LCD_WR_para(0xff);
//  LCD_WR_command(0x2b);              //Vertival Address end Position
//  LCD_WR_para(0x00);
//  LCD_WR_para(0x00);
//  LCD_WR_para(0xff);
//  LCD_WR_para(0xff);
//  LCD_WR_command(0x2c);
  
	
	for(i=0;i<21;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(0xF8,0x00);}	//R
	}
	
	


	for(i=21;i<50;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(green>>8,green&0xff);}	//G
	}

	for(i=50;i<80;i++)
	{	for (j=0;j<160;j++)
		{ LCD_WR_data(blue>>8,blue&0xff);}	//B
	}

//	for(i=0;i<800;i++)
//	{	for (j=0;j<1600;j++)
//		{ LCD_WR_data(red>>8,red&0xff);}	//B
//	}
 }

 //����ʾ������
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
//���Գ���
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