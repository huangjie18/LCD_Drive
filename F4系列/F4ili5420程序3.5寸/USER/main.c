#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //延时函数初始化	
	
	LCD_Init(5420);	       //初始化IC9326
//	LCD_Read();
	LCD_Clear(5420);         //三色显示

	while(1)
	{
		
	}
 }


