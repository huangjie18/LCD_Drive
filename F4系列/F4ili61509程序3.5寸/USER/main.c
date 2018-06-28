#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //延时函数初始化	
	
	LCD_Init(61509);	       //初始化IC9326
//	LCD_Read();
	LCD_Clear(5420);         //三色显示,红色有问题0xf800，但浅红色0xf000没问题

	while(1)
	{
		
	}
 }


