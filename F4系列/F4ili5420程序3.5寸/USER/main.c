#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init(5420);	       //��ʼ��IC9326
//	LCD_Read();
	LCD_Clear(5420);         //��ɫ��ʾ

	while(1)
	{
		
	}
 }


