#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	LCD_GPIO_Init(); //1.3��
	LCD_GPIOInit_0(); //0.96��
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	
	//1.3����
	LCD_Init(); //Ҫ��ʼ������
	LCD_Init();
	display_test(); //��ʾ���Ժ���

	//����
//	LCD_Init_1();
//	LCD_Init_1();
//	display_test_1();
	
	
	//0.96����
//	LCD_Init_0();
//	display_rgb();
	
	while(1)
	{
	}
}