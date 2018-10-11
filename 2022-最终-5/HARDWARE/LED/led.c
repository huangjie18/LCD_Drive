#include "led.h"

	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
		
////////////////////////////////////////////////////////////////////////
	GPIO_InitTypeDef  GPIO_InitStructure;
 	//��ΪPB3���������ţ�������Ҫ��ӳ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_3;				 //LED0-->PB.3 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//��������ʼ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12
	|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
//	LED0 = 1;

}
 
/**************************ȫ����************************************/

void LED_Def(void)
{
	char i,j;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		SCK = 0;
		RCK = 0;
		for(i=0;i<8;i++)
		{
			SEG = 0;  //��λ����λ
			SCK = 1;  //SCK�����ؾͰ����������595
	//		delay_us(30);
			SCK = 0;
		}
		RCK = 1;     //RCK�����ؾͲ��������λ����λ
	//	delay_us(30);
		RCK = 0;
	}
}

/**************************ȫ����************************************/
void LED_bright(void)
{
	char i,j;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		SCK = 0;
		RCK = 0;
		for(i=0;i<8;i++)
		{
			SEG = 1;   //��λ����λ
			SCK = 1;   //SCK�����ؾͰ����������595
	//		delay_us(30);
			SCK = 0;
		}
		RCK = 1;      //RCK�����ؾͲ��������λ����λ
	//	delay_us(30);
		RCK = 0;
	}
}

//д�����ֽڣ������ŵĴ����ٶȴﵽ100Mʱ���д��󣬴�ʱ�õ���2M
void LED_bright_one(u8 *data_led)
{
	char a,j;
	u16 temp1;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		for(a=0;a<8;a++)
		{
			temp1 = (*data_led>>a)&0x01; //ȡ���Ӧָ������д
			if(temp1)
			{
				SEG = 1;   //��λ����λ
			}
			else
			{
				SEG = 0;   //��λ����λ
			}
			SCK = 1;   //SCK�����ؾͰ����������595
			SCK = 0;
		}
		data_led++;       //ָ���һ
//		RCK = 1;      //RCK�����ؾͲ��������λ����λ
//		RCK = 0;
	}
	RCK = 1;      //RCK�����ؾͲ��������λ����λ
//	delay_us(30);
	RCK = 0;

}