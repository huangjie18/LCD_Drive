/**
  *********************************  STM32F0xx  ********************************
  * @�ļ���     �� mic_page2.h
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� 
  ******************************************************************************/
  
/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __MIC_PAGE2_1_H
#define __MIC_PAGE2_1_H
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "sys.h"

/* �ṹ�嶨��   --------------------------------------------------------------*/

typedef struct 
{
	u8 mic_state_1;    //����1״̬
	u8 mic_state_2;    //����2״̬
}MIC_STATE;
//����1���ܴ��ڵ�״̬
enum
{
	Reverb_flag,       //�����Ƿ�ѡ�б�־
	Equili_flag,       //�����Ƿ�ѡ�б�־
	Echo_flag,         //�����Ƿ�ѡ�б�־
	Frequenc_flag,     //��Ƶ�Ƿ�ѡ�б�־
	DR_flag,           //��̬��Χ
	Noise_flag,        //�����ŷ�ֵ
	Input_flag,        //�����ͨ�˲���
};

//����2���ܴ��ڵ�״̬
enum
{
	Dry_flag,         //����
	Wet_flag,         //ʪ��
	Echo_time_flag,   //������ʱ
	Echo_Gain_flag,   //��������
	Reverb_Time_flag, //����ʱ��
	HightorLow_flag,  //�ߵ���
	PerGain_flag,     //PerGain
	Thershold_flag,   //Threshold
	Ratio_flag,       //Ratio
	Attack_flag,      //Attack
	Release_flag,     //Release
	FS_value_flag,    //��Ƶֵ
	FS_switch_flag,   //��Ƶ����
	Seg1_flag,        //Seg1
	Seg2_flag,        //Seg2
	Seg3_flag,        //Seg3
	Seg4_flag,        //Seg4
	Seg5_flag,        //Seg5
	Seg6_flag,        //Seg6
	Seg7_flag,        //Seg7
	Seg8_flag,        //Seg8
	Seg9_flag,        //Seg9
	ADelay_A_flag,    //Ԥ��ʱA
	MDelay_A_flag,    //����ʱA
	FValue_A_flag,    //����ֵA
	Vout_A_flag,      //�������A
	Filter_A_flag,    //�˲���A
	ADelay_B_flag,    //Ԥ��ʱB
	MDelay_B_flag,    //����ʱB
	FValue_B_flag,    //����ֵB
	Vout_B_flag,      //�������B
	Filter_B_flag,    //�˲���B
	NOPP,             //��
};

extern u8 Choose_place;     //ѡ��λ��
extern MIC_STATE mic_state;
/* ��������  ---- ------------------------------------------------------------*/
/* ����ϵ��     --------------------------------------------------------------*/
void Dry_voice(u16 x,u16 y,uint16 bk);
void Wet_voice(u16 x,u16 y,uint16 bk);
void Echo_time_delay(u16 x,u16 y,uint16 bk);
void Echo_Gain(u16 x,u16 y,uint16 bk);
void Reverb_Time(u16 x,u16 y,uint16 bk);
void HightorLow_Cut(u16 x,u16 y,uint16 bk);

/* ����ϵ�� -----------------------------------------------------------------*/
void Advance_Delay_A(u16 x,u16 y,uint16 bk);
void Main_Delay_A(u16 x,u16 y,uint16 bk);
void Feedback_Value_A(u16 x,u16 y,uint16 bk);
void Volume_Out_A(u16 x,u16 y,uint16 bk);
void Filter_A(u16 x,u16 y,uint16 bk);
void Advance_Delay_B(u16 x,u16 y,uint16 bk);
void Main_Delay_B(u16 x,u16 y,uint16 bk);
void Feedback_Value_B(u16 x,u16 y,uint16 bk);
void Volume_Out_B(u16 x,u16 y,uint16 bk);
void Filter_B(u16 x,u16 y,uint16 bk);

/* ����ϵ�� -----------------------------------------------------------------*/
void Seg1_Show(u16 x,u16 y,uint16 bk);
void Seg2_Show(u16 x,u16 y,uint16 bk);
void Seg3_Show(u16 x,u16 y,uint16 bk);
void Seg4_Show(u16 x,u16 y,uint16 bk);
void Seg5_Show(u16 x,u16 y,uint16 bk);
void Seg6_Show(u16 x,u16 y,uint16 bk);
void Seg7_Show(u16 x,u16 y,uint16 bk);
void Seg8_Show(u16 x,u16 y,uint16 bk);
void Seg9_Show(u16 x,u16 y,uint16 bk);

/* ��Ƶϵ�� -----------------------------------------------------------------*/
void Frequency_shift_value(u16 x,u16 y,uint16 bk);
void Frequency_shift_switch(u16 x,u16 y,uint16 bk);

/* ��̬��Χѹ��ϵ�� ---------------------------------------------------------*/
void PreGain_Show(u16 x,u16 y,uint16 bk);
void Shold_Show(u16 x,u16 y,uint16 bk);
void Ratio_Show(u16 x,u16 y,uint16 bk);
void Attack_Show(u16 x,u16 y,uint16 bk);
void Release_Show(u16 x,u16 y,uint16 bk);

/* ������ʾ  ----------------------------------------------------------------*/
void MIC_Reverb_page2(void);        //�����ӽ���
void MIC_Echo_page2(void);          //�����ӽ���
void MIC_Equili_page2(void);        //�����ӽ���
void MIC_Frequenc_page2(void);      //��Ƶ�ӽ���
void MIC_DR_page2(void);            //��̬��Χ�ӽ���
void Echo_Volume(void);             //��������          
#endif  /* _REVERB_H */
/**** Copyright (C)2016 Huang. All Rights Reserved **** END OF FILE ****/
