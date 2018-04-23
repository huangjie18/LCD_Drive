#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //延时函数初始化
	LCD_GPIO_Init();
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	LCD_Init(); //要初始化两次
	LCD_Init();
	
	
	display_test(); //显示测试函数

	

	while(1)
	{
	}
}