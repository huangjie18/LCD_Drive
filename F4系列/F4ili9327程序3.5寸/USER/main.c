#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init(9327);	       //��ʼ��IC9327
	LCD_Clear(9327);         //��ɫ��ʾ

	while(1)
	{
		
	}
 }


