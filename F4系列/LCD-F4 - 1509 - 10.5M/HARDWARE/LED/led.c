#include "led.h"
#include "stdlib.h"
#include "delay.h"
u16 LCD_id=0;
/*
文件说明：该LCD驱动适合正点原子F1和F4开发板使用
文件使用：适合8线并口传输，只需要修改LCD_Init初始驱动
		  接线按照lcd.h里的定义接
 */
 
#define WRITE_C(reg,da) LCD_WR_REG_DATA(reg,da)

void LCD_Writ_Bus(char data_1, char data_2)  //并行数据写入函数
{
	u16 i,temp1,temp2;
	CS = 0;
	WR = 1;
	for(i=0;i<8;i++)
	{
		temp1 = (data_1>>i)&1;
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
	CS = 1;
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

void LCD_IN(void)
{

}

void LCD_OUT(void)
{

	
}
/****************初始化命令*******************/
void LCD_Init(u16 LCD_ID)
{

	RST = 0;
	delay_ms(100);
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
void LCD_Clear(u16 LCD_ID)
{
	u16 i, j;
	if(LCD_ID == 5420)
	{
		LCD_WR_REG_DATA(0x0210, 0x0000);	//X_Start);	//x start
		LCD_WR_REG_DATA(0x0211, 0x00ef);	//X_End);		//x end
		LCD_WR_REG_DATA(0x0212, 0x0000);	//Y_Start);	//y start
		LCD_WR_REG_DATA(0x0213, 0x018f);	//Y_End);		//y end
		LCD_WR_REG_DATA(0x0201, 0x0000);	//Y_Start);	//y addres
		LCD_WR_REG_DATA(0x0200, 0x0000);	//X_Start);	//x addres

		LCD_WR_REG(0x0202);
		
	}
	else if (LCD_ID == 9225)
	{
		LCD_WR_REG_DATA(0x36,0x00af);     //horizontal address  水平地址高八位
		LCD_WR_REG_DATA(0x37,0x0000);	  //horizontal address  水平地址低八位
		LCD_WR_REG_DATA(0x38,0x00db);	  //vertical address    垂直地址高八位
		LCD_WR_REG_DATA(0x39,0x0000);     //vertical address    垂直地址高八位

		LCD_WR_REG_DATA(0x20,0x0000);    //GRAM address set   设置地址计数器的初始值
		LCD_WR_REG_DATA(0x21,0x0000);

		LCD_WR_REG(0x22);
	}
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


void SLEEPEXIT(void)
{
	LCD_WR_REG_DATA(0x10, 0x0008);						 
	LCD_WR_REG_DATA(0x15, 0x7040);							
	LCD_WR_REG_DATA(0x11, 0x0510);	   //0x0110
	LCD_WR_REG_DATA(0x10, 0x3628);	 
	LCD_WR_REG_DATA(0x12, 0x0006);	 
	LCD_WR_REG_DATA(0x13, 0x0c2f);	  
	delay_ms(40); 
	LCD_WR_REG_DATA(0x12, 0x0015); //0x0016		 
	delay_ms(40);				
	LCD_WR_REG_DATA(0x10, 0x3640);	//0x3620  //0x3640	  
	LCD_WR_REG_DATA(0x13, 0x2b28);		//0x2D24  0x2C2f
	delay_ms(20); 
	LCD_WR_REG_DATA(0x07, 0x0001);
    LCD_WR_REG_DATA(0x07, 0x0021);
    LCD_WR_REG_DATA(0x07, 0x0023);
	LCD_WR_REG_DATA(0x07, 0x0033);
	LCD_WR_REG_DATA(0x07, 0x0133);

}

void SLEEPON(void)
{

    LCD_WR_REG_DATA(0x07, 0x0032);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0022);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0002);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0000);
    delay_ms(10);
    LCD_WR_REG_DATA(0x17, 0x0001);
    LCD_WR_REG_DATA(0x13, 0x0000);
    LCD_WR_REG_DATA(0x12, 0x0000);
    LCD_WR_REG_DATA(0x10, 0x0008);
    delay_ms(10);
    LCD_WR_REG_DATA(0x10, 0x000A);

}

void address(void)
{
	LCD_WR_REG_DATA(0x50,0x0000);
	LCD_WR_REG_DATA(0x51,0x00ef);
	LCD_WR_REG_DATA(0x52,0x0000);
	LCD_WR_REG_DATA(0x53,0x018f);
	LCD_WR_REG_DATA(0x20,0x0000);
	LCD_WR_REG_DATA(0x21,0x0000);
	LCD_WR_REG(0x22);
}


void LCD_Read(void)
{
	u16 temp;
	CS = 0;
	RS = 0;
	WR = 1;
	GPIOE->ODR = 0;
	WR = 0;
	WR = 1;
	RS = 1;
	LCD_IN();  //设置引脚为输入
	RD = 0;
	delay_us(5);
	RD = 1;
	LCD_id = GPIOE->IDR;
	temp = LCD_id &0xff00; 
	RD = 0;
	LCD_id = GPIOE->IDR;
	RD = 1;
	temp |= (LCD_id >> 8);
	LCD_id = temp;
	LCD_OUT(); //设置引脚为输出
	CS = 1;
}