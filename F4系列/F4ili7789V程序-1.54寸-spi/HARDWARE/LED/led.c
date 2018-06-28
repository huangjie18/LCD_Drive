#include "led.h"
#include "stdlib.h"
#include "delay.h"
#include "spi.h"

///****************写命令函数*******************/
//static void LcdWriCommand(unsigned char command)
//{
//	u8 i;
//	DC = 0; //4线SPI

//	for(i=0;i<8;i++)
//	{
//		if(command&0x80)
//		{
//			SDA = 1;
//		}
//		else
//		{
//			SDA = 0;
//		}
//		SCL = 0;
//		SCL = 1;

//		command<<=1;
//	}

//}

///****************写数据函数*******************/
//static void LcdWriData(unsigned char Data)
//{
//	u8 i;
//	DC = 1; //4线SPI
//	
//	for(i=0;i<8;i++)
//	{
//		
//		if(Data&0x80)
//		{
//			SDA = 1;
//		}
//		else
//		{
//			SDA = 0;
//		}
//		SCL = 0;
//		SCL = 1;
//		
//		Data<<=1;
//	}

//}
/*
文件说明：该LCD驱动适合正点原子F1和F4开发板使用
文件使用：适合8线并口传输，只需要修改LCD_Init初始驱动
          接线按照lcd.h里的定义接
 */
void LCD_Writ_Bus(int data)  //并行数据写入函数
{
    u8 i, temp;
    LCD_CS = 0;
    for(i = 0; i < 16; i++)
    {
        temp = (data >> i) & 1;
        switch(i)
        {
            case 0:
                LCD_DB0 = temp;
                break;
            case 1:
                LCD_DB1 = temp;
                break;
            case 2:
                LCD_DB2 = temp;
                break;
            case 3:
                LCD_DB3 = temp;
                break;
            case 4:
                LCD_DB4 = temp;
                break;
            case 5:
                LCD_DB5 = temp;
                break;
            case 6:
                LCD_DB6 = temp;
                break;
            case 7:
                LCD_DB7 = temp;
                break;
            case 8:
                LCD_DB8 = temp;
                break;
            case 9:
                LCD_DB9 = temp;
                break;
            case 10:
                LCD_DB10 = temp;
                break;
            case 11:
                LCD_DB11 = temp;
                break;
            case 12:
                LCD_DB12 = temp;
                break;
            case 13:
                LCD_DB13 = temp;
                break;
            case 14:
                LCD_DB14 = temp;
                break;
            case 15:
                LCD_DB15 = temp;
                break;
        }
    }
    LCD_WR = 0;
    LCD_WR = 1;
    LCD_CS = 1;
}

/***************************写数据**********************************************/
void LCD_WR_DATA(int da)
{
	#if (spi_mode != 0)
    LCD_RS = 1;
    LCD_Writ_Bus(da);
	#else
	LCD_DC = 1;
	SPI1_ReadWriteByte(da);
	#endif
}
/***************************写命令**************************************************/
void LCD_WR_REG(int reg)
{
	#if (spi_mode != 0)
    LCD_RS = 0;
    LCD_Writ_Bus(reg);
	#else
	LCD_DC = 0;
	SPI1_ReadWriteByte(reg);
	#endif
}
/****************************写命令和数据**********************************************/
void LCD_WR_REG_DATA(int reg, int da)
{
    LCD_WR_REG(reg);
    LCD_WR_DATA(da);
}


void GPIO_5510_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE
                           | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 |
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_14 |
                                  GPIO_Pin_15
                                  | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    LCD_CS = 1;
    LCD_RD = 1;
    LCD_BL = 1;
    LCD_WR = 1;
}
/****************初始化命令*******************/
void LCD_Init()
{
	LCD_RST = 1;  //SPI复位
	RST = 1;
	delay_ms(100);
	
    RST = 0;
	LCD_RST = 0;  //SPI复位
    delay_ms(100);
	
    RST = 1;
	LCD_RST = 1;  //SPI复位
    delay_ms(50);



    //初始化代码

    LCD_WR_REG(0x11);
    delay_ms(120);
    LCD_WR_REG(0x36);
    LCD_WR_DATA (0x00);
    LCD_WR_REG(0x3a);
    LCD_WR_DATA (0x05);
    LCD_WR_REG(0x21);
    LCD_WR_REG(0xE7);
    LCD_WR_DATA (0x00);  //10h-2 data;00h-1data
    LCD_WR_REG(0x2a);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0xef);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0xef);
//---ST7789V Frame rate setting------//
    LCD_WR_REG(0xb2);
    LCD_WR_DATA (0x0c);
    LCD_WR_DATA (0x0c);
    LCD_WR_DATA (0x00);
    LCD_WR_DATA (0x33);
    LCD_WR_DATA (0x33);
    LCD_WR_REG(0xb7);
    LCD_WR_DATA (0x35);
