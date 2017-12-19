#include "led.h"
#include "stdlib.h"
#include "delay.h"
/*
�ļ�˵������LCD�����ʺ�����ԭ��F1��F4������ʹ��
�ļ�ʹ�ã��ʺ�8�߲��ڴ��䣬ֻ��Ҫ�޸�LCD_Init��ʼ����
		  ���߰���lcd.h��Ķ����
 */
void LCD_Writ_Bus(char data_1, char data_2)  //��������д�뺯��
{
	//����������оƬ���ź�lcd�����ݴ��������෴��������Ҫ�Ѵ������ݵߵ�˳���ٴ���
	u16 i, j, addr2 = 0, addr3 = 0, temp2, temp3;
	for (i = 0; i <= 7; i++)
	{
		addr2 = addr2 << 1;
		addr2 = addr2 | (data_1 & 1);
		data_1 = data_1 >> 1;
	}
	for (j = 0; j <= 7; j++)
	{
		addr3 = addr3 << 1;
		addr3 = addr3 | (data_2 & 1);
		data_2 = data_2 >> 1;
	}
	addr2 = addr2 << 8; //��Ϊ�õ�оƬ�����Ǹ߰�λ����������8λ
	addr3 = addr3 << 8;

	CS = 0;
	WR = 1;
	temp2 = (GPIOE->IDR & 0xff00);

#if defined STM32F40_41xxx
	GPIOE->BSRRH = temp2;  //��GPIOEȫ�����Ϊ0
	GPIOE->BSRRL = addr2;  //GPIOE�������
	WR = 0;  //д����ʹ��
	WR = 1;  //д����ʧ��
	CS = 1;

	CS = 0;
	WR = 1;
	temp3 = (GPIOE->IDR & 0xff00);
	GPIOE->BSRRH = temp3;
	GPIOE->BSRRL = addr3;
	WR = 0;
	WR = 1;
	CS = 1;   //�ر�Ƭѡʹ��

#elif defined STM32F10X_HD
	GPIOE->BSRR = temp2 << 16;
	GPIOE->BSRR = addr2;
	WR = 0;  //д����ʹ��
	WR = 1;  //д����ʧ��
	CS = 1;

	CS = 0;
	WR = 1;
	temp3 = (GPIOE->IDR & 0xff00);
	GPIOE->BSRR = temp3 << 16;
	GPIOE->BSRR = addr3;
	WR = 0;
	WR = 1;
	CS = 1;   //�ر�Ƭѡʹ��
#endif
}

void LCD_WR_DATA8(char VH, char VL) //��������-8λ����
{
	LCD_RS = 1;
	LCD_Writ_Bus(VH, VL);
}
/***************************д����**********************************************/
void LCD_WR_DATA(int da)
{
	LCD_RS = 1;
	LCD_Writ_Bus(da >> 8, da);
}
/***************************д����**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg >> 8, reg);
}
/****************************д���������**********************************************/
void LCD_WR_REG_DATA(int reg, int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}


/****************��ʼ������*******************/
void LCD_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;//���¶���һ���ṹ��

	//����ʱ���ߣ�stm32�У���Ƭ��û��
#ifdef STM32F40_41xxx   //�ж�оƬ����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	//�Խṹ��ı������г�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
	                              GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
#elif defined  STM32F10X_HD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	//�Խṹ��ı������г�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |
	                              GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
#endif
	RST = 0;
	delay_ms(20);
	RST = 1;
	delay_ms(10);


	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delay_ms(5);
	LCD_CS = 0; //��Ƭѡʹ��

	//�����ǳ�ʼ���룬����Ҫ֪��ȫ��ϸ�ڣ�һ���ɳ����ṩ
	//��Ҫ�޸�ʱҪ�ο������ֲ�,��ʼ������һ����ʾЧ��Ҳ��һ��

	LCD_WR_REG_DATA(0x0702, 0x3008);// Set internal timing, don?��t change this value
	LCD_WR_REG_DATA(0x0705, 0x0036);// Set internal timing, don?��t change this value
	LCD_WR_REG_DATA(0x070B, 0x1213);// Set internal timing, don?��t change this value
	LCD_WR_REG_DATA(0x0001, 0x0100); // set SS and SM bit
	LCD_WR_REG_DATA(0x0002, 0x0100); // set 1 line inversion
