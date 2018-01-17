#include "lcd.h"
#include "delay.h"
#include "LCDFONT.h"
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


/********************д����*********************/
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
	addr2 |= (addr1&0xf8);  //��λ����
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);  //RS=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;  //����
	GPIOA->ODR |= addr2;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
}

/*********************д�������*********************/
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
	GPIOA->ODR &= 0xff00;   //����
	GPIOA->ODR |= para1;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
}

/*
* �������ܣ�LCDд16λ����
* ���������data_1:�߰�λ���ݣ�data_2:�Ͱ�λ����
* ���������
* ����ֵ  ����
*/
void LCD_WR_data(unsigned char data_1,unsigned char data_2)
{
	
	u8 i,data_3=0,data3,data_4=0,data4;
	data3 = data_1;
	data4 = data_2;
	for (i=0;i<3;i++)
	{
		data_3 = data_3 << 1;
		data_3 = data_3 | (data3&1);
		data3 = data3 >> 1;
	} //end of for
	
	for(i=0;i<3;i++)
	{
		data_4 = data_4 << 1;
		data_4 = data_4 | (data4&1);
		data4 = data4 >> 1;
	} //end of for
	data_3 |= (data_1&0xf8);
	data_4 |= (data_2&0xf8);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);   //RS=1
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;   //����
	GPIOA->ODR |= data_3;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	GPIOA->ODR &= 0xff00;   //����
	GPIOA->ODR |= data_4;
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //WR=0
	GPIO_SetBits(GPIOA,GPIO_Pin_8);   //WR=1
	
}

/****************LCD��ʼ������*******************/
//�ͺţ��ξ��Ƽ�0.96��
void LCD_Init(void)
{
	LCD_GPIO_Init(); //LCD���ų�ʼ��
//	BK_ON;  //���⿪
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
	LCD_WR_command(0x13); //��ͨģʽ��ʾ
	LCD_WR_command(0x29); //Display on   
	delay_ms(20);
}


void display_pic(u16 bk)
{
  unsigned int i,j;
  LCD_qu(0,0,0x3f,0x7f);
  
	for(i=0;i<128;i++)
	{	
		for (j=0;j<64;j++)
		{ LCD_WR_data(bk>>8,bk);}	
	}
}

///************�ֲ�����******************/
void LCD_qu(u8 x,u8 y,u8 xend,u8 yend)
{
	
	LCD_WR_command(0x2a);    //Column address set ���ҿ��
	LCD_WR_para(0x00);
	LCD_WR_para(x+1);
	LCD_WR_para(0x00);
	LCD_WR_para(xend+1);
	LCD_WR_command(0x2b);    //Row Address Set   ���¿��
	LCD_WR_para(0x00);
	LCD_WR_para(y+2);     //ȥ������ʾ����
	LCD_WR_para(0x00);
	LCD_WR_para(yend+2);
	LCD_WR_command(0x2c);
}

void address(void)
{             
	LCD_WR_command(0x2A);
	LCD_WR_para(0x00);
	LCD_WR_para(0x01);
	LCD_WR_para(0x00);
	LCD_WR_para(0x3f+1);

	LCD_WR_command(0x2B);
	LCD_WR_para(0x00);
	LCD_WR_para(0x02);
	LCD_WR_para(0x00);
	LCD_WR_para(0x7f+2);

	LCD_WR_command(0x2C);
}
//ֻ����ʾRGB��ɫ
void rgb(void)											
{
	unsigned int i,j;
    address();

	for(i=0;i<42;i++)
	{	for (j=0;j<64;j++)
		{ LCD_WR_data(0xf8,0x00);}	//R	
	}

	for(i=42;i<84;i++)
	{	for (j=0;j<64;j++)
		{ LCD_WR_data(0x07,0xe0);}	//G
	}

	for(i=84;i<128;i++)
	{	for (j=0;j<64;j++)
		{ LCD_WR_data(0x00,0x1f);}	//B		
	}

}

//void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
//{
//	LCD_qu(x,y,x,y);//���ù��λ�� 
//	LCD_WR_data(color>>8,color); 	    
//} 

/*******************************************/
void SetBkColor(uint8 y,uint16 bk)
{
	unsigned int i,j;
	LCD_qu(0,y,0x40,y+15);
  
	for(i=0;i<16;i++)
	{	for (j=0;j<66;j++)
		{ LCD_WR_data(bk>>8,bk);}	
	}
}
///**************��������*******************/
//����ĸ��ֽڵĴ�С������д����ɫ
void qingqu(u8 x,u8 y,u16 bk)
{
	u8 i,j;
	LCD_qu(x,y,x+32-1,y+16-1); //�ĸ��ֽ�4*8=32��ǰ������ֵ����㣬���������յ�

	for(j=0;j<16;j++)
		for(i=0;i<32;i++)
		{
			LCD_WR_data(bk>>8,bk);
		}
}


/*��ʾADC_KEY��ADCֵ*/
void showshuzi(uint8 x,uint8 y,uint16 num,u16 bk)
{
	u8 b,temp1,count=0,num1;
	u32 i=1;
	qingqu(x,y,bk);
	do
	{
		++count;
		i *= 10;
	}while(i<=num);	 //ͳ������һ���ж���λ
	for(b=0;b<count;b++)
	{
		temp1=((int)num/mypow(10,count-b-1))%10; //��ȡÿһλ
		num1 = temp1; //��ȡ��ģ���������Ӧ����
		showchar(x,y,num1,bk);  //��ʾ�ַ�
		x+=8;
	}
}

/******m^n��ֵ******************/
uint32 mypow(uint8 m,uint8 n)
{
	uint32 result=1;	 
	while(n--)result*=m;    
	return result;
}

/************��ʾ�ַ�************/
void showchar(u8 x,u8 y,u8 num,u16 bk)
{
	u8 i,j,temp;
	LCD_qu(x,y,x+8-1,y+16-1);      //��������Ĵ�С
	for(j=0;j<16;j++)
	{
		temp = shuzizimo[num][j];  //��ȡ��Ӧ�ַ���ģ����
		for(i=0;i<8;i++)     //��λ����������
		{
			if(temp&0x01) LCD_WR_data(fontcolor>>8,fontcolor);
			else LCD_WR_data(bk>>8,bk);
			temp >>= 1; 
		}
	}

}
