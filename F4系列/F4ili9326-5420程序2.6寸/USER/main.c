#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init(9326);	       //��ʼ��IC9326
//	LCD_Read();
	LCD_Clear(9326);         //��ɫ��ʾ

	while(1)
	{
		
	}
 }


