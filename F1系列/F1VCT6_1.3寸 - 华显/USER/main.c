#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	LCD_GPIO_Init_1();

	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	LCD_Init_1(); //Ҫ��ʼ������
	LCD_Init_1();
	
	
	
	display_test_1(); //��ʾ���Ժ���

	

	while(1)
	{
	}
}