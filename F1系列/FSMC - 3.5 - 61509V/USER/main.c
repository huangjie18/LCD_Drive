#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"

 
/************************************************
该2.6寸的屏中DB13位和DB15数据要对换

************************************************/
 	
 int main(void)
 {	 
	 u16 i,j;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
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
		//黑色
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
