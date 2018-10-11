#include "led.h"

	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
		
////////////////////////////////////////////////////////////////////////
	GPIO_InitTypeDef  GPIO_InitStructure;
 	//因为PB3是特殊引脚，所以需要重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_3;				 //LED0-->PB.3 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//编码器初始化
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12
	|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
//	LED0 = 1;

}
 
/**************************全灯灭************************************/

void LED_Def(void)
{
	char i,j;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		SCK = 0;
		RCK = 0;
		for(i=0;i<8;i++)
		{
			SEG = 0;  //八位数据位
			SCK = 1;  //SCK上升沿就把数据锁存进595
	//		delay_us(30);
			SCK = 0;
		}
		RCK = 1;     //RCK上升沿就并口输出八位数据位
	//	delay_us(30);
		RCK = 0;
	}
}

/**************************全灯亮************************************/
void LED_bright(void)
{
	char i,j;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		SCK = 0;
		RCK = 0;
		for(i=0;i<8;i++)
		{
			SEG = 1;   //八位数据位
			SCK = 1;   //SCK上升沿就把数据锁存进595
	//		delay_us(30);
			SCK = 0;
		}
		RCK = 1;      //RCK上升沿就并口输出八位数据位
	//	delay_us(30);
		RCK = 0;
	}
}

//写单个字节，当引脚的传输速度达到100M时会有错误，此时用的是2M
void LED_bright_one(u8 *data_led)
{
	char a,j;
	u16 temp1;
	SCK = 0;
	RCK = 0;
	for(j=0;j<10;j++)
	{
		for(a=0;a<8;a++)
		{
			temp1 = (*data_led>>a)&0x01; //取相对应指针数据写
			if(temp1)
			{
				SEG = 1;   //八位数据位
			}
			else
			{
				SEG = 0;   //八位数据位
			}
			SCK = 1;   //SCK上升沿就把数据锁存进595
			SCK = 0;
		}
		data_led++;       //指针加一
//		RCK = 1;      //RCK上升沿就并口输出八位数据位
//		RCK = 0;
	}
	RCK = 1;      //RCK上升沿就并口输出八位数据位
//	delay_us(30);
	RCK = 0;

}