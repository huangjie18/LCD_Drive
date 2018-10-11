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
//F1ϵ�е�DMA������ɺ�ENʹ��λ�����Զ����㣻F4ϵ�еĻ��Զ�����
/*****************************************************************/
//u8 HC595[10];

//��ֵ��Ӧ�Ľ�������BUFС�Ʊ�,���ǰ��°���Ȼ���ȡ����������ĵڼ�λ
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

//����״̬
enum
{
	KEY_ONE,  //
	KEY_TWO,
};	 
u8 Key_State[85]={KEY_ONE}; //��ʼ������״ֵ̬
//C0;1��22���ӣ�0��21����
u8 debug_value_1=0x00;
u8 debug_value_2=0x00;
u8 debug_value_3=0x00;
u8 debug_value_4=0x00;
u8 debug_value_5=0x00;
u8 debug_value_6=0x00;
u8 debug_value_7=0x00;
u8 KEY_STATE = KEY_ONE;  //�Ƿ�ת

static void key_state_tration(u8 key_value,u8 key_sta);
static void check_usart(void);
int main(void)
{	
	u8 i;
	u16 adcx;
	u8 key_last = 0;
	u32 time_out=1;
	
	delay_init();	    //��ʱ������ʼ��	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//uart_init(230400);  //���ڳ�ʼ��
	uart_init(115200);  //���ڳ�ʼ��
	
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
	LED_Def();       //ȫ������
	 
	dac_iic_init();
	adc_reset=0;
	delay_ms(5);
	adc_reset=1;//��ad��λ
	delay_ms(5);	

	dac_reset=0;
	delay_ms(5);
	dac_reset=1;//��ad��da��λ
	delay_ms(5);

	write_dac_data0(0x30,0x02,0x80);	//ȡ���͹���
	write_dac_data0(0x30,0x03,0xc3);	//TDM��һ��Ƶ---48KHZ
	write_dac_data0(0x32,0x02,0x80);	//ȡ���͹���
	write_dac_data0(0x32,0x03,0xc3);		//TDM��һ��Ƶ---48KHZ
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
	
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�,�����������ų�ʼ��Ҳ������
	Adc_Init();         //ADC��ʼ��
	KEY_Init();         //������ʼ��
	while(1)
	{
		//����У��
		check_usart();
		
		//���ݷ���
		key_last = KEY_Scan();
		if(key_last)
		{
			USART_RX_BUF_STATE = USART_RX_BUF_LOCK;        //�ع�����Դ
			USART_ITConfig(USART1,USART_IT_RXNE,DISABLE); //�ش����ж�
			KeyValue = key_last;
			key_state_tration(key_last,0);
			
			SendBuff_Init();  //��ʼ����������
			for(i=0;i<3;i++)  //�����������ݣ���ֹ���ղ���
			{
				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����
				MYDMA_Enable(DMA1_Channel4);
			}
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�������ж�
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;     //���½�������
			USART_RX_STA = 0;
			g_usart_curstate = USART_WAIT; //�ȴ�����״̬
			while((g_usart_curstate != USART_COMPLETE) && (time_out != 500000))
			{
				time_out++; //�ȴ���ʱ
			};    //�ȴ�����һ���������
			time_out=0;
//			check_usart(); //����У��
//			if(USART_jiaoyan)  //������ȷ����
//			{
//				USART_Light(); //��Ƴ���
//				USART_jiaoyan = 0;
//				USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;
//				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //�������ж�
//			}
		}
		else
		{
			SendBuff_Init();
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����
			MYDMA_Enable(DMA1_Channel4); 
		}
		
		//���ݴ���
		if(USART_jiaoyan)  //������ȷ����
		{
			USART_Light(); //��Ƴ���
			USART_jiaoyan = 0;
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK;
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //�������ж�
		}
	}
 }

/************************************************
�������� �� key_state_tration
��    �� �� ����״̬ת��
��    �� �� ����ֵ������״̬
�� �� ֵ �� ��
*************************************************/
static void key_state_tration(u8 key_value,u8 key_sta)
{

	if(key_value<=26)
	{
		//�����Զ��������жϷ�ת�Ƶ�״̬
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
		//���ݵƵ�״̬�жϷ�ת�Ƶ�״̬
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
�������� �� check_usart
��    �� �� ��������У��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void check_usart(void)
{
	if(g_usart_curstate == USART_COMPLETE) //�������
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //�ش����ж�
		USART_RX_BUF_STATE = USART_RX_BUF_LOCK;  //��Ϣ�ؼ���
		check_sum = 0;
		for(check=0;check<(USART_REC_LEN-1);check++)
		{
			check_sum += USART_RX_BUF[check];
		}
		if(check_sum==USART_RX_BUF[USART_REC_LEN-1])
		{
			USART_jiaoyan = 1;  //������ȷ��Ҫ�ȵ����������ݺ�ſ������ж�
		}
		else
		{
			USART_jiaoyan = 0;  //���ݲ���ȷ
			USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK; //��Ϣ�ؽ���
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�������ж�
		}
		USART_RX_BUF_STATE = USART_RX_BUF_UNLOCK; //��Ϣ�ؽ���
		g_usart_curstate = USART_WAIT;  //�ȴ�״̬,���½���״̬
	}
}

	


