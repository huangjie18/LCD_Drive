#include "lcd.h"
#include "delay.h"


//lcd�ӿڳ�ʼ��
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);//ʹ��GPIOD��GPIOE��ʱ����
	
	//GPIOD��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_0;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);  //GND
	GPIO_SetBits(GPIOE,GPIO_Pin_13);    //VCC
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