//--------ST7789V Power setting--------//
    LCD_WR_REG(0xbb);
    LCD_WR_DATA (0x2a);
    LCD_WR_REG(0xc0);
    LCD_WR_DATA (0x2c);
    LCD_WR_REG(0xc2);
    LCD_WR_DATA (0x01);
    LCD_WR_REG(0xc3);
    LCD_WR_DATA (0x0b);
    LCD_WR_REG(0xc4);
    LCD_WR_DATA (0x20);
    LCD_WR_REG(0xc6);
    LCD_WR_DATA (0x0f);
    LCD_WR_REG(0xd0);
    LCD_WR_DATA (0xa4);
    LCD_WR_DATA (0xa1);
    LCD_WR_REG(0xe9);
    LCD_WR_DATA (0x11);
    LCD_WR_DATA (0x11);
    LCD_WR_DATA (0x03);

//--------------ST7789V
    LCD_WR_REG(0xe0);
    LCD_WR_DATA (0xf0);
    LCD_WR_DATA (0x09);
    LCD_WR_DATA (0x13);
    LCD_WR_DATA (0x0a);
    LCD_WR_DATA (0x0b);
    LCD_WR_DATA (0x06);
    LCD_WR_DATA (0x38);
    LCD_WR_DATA (0x33);
    LCD_WR_DATA (0x4f);
    LCD_WR_DATA (0x04);
    LCD_WR_DATA (0x0d);
    LCD_WR_DATA (0x19);
    LCD_WR_DATA (0x2e);
    LCD_WR_DATA (0x2f);
    LCD_WR_REG(0xe1);
    LCD_WR_DATA (0xf0);
    LCD_WR_DATA (0x09);
    LCD_WR_DATA (0x13);
    LCD_WR_DATA (0x0a);
    LCD_WR_DATA (0x0b);
    LCD_WR_DATA (0x06);
    LCD_WR_DATA (0x38);
    LCD_WR_DATA (0x33);
    LCD_WR_DATA (0x4f);
    LCD_WR_DATA (0x04);
    LCD_WR_DATA (0x0d);
    LCD_WR_DATA (0x19);
    LCD_WR_DATA (0x2e);
    LCD_WR_DATA (0x2f);
    delay_ms(150);
    LCD_WR_REG(0x29);
	#if(spi_mode == 0)
	  LCD_WR_REG(0x2A);     //Column Address Set
	  LCD_WR_DATA(0x00);
	  LCD_WR_DATA(0x00);   //0
	  LCD_WR_DATA(0x0);
	  LCD_WR_DATA(0xEF);   //239

	  LCD_WR_REG(0x2B);     //Row Address Set
	  LCD_WR_DATA(0x00);
	  LCD_WR_DATA(0x00);   //0
	  LCD_WR_DATA(0x00);
	  LCD_WR_DATA(0xEF);   //239

      LCD_WR_REG(0x2C);
	#endif

}

/*************************三色函数**********************************************/
void LCD_Clear(u16 color)
{
    u16 length, hight;

	  LCD_WR_REG(0x2A);     //Column Address Set
	  LCD_WR_DATA(0x00);
	  LCD_WR_DATA(0x00);   //0
	  LCD_WR_DATA(0x0);
	  LCD_WR_DATA(0xEF);   //239

	  LCD_WR_REG(0x2B);     //Row Address Set
	  LCD_WR_DATA(0x00);
	  LCD_WR_DATA(0x00);   //0
	  LCD_WR_DATA(0x01);
	  LCD_WR_DATA(0x3F);   //239

      LCD_WR_REG(0x2C);
////
    for(hight = 0; hight < 240; hight++)
    {
        for(length = 0; length < 320; length++)
        {
            LCD_WR_DATA(BLACK);
        }
    }
	
	//RED
	for(hight = 0; hight < 113; hight++)
    {
        for(length = 0; length < 240; length++)
        {
            LCD_WR_DATA(RED);
        }
    }
	
	//GREEN
	for(hight = 0; hight < 113; hight++)
    {
        for(length = 0; length < 240; length++)
        {
            LCD_WR_DATA(GREEN);
        }
    }
	
    //BLUE
	for(hight = 0; hight < (0X13F-113-113); hight++)
    {
        for(length = 0; length < 240; length++)
        {
            LCD_WR_DATA(BLUE);
        }
    }
}

static void WriteDAT(unsigned char DH,unsigned char DL)		
{
	LCD_WR_DATA(DH);
	LCD_WR_DATA(DL);	
}
//测试程序
void display_test(void)
{
	 u16 length, hight;
	 u8 i,j;

	
	for(hight = 0; hight < 240; hight++)
    {
        for(length = 0; length < 240; length++)
        {
            LCD_WR_DATA(BLACK>>8);
			LCD_WR_DATA(BLACK&0xff);
        }
    }
	
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT(RED>>8,RED&0xff);
			}
			else if(j<=160)
			{
				WriteDAT(GREEN>>8,GREEN&0xff);
			}
			else
			{
				WriteDAT(BLUE>>8,BLUE&0xff);
			}
		}
	}
	for(i=0;i<120;i++)
	{
		for(j=0;j<240;j++)
		{
			if(j<=80)
			{
				WriteDAT(WHITE>>8,WHITE&0xff);
			}
			else if(j<=160)
			{
				WriteDAT(BLACK>>8,BLACK&0xff);
			}
			else
			{
				WriteDAT(GRAY>>8,GRAY&0xff);
			}
		}
	}
}

