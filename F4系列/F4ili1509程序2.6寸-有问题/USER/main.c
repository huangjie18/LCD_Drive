#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

void STM32_Clock_Init(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ);
 int main(void)
 {	
//	STM32_Clock_Init(168,4,2,4);
	delay_init(10);	    //��ʱ������ʼ��	
	LCD_Init();	
	LCD_Clear();         //��ɫ��ʾ
  //ȫ����ɫ
	while(1)
	{
		
	}
 }

u8 Sys_Clock_Set(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ) 
{
	u16 retry=0;
	u8 status=0;
	RCC->CR|=1<<16;				//HSE ���� 
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//�ȴ�HSE RDY
	if(retry==0X1FFF)status=1;	//HSE�޷�����
	else   
	{
		RCC->APB1ENR|=1<<28;	//��Դ�ӿ�ʱ��ʹ��
		PWR->CR|=3<<14; 		//������ģʽ,ʱ�ӿɵ�168Mhz
		RCC->CFGR|=(16<<4)|(5<<10)|(4<<13);//HCLK ����Ƶ;APB1 4��Ƶ;APB2 2��Ƶ. 
		RCC->CR&=~(1<<24);	//�ر���PLL
		RCC->PLLCFGR=PLLM|(PLLN<<6)|(((PLLP>>1)-1)<<16)|(PLLQ<<24)|(1<<22);//������PLL,PLLʱ��Դ����HSE
		RCC->CR|=1<<24;			//����PLL
		while((RCC->CR&(1<<25))==0);//�ȴ�PLL׼���� 
		FLASH->ACR|=1<<8;		//ָ��Ԥȡʹ��.
		FLASH->ACR|=1<<9;		//ָ��cacheʹ��.
		FLASH->ACR|=1<<10;		//����cacheʹ��.
		FLASH->ACR|=5<<0;		//5��CPU�ȴ�����. 
		RCC->CFGR&=~(3<<0);		//����
		RCC->CFGR|=2<<0;		//ѡ����PLL��Ϊϵͳʱ��	 
		while((RCC->CFGR&(3<<2))!=(2<<2));//�ȴ���PLL��Ϊϵͳʱ�ӳɹ�. 
	} 
	return status;
}
void STM32_Clock_Init(u32 PLLN,u32 PLLM,u32 PLLP,u32 PLLQ)
{
	RCC->CR|=0x00000001;		//����HISON,�����ڲ�����RC��
	RCC->CFGR=0x00000000;		//CFGR���� 
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON���� 
	RCC->PLLCFGR=0x24003010;	//PLLCFGR�ָ���λֵ 
	RCC->CR&=~(1<<18);			//HSEBYP����,�ⲿ������·
	RCC->CIR=0x00000000;		//��ֹRCCʱ���ж� 
	Sys_Clock_Set(PLLN,PLLM,PLLP,PLLQ);//����ʱ�� 
}