#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	LCD_GPIO_Init();
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	LCD_Init(); //Ҫ��ʼ������
	LCD_Init();
	
	
	display_test(); //��ʾ���Ժ���

	

	while(1)
	{
	}
}