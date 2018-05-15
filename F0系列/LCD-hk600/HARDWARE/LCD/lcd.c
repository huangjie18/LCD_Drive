#include "lcd.h"
#include "delay.h"
/***************************************************************
//˵��������ST7789V����ʹ�õ���3��SPI������������4��
//����SPI������SPI��������DCXλ�����ߵ�ģʽ������һ�����ŵ����ã�������ģʽ�£�DCXλ���Ǿ���SPI���ͳ�ȥ��û��ר�ŵ�DC���š�
//������ˣ������Խ�ʡһ�����ţ�����Ҳ��ĳЩ���������˱׶ˡ�
***************************************************************/

#define LCD_WR_command(command) LcdWriCommand(command)
#define LCD_WR_para(data)  LcdWriData(data)
#define Delay(ms) delay_ms(ms)
u8 mode=4;
//��������
static void ST7789_Init_16(void); //16λ��1.3����
static void LcdWriCommand(unsigned char command); //д����
static void LcdWriData(unsigned char Data);       //д����
static void address(void);                        //����
static void WriteDAT(unsigned char DH,unsigned char DL); //д��ɫ����
//����ʵ��
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOF, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4
	| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

}

/****************LCD��ʼ������*******************/
void LCD_Init(void)
{
	ST7789_Init_16();   //7789������ʼ�����룬16���ŵ� SPI
//	ST7789_Init_24();   //24���ŵ� DB0-DB15
}
/****************д�����*******************/
static void LcdWriCommand(unsigned char command)
{
	u8 i;
	DC = 0; //4��SPI
	CS = 0;
	//3��SPI����Ҫע��
	//����D/C=0��������������
	if(mode==3)
	{	
		SCL = 0;
		SDA = 0;
		SCL = 1;
	}

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
	CS = 1;
}
/****************д���ݺ���*******************/
static void LcdWriData(unsigned char Data)
{
	u8 i;
	DC = 1; //4��SPI
	CS = 0;
	
	//3��SPI
	//����D/C=1��������������
	if(mode==3)
	{
		SCL = 0;
		SDA = 1;
		SCL = 1;
	}
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
	CS = 1;
}

/****************16IC��ʼ��*******************/
static void ST7789_Init_16(void)
{


delay_ms(200);

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
		{WriteDAT(dat>>8,dat&0xff); }
	}	
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
void LcdWriCommand_8(u8 command)
{
	u16 temp;
	RS = 0;
	CS = 0;
	WR = 1;
	temp = GPIOA->IDR;
	temp = command|(temp&0xff00);
	GPIOA->ODR = temp;
	WR = 0;
	WR = 1;
	CS = 1;
	
}
void LcdWriData_8(u8 data)
{
	u16 temp;
	RS = 1;
	CS = 0;
	WR = 1;
	temp = GPIOA->IDR;
	temp = data|(temp&0xff00);
	GPIOA->ODR = temp;
	WR = 0;
	WR = 1;
	CS = 1;
}
/****************24IC��ʼ��*******************/
void ST7789_Init_24(void)
{
	delay_ms(200);
	
	LcdWriCommand_8(0x11);
	delay_ms(200);
	
	LcdWriCommand_8(0x36);  //ɨ�跽ʽ
	LcdWriData_8(0x00);
	LcdWriCommand_8(0x3a); 
	LcdWriData_8(0x05); 
	
	LcdWriCommand_8(0xb2); 
	LcdWriData_8(0x0c); 
	LcdWriData_8(0x0c); 
	LcdWriData_8(0x00); 
	LcdWriData_8(0x33); 
	LcdWriData_8(0x33); 
	
	LcdWriCommand_8(0xb7); 
	LcdWriData_8(0x35); 
	
	//---------------------------------ST7789S Power setting--------------------------------------// 
	
	LcdWriCommand_8(0xbb); 
	LcdWriData_8(0x2C); 

	
	LcdWriCommand_8(0xc0); 
	LcdWriData_8(0x2c); 
	
	LcdWriCommand_8(0xc2); 
	LcdWriData_8(0x01); 
	
	LcdWriCommand_8(0xc3); 
	LcdWriData_8(0x0b); 

	
	LcdWriCommand_8(0xc4); 
	LcdWriData_8(0x20); 
	
	LcdWriCommand_8(0xc6); 
	LcdWriData_8(0x0f); 
	
	LcdWriCommand_8(0xd0); 
	LcdWriData_8(0xa4); 
	LcdWriData_8(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	LcdWriCommand_8(0xe0); 
	LcdWriData_8(0xd0); 
	LcdWriData_8(0x06); 
	LcdWriData_8(0x01); 
	LcdWriData_8(0x0e); 
	LcdWriData_8(0x0e); 
	LcdWriData_8(0x08); 
	LcdWriData_8(0x32); 
	LcdWriData_8(0x44); 
	LcdWriData_8(0x40); 
	LcdWriData_8(0x08); 
	LcdWriData_8(0x10); 
	LcdWriData_8(0x0f); 
	LcdWriData_8(0x15); 
	LcdWriData_8(0x19); 
	
	LcdWriCommand_8(0xe1); 
	LcdWriData_8(0xd0); 
	LcdWriData_8(0x06); 
	LcdWriData_8(0x01); 
	LcdWriData_8(0x0f); 
	LcdWriData_8(0x0e); 
	LcdWriData_8(0x09); 
	LcdWriData_8(0x2f); 
	LcdWriData_8(0x54); 
	LcdWriData_8(0x44); 
	LcdWriData_8(0x0f); 
	LcdWriData_8(0x1d); 
	LcdWriData_8(0x1a); 
	LcdWriData_8(0x16); 
	LcdWriData_8(0x19); 
	
	LcdWriCommand_8(0x21);	//display inversion on
	LcdWriCommand_8(0x29);//display on

	delay_ms(120);
}
static void WriteDAT_8(unsigned char DH,unsigned char DL)
{
	LcdWriData_8(DH);
	LcdWriData_8(DL);
}
static void address_8(void)
{
	LcdWriCommand_8(0x2A);
	LcdWriData_8(0x00);
	LcdWriData_8(0x00);
	LcdWriData_8(0x01);
	LcdWriData_8(0x00);
	
	LcdWriCommand_8(0x2B);
	LcdWriData_8(0x00);
	LcdWriData_8(0x00);//3B
	LcdWriData_8(0x01);
	LcdWriData_8(0x00);

	LcdWriCommand_8(0x2C);
}

void display_test_8(void)
{
	u16 i,j;
	address_8();
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT_8(red>>8,red&0xff);
			}
			else if(j<=160)
			{
				WriteDAT_8(green>>8,green&0xff);
			}
			else
			{
				WriteDAT_8(blue>>8,blue&0xff);
			}
		}
	}
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT_8(white>>8,white&0xff);
			}
			else if(j<=160)
			{
				WriteDAT_8(black>>8,black&0xff);
			}
			else
			{
				WriteDAT_8(gray>>8,gray&0xff);
			}
		}
	}
//	for(i=0;i<240;i++)		//64
//	{		
//		for (j=0;j<240;j++) //128
//		{WriteDAT_8(red>>8,red&0xff); }
//	}
}