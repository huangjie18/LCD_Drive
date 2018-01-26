#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "INIT.h"
#include "exti.h"

int main(void)
{ 
	delay_init(168);		  //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();		        //��ʼ��LED�˿�
	KEY_Init();  //������ʼ��
	EXTIX_Init();
	TIM3_Int_Init(49999,840-1);//1/10M�ļ���Ƶ�ʣ���һ����Ϊ10us
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





