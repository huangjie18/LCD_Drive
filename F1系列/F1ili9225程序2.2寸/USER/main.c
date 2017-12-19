#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

//*****************************************************
//注意：9225设置开区寄存器不同，并且要设置GRAM的起始地址
//*****************************************************



 int main(void)
 {	
	 int j;
	int i=0,x=0,y=204;
	delay_init();	    //延时函数初始化	
	
	LCD_Init();	
	 
	LCD_Clear();
	for(i=0;i<22;i++)
	 {
		 showchar(x,y,i+33);
		 x = x+8;
		 delay_ms(3);
	 }
	while(1)
	{
		
	}
 }


