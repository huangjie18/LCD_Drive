#include "exti.h"
#include "led.h"
#include "delay.h"


u8 irflag = 0;  //红外接收标志，收到一帧正确数据后置1
unsigned char ircode[4];  //红外代码接收缓冲区
static unsigned int GetLowTime(void);
static unsigned int GetHighTime(void);
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	//GPIOE.2 中断线以及中断初始化配置   下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2|EXTI_Line4|EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//  	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//  	EXTI_Init(&EXTI_InitStructure);
	
	//GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	
	
	//红外引脚初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED0-->PB.9 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	
}

//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(WK_UP==1)	 	 //WK_UP按键
	{				 

	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	  //按键KEY2
	{
		LED0=!LED0;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键KEY1
	{				 
		LED1=!LED1;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==0)	 //按键KEY0
	{
		LED0=!LED0;
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}

void EXTI9_5_IRQHandler(void)
{
//	delay_ms(100);
//	LED0=!LED0;
//	LED1=!LED1;
//	EXTI_ClearITPendingBit(EXTI_Line9);
	unsigned char i; //字节数
	unsigned char j; //位数
	unsigned char byt; //接收的数据
	u16 time;
	time = GetLowTime();
	
	//接收引导码的9ms低电平
	if((time<850)||(time>950))
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		return;
	}
	//接收引导码的4.5ms高电平
	time = GetHighTime();
	if((time<400)||(time>500))
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		return;
	}
	
	//接收并判定后续的4字节数据
	for(i=0;i<4;i++)  //循环接收4个字节
	{
		for(j=0;j<8;j++)  //循环接收判定每字节的8个bit
		{
			time = GetLowTime();
			if((time<34)||(time>78))   //时间判定范围为340～780us，
			{                          //超过此范围则说明为误码，直接退出
				EXTI_ClearITPendingBit(EXTI_Line9);
				return;
			}
			time = GetHighTime();
			if((time>34)&&(time<78))  //时间判定范围为340～780us
			{                         //在此范围内说明该bit值为0
				byt >>= 1;//因低位在先，所以数据右移，高位为0
			}
			else if((time>146)&&(time<190))  //时间判定范围为1460～1900us，
			{                                //在此范围内说明该bit值为1
				byt >>= 1;
				byt |= 0x80;
			}
			else
			{
				EXTI_ClearITPendingBit(EXTI_Line9);
				return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;  //接收完毕后设置标志
	EXTI_ClearITPendingBit(EXTI_Line9);
}

static unsigned int GetLowTime(void)
{
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,ENABLE); //开始计数
	while(!IR_INPUT)
	{
		if(TIM3->CNT >= 2000)
		{
			break;
		}
	}
	TIM_Cmd(TIM3,DISABLE);  //停止计数
	
	return(TIM3->CNT);
}

static unsigned int GetHighTime(void)
{
	TIM3->CNT = 0;
	TIM_Cmd(TIM3,ENABLE); //开始计数
	while(IR_INPUT)
	{
		if(TIM3->CNT >= 2000)
		{
			break;
		}
	}
	TIM_Cmd(TIM3,DISABLE); //停止计数
	return(TIM3->CNT);
}