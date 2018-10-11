#include "key.h"
#include "delay.h"

u8 anjian[10][10] =
{
	{0,   0,   0,   0,   0,   0,   0,   0,   0,   0, },
	{0,   1,   2,   3,   4,   5,   6,   7,   8,   9, }, //key1�а���
	{0,   27,  28,  29,  30,  31,  32,  33,  34,  35,}, //key2�а���
	{0,   53,  54,  55,  56,  57,  58,  59,  60,  61, }, //key3�а���
	{0,   10,  11,  12,  13,  14,  15,  16,  17,  18, }, //key4�а���
	{0,   36,  37,  38,  39,  40,  41,  42,  43,  44, }, //key5�а���
	{0,   62,  63,  64,  65,  66,  67,  68,  69,  70, }, //key6�а���
	{0,   19,  20,  21,  22,  23,  24,  25,  26,  80, }, //key7�а���
	{0,   45,  46,  47,  48,  49,  50,  51,  52,  79, }, //key8�а���
	{0,   71,  72,  73,  74,  75,  76,  77,  78,   0, }, //key9�а���
};

void KEY_Init(void)
{
 ///////////////////////////////key1-key9����Ϊ����////////////////////////////////////

	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
	|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//KEY1-KEY9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	
	PWR_BackupAccessCmd(ENABLE);//�����޸�RTC �ͺ󱸼Ĵ���
	RCC_LSEConfig(RCC_LSE_OFF);//�ر��ⲿ�����ⲿʱ���źŹ��� ��PC13 PC14 PC15 �ſ��Ե���ͨIO�á�
	PWR_BackupAccessCmd(DISABLE);//�������޸�RTC �ͺ󱸼Ĵ���
	////////////////////////////key10-key18����Ϊ���///////////////////////////////////////////////
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.3 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
	|GPIO_Pin_5;				 //LED0-->PB.3 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
		key10 = 1;
		key11 = 1;
		key12 = 1;
		key13 = 1;
		key14 = 1;
		key15 = 1;
		key16 = 1;
		key17 = 1;
		key18 = 1;
}

u8 KEY_Scan(void)
{
	u8 i,j;
	static u8 key_up = 1;
	
	if(key_up)
	{
		key10 = 1;
		key11 = 1;
		key12 = 1;
		key13 = 1;
		key14 = 1;
		key15 = 1;
		key16 = 1;
		key17 = 1;
		key18 = 1;
		delay_ms(1); 
		for(j=1;j<11;j++)
		{
			switch(j)
			{
				case 1: key10 = 0; key18 = 1; break; //����key10ɨ�裬�ر�key16ɨ��
				case 2: key11 = 0; key10 = 1; break;
				case 3: key12 = 0; key11 = 1; break;
				case 4: key13 = 0; key12 = 1; break;
				case 5: key14 = 0; key13 = 1; break;
				case 6: key15 = 0; key14 = 1; break;
				case 7: key16 = 0; key15 = 1; break;
				case 8: key17 = 0; key16 = 1; break;
				case 9: key18 = 0; key17 = 1; break;
				default: key18 = 1; break;
			}
			if(key1==0||key2==0||key3==0||key4==0||key5==0||key6==0||key7==0||key8==0
				||key9==0)
			{
				key_up = 0;
				delay_ms(10);   //��������
				if(key1==0) {return anjian[1][j];} //���ض�Ӧ��ֵ
				else if(key2==0) {return anjian[2][j];} 
				else if(key3==0) {return anjian[3][j];}
				else if(key4==0) {return anjian[4][j];}
				else if(key5==0) {return anjian[5][j];}
				else if(key6==0) {return anjian[6][j];}
				else if(key7==0) {return anjian[7][j];}
				else if(key8==0) {return anjian[8][j];}
				else if(key9==0) {return anjian[9][j];}
				
				
			}
		}
	}
	else 
	{
		key10 = 0;  
		key11 = 0;
		key12 = 0;
		key13 = 0;
		key14 = 0;
		key15 = 0;
		key16 = 0;
		key17 = 0;
		key18 = 0;
		if(key1==1&&key2==1&&key3==1&&key4==1&&key5==1&&key6==1&&key7==1&&key8==1&&key9==1)key_up=1;
	}
	
	return 0;
}