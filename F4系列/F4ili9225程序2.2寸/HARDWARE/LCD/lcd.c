#include "lcd.h"
#include "stdlib.h"
#include "lcdfont.h"
#include "delay.h"

void LCD_Writ_Bus(char data_1,char data_2)   //��������д�뺯��
{	
	//����������оƬ���ź�lcd�����ݴ��������෴��������Ҫ�Ѵ������ݵߵ�˳���ٴ���
	u16 i,j, addr2 = 0,addr3 = 0,temp2,temp3;
	for(i=0;i<=7;i++)
	{
		addr2 = addr2 << 1;
		addr2 = addr2 | (data_1 & 1);
		data_1 = data_1 >> 1;
	}
	for(j=0;j<=7;j++)
	{
		addr3 = addr3 << 1;
		addr3 = addr3 | (data_2 & 1);
		data_2 = data_2 >> 1;
	}
	addr2 = addr2<<8; //��Ϊ�õ�оƬ�����Ǹ߰�λ����������8λ
	addr3 = addr3<<8;
	
	CS = 0;
	WR = 1;
	temp2 = (GPIOE->IDR&0xff00);
	GPIOE->BSRRH = temp2;
	GPIOE->BSRRL = addr2;
	WR = 0;  //д����ʹ��
	WR = 1;  //д����ʧ��
	CS = 1;
	
	CS = 0;
	WR = 1;
	temp3 = (GPIOE->IDR&0xff00);
	GPIOE->BSRRH = temp3;
	GPIOE->BSRRL = addr3;
	WR = 0;
	WR = 1;
	CS = 1;   //�ر�Ƭѡʹ��
}

void LCD_WR_DATA8(char VH,char VL) //��������-8λ����
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}
/***************************д����**********************************************/
void LCD_WR_DATA(int da)   
{
    LCD_RS=1;
	LCD_Writ_Bus(da>>8,da);
}
/***************************д����**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg>>8,reg);
}
/****************************д���������**********************************************/
void LCD_WR_REG_DATA(int reg,int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}


/****************��ʼ������*******************/
 void LCD_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;//���¶���һ���ṹ��
	
	//����ʱ���ߣ�stm32�У���Ƭ��û��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);
	
	//�Խṹ��ı������г�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
	GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);//�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Init(GPIOD,&GPIO_InitStructure);//�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
	
	RST = 0;
	delay_ms(20);
	RST = 1;
	delay_ms(10);
	
	
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delay_ms(5);
	LCD_CS =0;  //��Ƭѡʹ��
	
	//�����ǳ�ʼ���룬����Ҫ֪��ȫ��ϸ�ڣ�һ���ɳ����ṩ
	//��Ҫ�޸�ʱҪ�ο������ֲ�,��ʼ������һ����ʾЧ��Ҳ��һ��
	
	LCD_WR_REG(0x00D0);
	LCD_WR_DATA(0x0003);
	LCD_WR_REG(0x00EB);
	LCD_WR_DATA(0x0B00);
	LCD_WR_REG(0x00EC);
	LCD_WR_DATA(0x000F);
	
	LCD_WR_REG(0x0001);
	LCD_WR_DATA(0x011C); //011c
	LCD_WR_REG(0x0002);
	LCD_WR_DATA(0x0100);
	//ɨ�跽ʽ����ɫ����
	LCD_WR_REG(0x0003);
	LCD_WR_DATA(0x0030); //1030
	
	LCD_WR_REG(0x0007);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0008);
	LCD_WR_DATA(0x0202);
	LCD_WR_REG(0x000F);
	LCD_WR_DATA(0x0901);
	LCD_WR_REG(0x0010);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0011);
	LCD_WR_DATA(0x1B41);
	LCD_WR_REG(0x0012);
	LCD_WR_DATA(0x200E);
	LCD_WR_REG(0x0013);
	LCD_WR_DATA(0x0052);
	LCD_WR_REG(0x0014);
	LCD_WR_DATA(0x475C);
	
	LCD_WR_REG(0x0030);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0031);
	LCD_WR_DATA(0x00DB);
	LCD_WR_REG(0x0032);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0033);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0034);
	LCD_WR_DATA(0x00DB);
	LCD_WR_REG(0x0035);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0036);
	LCD_WR_DATA(0x00AF);
	LCD_WR_REG(0x0037);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0038);
	LCD_WR_DATA(0x00DB);
	LCD_WR_REG(0x0039);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0050);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0051);
	LCD_WR_DATA(0x0705);
	LCD_WR_REG(0x0052);
	LCD_WR_DATA(0x0C0A);
	LCD_WR_REG(0x0053);
	LCD_WR_DATA(0x0401);
	LCD_WR_REG(0x0054);
	LCD_WR_DATA(0x040C);
	LCD_WR_REG(0x0055);
	LCD_WR_DATA(0x0608);
	LCD_WR_REG(0x0056);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0057);
	LCD_WR_DATA(0x0104);
	LCD_WR_REG(0x0058);
	LCD_WR_DATA(0x0E06);
	LCD_WR_REG(0x0059);
	LCD_WR_DATA(0x060E);
	LCD_WR_REG(0x0020);
	LCD_WR_DATA(0x0000);
	LCD_WR_REG(0x0021);
	LCD_WR_DATA(0x0000);
	
	LCD_WR_REG(0x0007);
	LCD_WR_DATA(0x1017);    //262k color display ON
	LCD_WR_REG(0x0022);
	delay_ms(20);
}

/*************************��ɫ����**********************************************/
void LCD_Clear()
{
	u8 i,j;
	LCD_WR_REG_DATA(0x36,0x00af);     //horizontal address  ˮƽ��ַ�߰�λ
	LCD_WR_REG_DATA(0x37,0x0000);	  //horizontal address  ˮƽ��ַ�Ͱ�λ
	LCD_WR_REG_DATA(0x38,0x00db);	  //vertical address    ��ֱ��ַ�߰�λ
	LCD_WR_REG_DATA(0x39,0x0000);     //vertical address    ��ֱ��ַ�߰�λ
	
	LCD_WR_REG_DATA(0x20,0x0000);    //GRAM address set   ���õ�ַ�������ĳ�ʼֵ    
	LCD_WR_REG_DATA(0x21,0x0000);
	
	LCD_WR_REG(0x22);
	
	RS = 1;  //д����
	CS = 0;
	for (i = 0; i < 220; i++) 
	{
		if(i<73)
		 {
			for(j=0;j<176;j++)
			 {
				LCD_WR_DATA(red); 
			 }
		 }
		 else if(i<146)
		 {
			 for(j=0;j<176;j++)
			 {
				 LCD_WR_DATA(blue);
			 }
		 }
		 else
		 {
			 for(j=0;j<176;j++)
			 {
				 LCD_WR_DATA(green);
			 }
		 }
			
	}
	
}
