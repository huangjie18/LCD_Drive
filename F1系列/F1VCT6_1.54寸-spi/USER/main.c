#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "spi.h"

int main(void)
{
	u16 i=0,j=0;
	delay_init();	    //��ʱ������ʼ��
	LCD_GPIO_Init();
	SPI2_Init();
	
	
	//IC9326
//	Lcd_Initialize();
//	LCD_Clear();

	LCD_Init(); //Ҫ��ʼ������
	LCD_Init();
	
	
	display_test(BLACK); //��ʾ���Ժ���

	

	while(1)
	{
		//��ɫ
		display_test(RED);
		delay_ms(300);
		//��ɫ
		display_test(GREEN);
		delay_ms(300);
		//��ɫ
		display_test(BLUE);
		delay_ms(300);
	}
}