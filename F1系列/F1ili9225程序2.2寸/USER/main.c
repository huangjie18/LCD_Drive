#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

//*****************************************************
//ע�⣺9225���ÿ����Ĵ�����ͬ������Ҫ����GRAM����ʼ��ַ
//*****************************************************



 int main(void)
 {	
	 int j;
	int i=0,x=0,y=204;
	delay_init();	    //��ʱ������ʼ��	
	
	LCD_Init();	
	 
	LCD_Clear();
	for(i=0;i<22;i++)
	 {
		 showchar(x,y,i+33);
		 x = x+8;
		 delay_ms(3);
	 }
	while(1)
	{
		
	}
 }


