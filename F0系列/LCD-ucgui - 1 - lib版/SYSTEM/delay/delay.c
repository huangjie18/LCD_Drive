#include "delay.h"
#include "sys.h"
/***********************************************************************
参考：C:\Users\Administrator\Desktop\STM32F030\代码\TEST_STM32F0xx的程序修改
************************************************************************/
////////////////////////////////////////////////////////////////////////////////// 	 
static int8_t  fac_us=0;//us?óê±±?3?êy
static int16_t fac_ms=0;//ms?óê±±?3?êy


void delay_init(int8_t SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2????,????ía2?ê±?ó  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// 滴答定时器采用HCLK/8，即是一次计时是1/6M秒
	fac_us=SYSCLK/8;	//如果采用HCLK/8,fac_us=6  
	fac_ms=(int16_t)fac_us*1000;
}								    

//void delay_ms(int16_t nms)
//{	 		  	  
//	int32_t temp;		   
//	SysTick->LOAD=(int32_t)nms*fac_ms;//ê±???ó??(SysTick->LOAD?a24bit)
//	SysTick->VAL =0x00;           //??????êy?÷
//	SysTick->CTRL=0x01 ;          //?aê?μ1êy  
//	do
//	{
//		temp=SysTick->CTRL;
//	}
//	while(temp&0x01&&!(temp&(1<<16)));//μè′yê±??μ?′?   
//	SysTick->CTRL=0x00;       //1?±???êy?÷
//	SysTick->VAL =0X00;       //??????êy?÷	  	    
//}   


//void delay_us(int32_t nus)
//{		
//	int32_t temp;	    	 
//	SysTick->LOAD=nus*fac_us; //ê±???ó??	  		 
//	SysTick->VAL=0x00;        //??????êy?÷
//	SysTick->CTRL=0x01 ;      //?aê?μ1êy 	 
//	do
//	{
//		temp=SysTick->CTRL;
//	}
//	while(temp&0x01&&!(temp&(1<<16)));//μè′yê±??μ?′?   
//	SysTick->CTRL=0x00;       //1?±???êy?÷
//	SysTick->VAL =0X00;       //??????êy?÷	 
//}





   
//延时nms 
//nms:0~65535,因为SysTick->LOAD为24bit，所以需要采用这种算法，否则最大只能延时541ms左右
void delay_ms(int16_t nms)
{	 		  	  
  	u8 repeat=nms/540;						//这里用540,是考虑到某些客户可能超频使用,
											//比如超频到248M的时候,delay_xms最大只能延时541ms左右了
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 

void delay_us(int32_t nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载，如果是延时1us，那么就是计算6次，(1/6M)*6 秒=(1/1M)=1us 		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对168M条件下,nms<=798ms 
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
}


































