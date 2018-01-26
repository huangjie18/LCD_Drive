#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"
#include "time.h"
//*****************************************************
//ע�⣺9225���ÿ����Ĵ�����ͬ������Ҫ����GRAM����ʼ��ַ
//*****************************************************
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
}

 int main(void)
 {	
	u8 i=0,x=0,y=0;
	delay_init();	    //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();  //LED�Ƴ�ʼ��
	LCD_Init();	 //LCD��ʼ��
	KEY_Init();  //������ʼ��
	LCD_Clear();         //��ɫ��ʾ
//	LCD_Clear_black();  //ȫ����ɫ
	EXTIX_Init();
	TIM3_Int_Init(49999,719);//1M�ļ���Ƶ�ʣ���һ����Ϊ10us
	while(1)
	{
		if(irflag)
		{
			irflag = 0;
			LED0=!LED0;
			LED1=!LED1;
		}
		
	}
 }