//	LCD_WR_REG_DATA(0x0003, 0x1008); // set GRAM write direction and BGR=1. //1030
	LCD_WR_REG_DATA(0x0003, 0x0030);
	LCD_WR_REG_DATA(0x0008, 0x0202); // set the back porch and front porch
	LCD_WR_REG_DATA(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WR_REG_DATA(0x000C, 0x0000); // RGB interface setting
	LCD_WR_REG_DATA(0x000F, 0x0000); // RGB interface polarity
	//*************Power On sequence ****************//
	LCD_WR_REG_DATA(0x0100, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_REG_DATA(0x0102, 0x0000); // VREG1OUT voltage
	LCD_WR_REG_DATA(0x0103, 0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(200); // Dis-charge capacitor power voltage
	LCD_WR_REG_DATA(0x0100, 0x1190); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_REG_DATA(0x0101, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
	delay_ms(50); // Delay 50ms
	LCD_WR_REG_DATA(0x0102, 0x001D); // VREG1OUT voltage
	delay_ms(50); // Delay 50ms
	LCD_WR_REG_DATA(0x0103, 0x2000); // VDV[4:0] for VCOM amplitude
	LCD_WR_REG_DATA(0x0281, 0x0001); // VCM[5:0] for VCOMH
	LCD_WR_REG_DATA(0x020b, 0x0000);
	delay_ms(50);
	LCD_WR_REG_DATA(0x0200, 0x0000); // GRAM horizontal Address
	LCD_WR_REG_DATA(0x0201, 0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WR_REG_DATA(0x0300, 0x0000);
	LCD_WR_REG_DATA(0x0301, 0x0202);
	LCD_WR_REG_DATA(0x0302, 0x0202);
	LCD_WR_REG_DATA(0x0305, 0x0202);
	LCD_WR_REG_DATA(0x0306, 0x0202);
	LCD_WR_REG_DATA(0x0307, 0x0202);
	LCD_WR_REG_DATA(0x0308, 0x0202);
	LCD_WR_REG_DATA(0x0309, 0x0202);
	LCD_WR_REG_DATA(0x030C, 0x0202);
	LCD_WR_REG_DATA(0x030D, 0x0202);
	//------------------ Set GRAM area ---------------//
	LCD_WR_REG_DATA(0x0210, 0x0000); // Horizontal  Start Address
	LCD_WR_REG_DATA(0x0211, 0x00EF); // Horizontal  End Address
	LCD_WR_REG_DATA(0x0212, 0x0000); // Vertical  Start Address
	LCD_WR_REG_DATA(0x0213, 0x018F); // Vertical  End Address
	LCD_WR_REG_DATA(0x0400, 0x3100); // Gate Scan Line
	LCD_WR_REG_DATA(0x0401, 0x0001); // NDL,VLE, REV
	LCD_WR_REG_DATA(0x0404, 0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	LCD_WR_REG_DATA(0x0500, 0x0000);//Partial Image 1 Display Position
	LCD_WR_REG_DATA(0x0501, 0x0000); //Partial Image 1 RAM Start/End Address
	LCD_WR_REG_DATA(0x0502, 0x0000); //Partial Image 1 RAM Start/End Address
	LCD_WR_REG_DATA(0x0503, 0x0000); //Partial Image 2 Display Position
	LCD_WR_REG_DATA(0x0504, 0x0000);//Partial Image 2 RAM Start/End Address
	LCD_WR_REG_DATA(0x0505, 0x0000); //Partial Image 2 RAM Start/End Address
	//-------------- Panel Control -------------------//
	LCD_WR_REG_DATA(0x0010, 0x0010); //DIVI[1:0];RTNI[4:0]
	LCD_WR_REG_DATA(0x0011, 0x0600); //NOWI[2:0];SDTI[2:0]
	LCD_WR_REG_DATA(0x0020, 0x0002); //DIVE[1:0];RTNE[5:0]
	LCD_WR_REG_DATA(0x0007, 0x0173); // 262K color and display ON

	LCD_WR_REG(0x0202);
	delay_ms(20);
}

/*************************��ɫ����**********************************************/
//9225������ģ���Ҫ�����
//void LCD_Clear()
//{
//	u8 i,j;
//	LCD_WR_REG_DATA(0x36,0x00af);     //horizontal address  ˮƽ��ַ�߰�λ
//	LCD_WR_REG_DATA(0x37,0x0000);	  //horizontal address  ˮƽ��ַ�Ͱ�λ
//	LCD_WR_REG_DATA(0x38,0x00db);	  //vertical address    ��ֱ��ַ�߰�λ
//	LCD_WR_REG_DATA(0x39,0x0000);     //vertical address    ��ֱ��ַ�߰�λ
//
//	LCD_WR_REG_DATA(0x20,0x0000);    //GRAM address set   ���õ�ַ�������ĳ�ʼֵ
//	LCD_WR_REG_DATA(0x21,0x0000);
//
//	LCD_WR_REG(0x22);
//
//	RS = 1;  //д����
//	CS = 0;
//	for (i = 0; i < 220; i++)
//	{
//		if(i<73)
//		 {
//			for(j=0;j<176;j++)
//			 {
//				LCD_WR_DATA(red);
//			 }
//		 }
//		 else if(i<146)
//		 {
//			 for(j=0;j<176;j++)
//			 {
//				 LCD_WR_DATA(blue);
//			 }
//		 }
//		 else
//		 {
//			 for(j=0;j<176;j++)
//			 {
//				 LCD_WR_DATA(green);
//			 }
//		 }
//
//	}
//
//}
void LCD_Clear()
{
	u16 i, j;

	RS = 1;  //д����
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