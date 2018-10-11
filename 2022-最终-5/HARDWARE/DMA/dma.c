#include "dma.h"
#include "led.h"

u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 
u8 biaozhi=1;
u8 biaozhi1;

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{ 
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStruct;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
		DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
			
//		while((DMA_CHx->CCR&0x01)!= 0) {}	//等待DMA可配置
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
////////////////////////////////////////////////////////////////////////////////
	DMA_ITConfig(DMA_CHx,DMA_IT_TC,ENABLE);  //使能DMA完成中断
		
	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct); 
	
	DMA_Cmd(DMA_CHx, ENABLE);                      //开启DMA传输 

} 
//开启一次DMA传输
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:数据传输量  
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
 
//	DMA_Cmd(DMA_CHx, DISABLE);                      //关闭DMA传输,如果速度很快的话这句话不能要
	
//	while((DMA_CHx->CCR&0x01)!= 0) {}	//等待DMA可配置DMA才设置，EN硬件不置0，所以无效
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0){};  //不能用
	
//	while(DMA_GetCurrDataCounter(DMA_CHx)!=0){};  //可以用
	if(biaozhi)
	{
		biaozhi = 0;
		DMA_Cmd(DMA_CHx, DISABLE);  //F1必须要，F4自己会清零EN位，只有当EN为0时才能配置DMA
		DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
		DMA_Cmd(DMA_CHx, ENABLE);  //开启DMA传输 
	}		
}	  

void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
	{
//		LED0 = 1;
		biaozhi = 1;  //完成标志，表示可以关闭DMA进行下一次配置
		DMA_ClearITPendingBit(DMA1_IT_TC4);  //清除TCIF传输完成标志
	}
}



