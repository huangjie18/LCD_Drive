#include "sys.h"
#include "delay.h"
#include "led.h"


int main(void)
{
	delay_init();	    //��ʱ������ʼ��
	LCD_GPIO_Init();
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();
	
	//IC4551
	Lcd_Initialize_5420();
	LCD_Clear_5420();
	
	while(1)
	{
	}
}