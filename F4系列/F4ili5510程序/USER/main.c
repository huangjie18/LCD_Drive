#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

u16 LCD_D=0;
u16 LCD_B = 0;
int main(void)
{	

	delay_init(168);	    //延时函数初始化	
	GPIO_5510_Init();
	delay_ms(50);
	LCD_WR_REG_DATA(0X0000,0X0001);
	delay_ms(50);
	LCD_Read(0XDA00);
	LCD_D = LCD_Read(0XDB00);
	LCD_D <<= 8;
	LCD_D |= LCD_Read(0XDC00);

	while(1)
	{
		
	}
}


