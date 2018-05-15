#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"

 
/************************************************
��2.6�������DB13λ��DB15����Ҫ�Ի�

************************************************/
 	
 int main(void)
 {	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
#if FSMC_Enable	 
	LCD_Init();
#else
#endif
	LCD_GPIO_Init();
	Lcd_Initialize_5420();
	LCD_Clear_5420();
	 
  	while(1) 
	{		 


	} 
}
