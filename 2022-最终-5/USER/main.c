#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "adc.h"
#include "control.h"
#include "dma.h"
#include "myiic.h"
#include "spiflash.h"
#include "dsp1.h"
#include "dsp2.h"

/*****************************************************************/
//F1系列的DMA传输完成后EN使能位不会自动清零；F4系列的会自动清零
/*****************************************************************/
//u8 HC595[10];

//键值对应的接收数据BUF小灯表,即是按下按键然后读取接受数据里的第几位
u8 Key_Led[]=
{
	 0, 4, 5, 6, 7, 8, 9,10,11,12, //9
	13,14,15,16,17,18,19,20,21,22, //19
	23,24,25,26,27,28,29,30,31,32, //29
	33,34,35,36,37,38,39,40,41,42, //39
	43,44,45,46,47,48,49,50,51,52, //49
	53,54,55,56,57,58,59,60,61,62, //59
	63,64,65,66,67,68,69,70,71,72, //69
	73,74,75,76,77,78,79,80,81,3,  //79
	2,
};

//按键状态
enum
{
	KEY_ONE,  //
	KEY_TWO,
};	 
u8 Key_State[85]={KEY_ONE}; //初始化按键状态值
//C0;1→22推子，0→21推子
u8 debug_value_1=0x00;
u8 debug_value_2=0x00;
u8 debug_value_3=0x00;
u8 debug_value_4=0x00;
u8 debug_value_5=0x00;
u8 debug_value_6=0x00;
u8 debug_value_7=0x00;
u8 KEY_STATE = KEY_ONE;  //是否反转

static void key_state_tration(u8 key_value,u8 key_sta);
static void check_usart(void);
int main(void)
{	
	u8 i;
	u16 adcx;
	u8 key_last = 0;
	u32 time_out=1;
	
	delay_init();	    //延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//uart_init(230400);  //串口初始化
	uart_init(115200);  //串口初始化
	
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.
	LED_Def();       //全部灯亮
	 
	dac_iic_init();
	adc_reset=0;
	delay_ms(5);
	adc_reset=1;//主ad复位
	delay_ms(5);	

	dac_reset=0;
	delay_ms(5);
	dac_reset=1;//从ad和da复位
	delay_ms(5);

	write_dac_data0(0x30,0x02,0x80);	//取消低功耗
	write_dac_data0(0x30,0x03,0xc3);	//TDM，一倍频---48KHZ
	write_dac_data0(0x32,0x02,0x80);	//取消低功耗
	write_dac_data0(0x32,0x03,0xc3);		//TDM，一倍频---48KHZ
	debug_value_4=read_dac_data0(0x32,0x03);		 
	SPI_DSP_CODE_Init();	
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DelayUs(60000);
	DSP_Reset_Init();
	
	LED_Init();		  	//初始化与LED连接的硬件接口,编码器的引脚初始化也在这里
	Adc_Init();         //ADC初始化
	KEY_Init();         //按键初始化
	while(1)
	{
		//数据校验
		check_usart();
		
		//数据发送
		key_last = KEY_Scan();
		if(key_last)
		{
			USART_RX_BUF_STATE = USART_RX_BUF_LOCK;        //关公共资源
			USART_ITConfig(USART1,USART_IT_RXNE,DISABLE); //关串口中断
			KeyValue = key_last;
			key_state_tration(key_last,0);
			
			SendBuff_Init();  //初始化发送数据
			for(i=0;i<3;i++)  //发送三次数据，防止接收不到
			{
				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送
				MYDMA_Enable(DMA1_Channel4);
			}
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开串口中断
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;     //重新接受数据
			USART_RX_STA = 0;
			g_usart_curstate = USART_WAIT; //等待接受状态
			while((g_usart_curstate != USART_COMPLETE) && (time_out != 500000))
			{
				time_out++; //等待超时
			};    //等待接受一次数据完成
			time_out=0;
//			check_usart(); //数据校验
//			if(USART_jiaoyan)  //数据正确则处理
//			{
//				USART_Light(); //点灯程序
//				USART_jiaoyan = 0;
//				USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;
//				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开串口中断
//			}
		}
		else
		{
			SendBuff_Init();
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送
			MYDMA_Enable(DMA1_Channel4); 
		}
		
		//数据处理
		if(USART_jiaoyan)  //数据正确则处理
		{
			USART_Light(); //点灯程序
			USART_jiaoyan = 0;
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开串口中断
		}
	}
 }

/************************************************
函数名称 ： key_state_tration
功    能 ： 按键状态转换
参    数 ： 按键值，按键状态
返 回 值 ： 无
*************************************************/
static void key_state_tration(u8 key_value,u8 key_sta)
{

	if(key_value<=26)
	{
		//根据自定义数据判断翻转灯的状态
		if(Key_State[key_value]==KEY_ONE)
		{
			KEY_STATE = KEY_TWO;
			Key_State[key_value] = KEY_TWO;
		}
		else if(Key_State[key_value]==KEY_TWO)
		{
			KEY_STATE = KEY_ONE;
			Key_State[key_value] = KEY_ONE;
		}
	}
	else 
	{
		//根据灯的状态判断翻转灯的状态
		if(USART_RX_BUF[Key_Led[key_value]] == KEY_ONE)	
		{
			KEY_STATE = KEY_TWO;
		}
		else if(USART_RX_BUF[Key_Led[key_value]] == KEY_TWO)
		{
			KEY_STATE = KEY_ONE;
		}
	}
}
/************************************************
函数名称 ： check_usart
功    能 ： 接收数据校验
参    数 ： 无
返 回 值 ： 无
*************************************************/
static void check_usart(void)
{
	if(g_usart_curstate == USART_COMPLETE) //接收完成
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //关串口中断
		USART_RX_BUF_STATE = USART_RX_BUF_LOCK;  //信息池加锁
		check_sum = 0;
		for(check=0;check<(USART_REC_LEN-1);check++)
		{
			check_sum += USART_RX_BUF[check];
		}
		if(check_sum==USART_RX_BUF[USART_REC_LEN-1])
		{
			USART_jiaoyan = 1;  //数据正确，要等到处理完数据后才开串口中断
		}
		else
		{
			USART_jiaoyan = 0;  //数据不正确
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK; //信息池解锁
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开串口中断
		}
		USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK; //信息池解锁
		g_usart_curstate = USART_WAIT;  //等待状态,重新接收状态
	}
}

	


