#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


 int main(void)
 {	
	u8 i=0,x=0,y=0;
	delay_init(168);	    //��ʱ������ʼ��	
	
	LCD_Init();	
	 
	LCD_Clear();         //��ɫ��ʾ
  //ȫ����ɫ
//	for(i=0;i<20;i++)
//	{	 
//	 showchar(x,y,33+i);
//		x+=8;
//	}
	while(1)
	{
		
	}
 }


