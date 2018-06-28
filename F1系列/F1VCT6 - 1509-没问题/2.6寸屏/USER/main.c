#include "sys.h"
#include "delay.h"
#include "led.h"


int main(void)
{
	delay_init();	    //延时函数初始化
	LCD_GPIO_Init();
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	
	//IC4551
	Lcd_Initialize_1509();
	LCD_Clear_1509();
	
	while(1)
	{
	}
}