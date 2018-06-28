#include "led.h"
#include "stdlib.h"
#include "delay.h"
u16 LCD_id = 0;
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



#if defined STM32F40_41xxx
    WR = 0;  //д����ʹ��,MCU����LCD��Ҫ����DB��������
    GPIOE->ODR = addr2;
    WR = 1;  //д����ʧ�ܣ�LCD��ʼ�������ߵ�����д���Լ����ڴ�
    CS = 1;

    CS = 0;  //��LCDʹ��
    WR = 1;


    WR = 0;
    GPIOE->ODR = addr3;
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

void LCD_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//���¶���һ���ṹ��

    //����ʱ���ߣ�stm32�У���Ƭ��û��
#ifdef STM32F40_41xxx   //�ж�оƬ����
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


#elif defined  STM32F10X_HD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
#endif
}

void LCD_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//���¶���һ���ṹ��

    //����ʱ���ߣ�stm32�У���Ƭ��û��
#ifdef STM32F40_41xxx   //�ж�оƬ����
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


#elif defined  STM32F10X_HD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //�ѽṹ��ĳ�Ա����������Ӧ�Ĵ���
#endif

}
/****************��ʼ������*******************/
void LCD_Init(u16 LCD_ID)
{

    GPIO_InitTypeDef GPIO_InitStructure;//���¶���һ���ṹ��

    //����ʱ���ߣ�stm32�У���Ƭ��û��
#ifdef STM32F40_41xxx   //�ж�оƬ����
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //�Խṹ��ı������г�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
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
    delay_ms(100);
    RST = 1;
    delay_ms(10);


    LCD_CS = 1;
    LCD_RD = 1;
    LCD_WR = 1;
    delay_ms(5);
    LCD_CS = 0; //��Ƭѡʹ��

    
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

/*************************��ɫ����**********************************************/
//9225������ģ���Ҫ�����
void LCD_Clear(u16 LCD_ID)
{
    u16 i, j;
    if(LCD_ID == 5420)
    {
        LCD_WR_REG_DATA(0x0210, 0x0000);    //X_Start); //x start
        LCD_WR_REG_DATA(0x0211, 0x00EF);    //X_End);       //x end
        LCD_WR_REG_DATA(0x0212, 0x0000);    //Y_Start); //y start
        LCD_WR_REG_DATA(0x0213, 0x018f);    //Y_End);       //y end
        LCD_WR_REG_DATA(0x0201, 0x0000);    //Y_Start); //y addres
        LCD_WR_REG_DATA(0x0200, 0x0000);    //X_Start); //x addres

        LCD_WR_REG(0x0202);

    }
    else if (LCD_ID == 9225)
    {
        LCD_WR_REG_DATA(0x36, 0x00af);    //horizontal address  ˮƽ��ַ�߰�λ
        LCD_WR_REG_DATA(0x37, 0x0000);    //horizontal address  ˮƽ��ַ�Ͱ�λ
        LCD_WR_REG_DATA(0x38, 0x00db);    //vertical address    ��ֱ��ַ�߰�λ
        LCD_WR_REG_DATA(0x39, 0x0000);    //vertical address    ��ֱ��ַ�߰�λ

        LCD_WR_REG_DATA(0x20, 0x0000);   //GRAM address set   ���õ�ַ�������ĳ�ʼֵ
        LCD_WR_REG_DATA(0x21, 0x0000);

        LCD_WR_REG(0x22);
    }
    RS = 1;  //д����
    CS = 0;
	//����
	for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(BLACK);
        }
    }
	

	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(BLUE);
        }
    }

	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(GREEN);
        }
    }
	
	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(0XF000);
        }
    }

}


void SLEEPEXIT(void)
{
    LCD_WR_REG_DATA(0x10, 0x0008);
    LCD_WR_REG_DATA(0x15, 0x7040);
    LCD_WR_REG_DATA(0x11, 0x0510);     //0x0110
    LCD_WR_REG_DATA(0x10, 0x3628);
    LCD_WR_REG_DATA(0x12, 0x0006);
    LCD_WR_REG_DATA(0x13, 0x0c2f);
    delay_ms(40);
    LCD_WR_REG_DATA(0x12, 0x0015); //0x0016
    delay_ms(40);
    LCD_WR_REG_DATA(0x10, 0x3640);  //0x3620  //0x3640
    LCD_WR_REG_DATA(0x13, 0x2b28);      //0x2D24  0x2C2f
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
    LCD_IN();  //��������Ϊ����
    RD = 0;
    delay_us(5);
    RD = 1;
    LCD_id = GPIOE->IDR;
    temp = LCD_id & 0xff00;
    RD = 0;
    LCD_id = GPIOE->IDR;
    RD = 1;
    temp |= (LCD_id >> 8);
    LCD_id = temp;
    LCD_OUT(); //��������Ϊ���
    CS = 1;
}