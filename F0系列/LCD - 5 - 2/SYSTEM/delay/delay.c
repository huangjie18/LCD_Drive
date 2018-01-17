#include "delay.h"
#include "sys.h"
/***********************************************************************
�ο���C:\Users\Administrator\Desktop\STM32F030\����\TEST_STM32F0xx�ĳ����޸�
************************************************************************/
////////////////////////////////////////////////////////////////////////////////// 	 
static int8_t  fac_us=0;//us?��������?3?��y
static int16_t fac_ms=0;//ms?��������?3?��y


void delay_init(int8_t SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2????,????��a2?����?��  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// �δ�ʱ������HCLK/8������һ�μ�ʱ��1/6M��
	fac_us=SYSCLK/8;	//�������HCLK/8,fac_us=6  
	fac_ms=(int16_t)fac_us*1000;
}								    

//void delay_ms(int16_t nms)
//{	 		  	  
//	int32_t temp;		   
//	SysTick->LOAD=(int32_t)nms*fac_ms;//����???��??(SysTick->LOAD?a24bit)
//	SysTick->VAL =0x00;           //??????��y?��
//	SysTick->CTRL=0x01 ;          //?a��?��1��y  
//	do
//	{
//		temp=SysTick->CTRL;
//	}
//	while(temp&0x01&&!(temp&(1<<16)));//�̨���y����??��?��?   
//	SysTick->CTRL=0x00;       //1?��???��y?��
//	SysTick->VAL =0X00;       //??????��y?��	  	    
//}   


//void delay_us(int32_t nus)
//{		
//	int32_t temp;	    	 
//	SysTick->LOAD=nus*fac_us; //����???��??	  		 
//	SysTick->VAL=0x00;        //??????��y?��
//	SysTick->CTRL=0x01 ;      //?a��?��1��y 	 
//	do
//	{
//		temp=SysTick->CTRL;
//	}
//	while(temp&0x01&&!(temp&(1<<16)));//�̨���y����??��?��?   
//	SysTick->CTRL=0x00;       //1?��???��y?��
//	SysTick->VAL =0X00;       //??????��y?��	 
//}





   
//��ʱnms 
//nms:0~65535,��ΪSysTick->LOADΪ24bit��������Ҫ���������㷨���������ֻ����ʱ541ms����
void delay_ms(int16_t nms)
{	 		  	  
  	u8 repeat=nms/540;						//������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
											//���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
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
	SysTick->LOAD=nus*fac_us; 				//ʱ����أ��������ʱ1us����ô���Ǽ���6�Σ�(1/6M)*6 ��=(1/1M)=1us 		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}

//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��168M������,nms<=798ms 
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ���� 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;     		  		//��ռ�����	  	    
}


































