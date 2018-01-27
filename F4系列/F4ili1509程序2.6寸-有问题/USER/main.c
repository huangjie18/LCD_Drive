#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

void STM32_Clock_Init(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ);
 int main(void)
 {	
//	STM32_Clock_Init(168,4,2,4);
	delay_init(10);	    //延时函数初始化	
	LCD_Init();	
	LCD_Clear();         //三色显示
  //全屏黑色
	while(1)
	{
		
	}
 }

u8 Sys_Clock_Set(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ) 
{
	u16 retry=0;
	u8 status=0;
	RCC->CR|=1<<16;				//HSE 开启 
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//等待HSE RDY
	if(retry==0X1FFF)status=1;	//HSE无法就绪
	else   
	{
		RCC->APB1ENR|=1<<28;	//电源接口时钟使能
		PWR->CR|=3<<14; 		//高性能模式,时钟可到168Mhz
		RCC->CFGR|=(16<<4)|(5<<10)|(4<<13);//HCLK 不分频;APB1 4分频;APB2 2分频. 
		RCC->CR&=~(1<<24);	//关闭主PLL
		RCC->PLLCFGR=PLLM|(PLLN<<6)|(((PLLP>>1)-1)<<16)|(PLLQ<<24)|(1<<22);//配置主PLL,PLL时钟源来自HSE
		RCC->CR|=1<<24;			//打开主PLL
		while((RCC->CR&(1<<25))==0);//等待PLL准备好 
		FLASH->ACR|=1<<8;		//指令预取使能.
		FLASH->ACR|=1<<9;		//指令cache使能.
		FLASH->ACR|=1<<10;		//数据cache使能.
		FLASH->ACR|=5<<0;		//5个CPU等待周期. 
		RCC->CFGR&=~(3<<0);		//清零
		RCC->CFGR|=2<<0;		//选择主PLL作为系统时钟	 
		while((RCC->CFGR&(3<<2))!=(2<<2));//等待主PLL作为系统时钟成功. 
	} 
	return status;
}
void STM32_Clock_Init(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ)
{
	RCC->CR|=0x00000001;		//设置HISON,开启内部高速RC振荡
	RCC->CFGR=0x00000000;		//CFGR清零 
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON清零 
	RCC->PLLCFGR=0x24003010;	//PLLCFGR恢复复位值 
	RCC->CR&=~(1<<18);			//HSEBYP清零,外部晶振不旁路
	RCC->CIR=0x00000000;		//禁止RCC时钟中断 
	Sys_Clock_Set(PLLN,PLLM,PLLP,PLLQ);//设置时钟 
}