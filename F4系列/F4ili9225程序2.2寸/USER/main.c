#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"



int main(void)
{ 
	delay_init(168);    //初始化延时函数
 	LCD_Init();         //初始化LCD接口
	LCD_Clear(); 	    //显示三色界面
	while(1)
	{ 
	}
}



