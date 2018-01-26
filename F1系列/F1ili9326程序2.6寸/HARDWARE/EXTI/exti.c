#include "exti.h"
#include "led.h"
#include "delay.h"


u8 irflag = 0;  //������ձ�־���յ�һ֡��ȷ���ݺ���1
unsigned char ircode[4];  //���������ջ�����
static unsigned int GetLowTime(void);
static unsigned int GetHighTime(void);
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	//GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2|EXTI_Line4|EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//  	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//  	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	
	
	//�������ų�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED0-->PB.9 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(WK_UP==1)	 	 //WK_UP����
	{				 

	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	  //����KEY2
	{
		LED0=!LED0;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����KEY1
	{				 
		LED1=!LED1;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0)	 //����KEY0
	{
		LED0=!LED0;
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}

void EXTI9_5_IRQHandler(void)
{
//	delay_ms(100);
//	LED0=!LED0;
//	LED1=!LED1;
//	EXTI_ClearITPendingBit(EXTI_Line9);
	unsigned char i; //�ֽ���
	unsigned char j; //λ��
	unsigned char byt; //���յ�����
	u16 time;
	time = GetLowTime();
	
	//�����������9ms�͵�ƽ
	if((time<850)||(time>950))
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		return;
	}
	//�����������4.5ms�ߵ�ƽ
	time = GetHighTime();
	if((time<400)||(time>500))
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		return;
	}
	
	//���ղ��ж�������4�ֽ�����
	for(i=0;i<4;i++)  //ѭ������4���ֽ�
	{
		for(j=0;j<8;j++)  //ѭ�������ж�ÿ�ֽڵ�8��bit
		{
			time = GetLowTime();
			if((time<34)||(time>78))   //ʱ���ж���ΧΪ340��780us��
			{                          //�����˷�Χ��˵��Ϊ���룬ֱ���˳�
				EXTI_ClearITPendingBit(EXTI_Line9);
				return;
			}
			time = GetHighTime();
			if((time>34)&&(time<78))  //ʱ���ж���ΧΪ340��780us
			{                         //�ڴ˷�Χ��˵����bitֵΪ0
				byt >>= 1;//���λ���ȣ������������ƣ���λΪ0
			}
			else if((time>146)&&(time<190))  //ʱ���ж���ΧΪ1460��1900us��
			{                                //�ڴ˷�Χ��˵����bitֵΪ1
				byt >>= 1;
				byt |= 0x80;
			}
			else
			{
				EXTI_ClearITPendingBit(EXTI_Line9);
				return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;  //������Ϻ����ñ�־
	EXTI_ClearITPendingBit(EXTI_Line9);
}

static unsigned int GetLowTime(void)
{
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,ENABLE); //��ʼ����
	while(!IR_INPUT)
	{
		if(TIM3->CNT >= 2000)
		{
			break;
		}
	}
	TIM_Cmd(TIM3,DISABLE);  //ֹͣ����
	
	return(TIM3->CNT);
}

static unsigned int GetHighTime(void)
{
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,ENABLE); //��ʼ����
	while(IR_INPUT)
	{
		if(TIM3->CNT >= 2000)
		{
			break;
		}
	}
	TIM_Cmd(TIM3,DISABLE); //ֹͣ����
	return(TIM3->CNT);
}