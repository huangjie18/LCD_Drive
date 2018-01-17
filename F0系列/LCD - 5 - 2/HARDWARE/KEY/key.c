/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� key.c
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� ������ - ����ɨ��
                   �õ�ÿ�������ļ�ֵ
  ******************************************************************************/


/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "key.h"

u8 g_key_value[3][2]=
{
	1,  2,
	3,  4,
	5,  6,
};
/************************************************
�������� �� KEY_Init
��    �� �� �԰�����Ӧ���ų�ʼ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void KEY_Init(void)
{
	/////////////////��������Ҫ����ODR�Ĵ���////////////////////////////
/////////////////////����ģ�����������//////////////////////////////////////
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC->AHBENR |= 1<<17;//����GPIOAʱ��
	RCC->AHBENR |= 1<<18;//����GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                     //PA15����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                   //���ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PB����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_7;         //PB3��4��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIOB
	
	//��Դ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��PA10
	
}

/************************************************
�������� �� KEY_Scan
��    �� �� ����ɨ��
��    �� �� ��
�� �� ֵ �� ����ֵ
*************************************************/

u8 KEY_Scan(void)
{
	u8 scan_num=0; //ɨ�����
	key5_Set;      //PB5=1
	key4_Set;      //PB6=1
	
	for(scan_num=0;scan_num<3;scan_num++)
	{
		switch(scan_num)
		{
			case 0: key4_Reset; key5_Set; break;
			case 1: key5_Reset; key4_Set; break;
			default: break;
		}
		
		if((!key1)||(!key2)||(!key3))   //�а�������
		{
			if(!key1)
			{
				return g_key_value[0][scan_num];   //���ؼ�ֵ
			}
			else if(!key2)
			{
				return g_key_value[1][scan_num];
			}
			else if(!key3)
			{
				return g_key_value[2][scan_num];
			}
		} //end of if
		
	} //end of for
	
	return 0;  //����û���¾ͷ���0
}
