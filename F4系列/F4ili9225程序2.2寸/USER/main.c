#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"



int main(void)
{ 
	delay_init(168);    //��ʼ����ʱ����
 	LCD_Init();         //��ʼ��LCD�ӿ�
	LCD_Clear(); 	    //��ʾ��ɫ����
	while(1)
	{ 
	}
}



