#include "dma.h"
#include "led.h"

u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 
u8 biaozhi=1;
u8 biaozhi1;

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{ 
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStruct;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
		DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
			
//		while((DMA_CHx->CCR&0x01)!= 0) {}	//�ȴ�DMA������
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //����������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
////////////////////////////////////////////////////////////////////////////////
	DMA_ITConfig(DMA_CHx,DMA_IT_TC,ENABLE);  //ʹ��DMA����ж�
		
	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct); 
	
	DMA_Cmd(DMA_CHx, ENABLE);                      //����DMA���� 

} 
//����һ��DMA����
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ�����  
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
 
//	DMA_Cmd(DMA_CHx, DISABLE);                      //�ر�DMA����,����ٶȺܿ�Ļ���仰����Ҫ
	
//	while((DMA_CHx->CCR&0x01)!= 0) {}	//�ȴ�DMA������DMA�����ã�ENӲ������0��������Ч
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0){};  //������
	
//	while(DMA_GetCurrDataCounter(DMA_CHx)!=0){};  //������
	if(biaozhi)
	{
		biaozhi = 0;
		DMA_Cmd(DMA_CHx, DISABLE);  //F1����Ҫ��F4�Լ�������ENλ��ֻ�е�ENΪ0ʱ��������DMA
		DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
		DMA_Cmd(DMA_CHx, ENABLE);  //����DMA���� 
	}		
}	  

void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
	{
//		LED0 = 1;
		biaozhi = 1;  //��ɱ�־����ʾ���Թر�DMA������һ������
		DMA_ClearITPendingBit(DMA1_IT_TC4);  //���TCIF������ɱ�־
	}
}



