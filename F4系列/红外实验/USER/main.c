#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "INIT.h"
#include "exti.h"

int main(void)
{ 
	delay_init(168);		  //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();		        //初始化LED端口
	KEY_Init();  //按键初始化
	EXTIX_Init();
	TIM3_Int_Init(49999,840-1);//1/10M的计数频率，计一次数为10us
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





