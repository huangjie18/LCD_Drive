#include "exti.h"
#include "delay.h"
u8 irflag = 0;  //������ձ�־���յ�һ֡��ȷ���ݺ���1
unsigned char ircode[4];  //���������ջ�����
u16 count_ir=0;  //�ظ����մ���
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
	if(WK_UP==1)	 
	{
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY2==0)	  
	{				 
   LED0=!LED0; 
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY1==0)	 
	{
		LED1=!LED1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY0==0)	 
	{				 
		LED0=!LED0;	
		LED1=!LED1;	
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}




//�����������
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
//�ⲿ�ж�5-9�������
void EXTI9_5_IRQHandler(void)
{
//	delay_ms(100);
//	LED0=!LED0;	
//	LED1=!LED1;
//	EXTI_ClearITPendingBit(EXTI_Line8);
	unsigned char i; //�ֽ���
	unsigned char j; //λ��
	unsigned char byt; //���յ�����
	u16 time;
	time = GetLowTime();
	
	//�����������9ms�͵�ƽ
	if((time<850)||(time>950))
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		return;
	}
	//�����������4.5ms�ߵ�ƽ
	time = GetHighTime();
	if((time<400)||(time>500))
	{
		if((time>220)&&(time<230))  //�ظ���
		{
			irflag = 1; 
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
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
				EXTI_ClearITPendingBit(EXTI_Line8);
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
				EXTI_ClearITPendingBit(EXTI_Line8);
				return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;  //������Ϻ����ñ�־
	count_ir = 0; //���ظ���������
	EXTI_ClearITPendingBit(EXTI_Line8);
}
