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
	 u16 i,j;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
#if FSMC_Enable	 
	LCD_Init();
#else
#endif
	LCD_GPIO_Init();
	Lcd_Initialize_61509();
//	LCD_Clear_5420();
	 
	 
	LCD_WR_REG(0x0202);
	 
  	while(1) 
	{		 
		//��ɫ
		for (i = 0; i < 240; i++)
		{
			for (j = 0; j < 400; j++)
			{
				LCD_WR_DATA(BLACK);
			}
		}
		delay_ms(500);
		for (i = 0; i < 240; i++)
		{
			for (j = 0; j < 400; j++)
			{
				LCD_WR_DATA(WHITE);
			}
		}
		delay_ms(500);
		for (i = 0; i < 240; i++)
		{
			for (j = 0; j < 400; j++)
			{
				LCD_WR_DATA(RED);
			}
		}
		delay_ms(500);
		for (i = 0; i < 240; i++)
		{
			for (j = 0; j < 400; j++)
			{
				LCD_WR_DATA(GREEN);
			}
		}
		delay_ms(500);
		for (i = 0; i < 240; i++)
		{
			for (j = 0; j < 400; j++)
			{
				LCD_WR_DATA(BLUE);
			}
		}
		delay_ms(500);

	} 
}
