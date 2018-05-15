#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //延时函数初始化
	LCD_GPIO_Init_1();

	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	LCD_Init_1(); //要初始化两次
	LCD_Init_1();
	
	
	
	display_test_1(); //显示测试函数

	

	while(1)
	{
	}
}