#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //延时函数初始化	
	
	LCD_Init();	
	LCD_Read();
	LCD_Clear();         //三色显示

	while(1)
	{
		
	}
 }


