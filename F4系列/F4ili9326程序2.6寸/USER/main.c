#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init();	
	LCD_Read();
	LCD_Clear();         //��ɫ��ʾ

	while(1)
	{
		
	}
 }


