#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init();	
#if (LCD_ID == 5420)
	RAM_address();
#endif
//	LCD_Clear();         //��ɫ��ʾ
  //ȫ����ɫ

	while(1)
	{
		
	}
 }


