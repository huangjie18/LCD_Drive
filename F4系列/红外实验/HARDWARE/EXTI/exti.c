#include "exti.h"
#include "delay.h"
u8 irflag = 0;  //红外接收标志，收到一帧正确数据后置1
unsigned char ircode[4];  //红外代码接收缓冲区
u16 count_ir=0;  //重复接收次数
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP==1)	 
	{
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY2==0)	  
	{				 
   LED0=!LED0; 
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0)	 
	{
		LED1=!LED1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY0==0)	 
	{				 
		LED0=!LED0;	
		LED1=!LED1;	
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}




//红外测试数据
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
//外部中断5-9服务程序
void EXTI9_5_IRQHandler(void)
{
//	delay_ms(100);
//	LED0=!LED0;	
//	LED1=!LED1;
//	EXTI_ClearITPendingBit(EXTI_Line8);
	unsigned char i; //字节数
	unsigned char j; //位数
	unsigned char byt; //接收的数据
	u16 time;
	time = GetLowTime();
	
	//接收引导码的9ms低电平
	if((time<850)||(time>950))
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		return;
	}
	//接收引导码的4.5ms高电平
	time = GetHighTime();
	if((time<400)||(time>500))
	{
		if((time>220)&&(time<230))  //重复码
		{
			irflag = 1; 
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
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
				EXTI_ClearITPendingBit(EXTI_Line8);
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
				EXTI_ClearITPendingBit(EXTI_Line8);
				return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;  //接收完毕后设置标志
	count_ir = 0; //对重复次数清零
	EXTI_ClearITPendingBit(EXTI_Line8);
}
