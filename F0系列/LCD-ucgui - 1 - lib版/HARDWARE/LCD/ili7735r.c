#include "ili7735r.h"
#include "delay.h"













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
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
}


/********************写命令*********************/
void LCD_WR_command(unsigned char addr1)
{
	u8 i,addr2 = 0,addr3,temp;
	addr3 = addr1;
	for(i=0;i<3;i++)
	{
		addr2 = addr2 << 1;
		addr2 = addr2 | (addr3 & 1);
		addr3 = addr3 >> 1;
	}
	addr2 |= (addr1&0xf8);  //八位数据
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);  //RS=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;  //清零
	GPIOA->ODR |= addr2;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
}

/*********************写命令参数*********************/
void LCD_WR_para(unsigned char para)
{
	u8 i,para1 = 0,para2;
	para2 = para;
	for(i=0;i<3;i++)
	{
		para1 = para1 << 1;
		para1 = para1 | (para2&1);
		para2 = para2 >> 1;
	}
	
	para1 |= (para&0xf8);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);   //RS=1
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;   //清零
	GPIOA->ODR |= para1;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
}

/********************写数据**************************/
void LCD_WR_data(unsigned char data_1,unsigned char data_2)
{
	u8 i,data_3=0,data3,data_4=0,data4;
	data3 = data_1;
	data4 = data_2;
	for(i=0;i<3;i++)
	{
		data_3 = data_3 << 1;
		data_3 = data_3 | (data3&1);
		data3 = data3 >> 1;
	}
	
	for(i=0;i<3;i++)
	{
		data_4 = data_4 << 1;
		data_4 = data_4 | (data4&1);
		data4 = data4 >> 1;
	}
	data_3 |= (data_1&0xf8);
	data_4 |= (data_2&0xf8);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);   //RS=1
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;   //清零
	GPIOA->ODR |= data_3;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;   //清零
	GPIOA->ODR |= data_4;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	
}

/****************LCD初始化命令*******************/
void TFT_Init(void)
{
	LCD_GPIO_Init(); //LCD引脚初始化
	GPIO_SetBits(GPIOA,GPIO_Pin_9);  //背光开
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); //CS=0
	
	
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
	LCD_WR_para(saomiao);//c8
	LCD_WR_command(0x29); //Display on   
	delay_ms(20);
}


void display_pic(u16 bk)
{
  unsigned int i,j;
  LCD_qu(0,0,0x3f,0x7f);
  
	for(i=0;i<128;i++)
	{	for (j=0;j<64;j++)
		{ LCD_WR_data(bk>>8,bk);}	
	}
}

///************局部开区******************/
void LCD_qu(u8 x,u8 y,u8 xend,u8 yend)
{
	
//	LCD_WR_command(0x2a);    //Column address set 左右宽度
//	LCD_WR_para(0x00);
//	LCD_WR_para(x);
//	LCD_WR_para(0x00);
//	LCD_WR_para(xend);
	LCD_WR_command(0x2a);    //Column address set 左右宽度
	LCD_WR_para(0x00);
	LCD_WR_para(x+1);
	LCD_WR_para(0x00);
	LCD_WR_para(xend+1);
	LCD_WR_command(0x2b);    //Row Address Set   上下宽度
	LCD_WR_para(0x00);
	LCD_WR_para(y+2);     //去掉不显示部分
	LCD_WR_para(0x00);
	LCD_WR_para(yend+2);
	LCD_WR_command(0x2c);
}

/*---------------------------------------
函数功能：LCD画点函数, 用指定颜色填充一个像素
入口参数：(x,y)点的位置，color颜色
----------------------------------------*/
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_qu(x,y,x,y);//设置光标位置 
	LCD_WR_data(color>>8,color); 	    
} 

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_qu(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_data(color>>8,color); //设置光标位置 	    
	} 					  	    
}