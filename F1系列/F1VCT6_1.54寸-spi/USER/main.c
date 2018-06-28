#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "spi.h"

int main(void)
{
	u16 i=0,j=0;
	delay_init();	    //延时函数初始化
	LCD_GPIO_Init();
	SPI2_Init();
	
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();

	LCD_Init(); //要初始化两次
	LCD_Init();
	
	
	display_test(BLACK); //显示测试函数

	

	while(1)
	{
		//红色
		display_test(RED);
		delay_ms(300);
		//绿色
		display_test(GREEN);
		delay_ms(300);
		//蓝色
		display_test(BLUE);
		delay_ms(300);
	}
}