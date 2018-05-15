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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
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
