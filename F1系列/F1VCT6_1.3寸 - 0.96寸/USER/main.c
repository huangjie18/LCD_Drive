#include "sys.h"
#include "delay.h"
#include "lcd.h"


int main(void)
{
	delay_init();	    //延时函数初始化
	LCD_GPIO_Init(); //1.3寸
	LCD_GPIOInit_0(); //0.96寸
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	
	//1.3寸屏
	LCD_Init(); //要初始化两次
	LCD_Init();
	display_test(); //显示测试函数

	//华显
//	LCD_Init_1();
//	LCD_Init_1();
//	display_test_1();
	
	
	//0.96寸屏
//	LCD_Init_0();
//	display_rgb();
	
	while(1)
	{
	}
}