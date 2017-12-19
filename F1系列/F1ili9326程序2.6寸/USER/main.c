#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

//*****************************************************
//注意：9225设置开区寄存器不同，并且要设置GRAM的起始地址
//*****************************************************



 int main(void)
 {	
	u8 i=0,x=0,y=0;
	delay_init();	    //延时函数初始化	
	
	LCD_Init();	
	 
//	LCD_Clear();         //三色显示
	LCD_Clear_black();  //全屏黑色
//	for(i=0;i<20;i++)
//	{	 
//	 showchar(x,y,33+i);
//		x+=8;
//	}
	while(1)
	{
		
	}
 }


