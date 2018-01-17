/**
  *********************************  STM32F0xx  ********************************
  * @文件名     ： mic_page2.h
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 
  ******************************************************************************/
  
/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __MIC_PAGE2_1_H
#define __MIC_PAGE2_1_H
/* 包含的头文件 --------------------------------------------------------------*/
#include "sys.h"

/* 结构体定义   --------------------------------------------------------------*/

typedef struct 
{
	u8 mic_state_1;    //界面1状态
	u8 mic_state_2;    //界面2状态
}MIC_STATE;
//界面1可能存在的状态
enum
{
	Reverb_flag,       //混响是否选中标志
	Equili_flag,       //均衡是否选中标志
	Echo_flag,         //回声是否选中标志
	Frequenc_flag,     //移频是否选中标志
	DR_flag,           //动态范围
	Noise_flag,        //噪声门阀值
	Input_flag,        //输入高通滤波器
};

//界面2可能存在的状态
enum
{
	Dry_flag,         //干声
	Wet_flag,         //湿声
	Echo_time_flag,   //回声延时
	Echo_Gain_flag,   //回声增益
	Reverb_Time_flag, //混响时间
	HightorLow_flag,  //高低切
	PerGain_flag,     //PerGain
	Thershold_flag,   //Threshold
	Ratio_flag,       //Ratio
	Attack_flag,      //Attack
	Release_flag,     //Release
	FS_value_flag,    //移频值
	FS_switch_flag,   //移频开关
	Seg1_flag,        //Seg1
	Seg2_flag,        //Seg2
	Seg3_flag,        //Seg3
	Seg4_flag,        //Seg4
	Seg5_flag,        //Seg5
	Seg6_flag,        //Seg6
	Seg7_flag,        //Seg7
	Seg8_flag,        //Seg8
	Seg9_flag,        //Seg9
	ADelay_A_flag,    //预延时A
	MDelay_A_flag,    //主延时A
	FValue_A_flag,    //反馈值A
	Vout_A_flag,      //输出音量A
	Filter_A_flag,    //滤波器A
	ADelay_B_flag,    //预延时B
	MDelay_B_flag,    //主延时B
	FValue_B_flag,    //反馈值B
	Vout_B_flag,      //输出音量B
	Filter_B_flag,    //滤波器B
	NOPP,             //空
};

extern u8 Choose_place;     //选条位置
extern MIC_STATE mic_state;
/* 函数定义  ---- ------------------------------------------------------------*/
/* 混响系列     --------------------------------------------------------------*/
void Dry_voice(u16 x,u16 y,uint16 bk);
void Wet_voice(u16 x,u16 y,uint16 bk);
void Echo_time_delay(u16 x,u16 y,uint16 bk);
void Echo_Gain(u16 x,u16 y,uint16 bk);
void Reverb_Time(u16 x,u16 y,uint16 bk);
void HightorLow_Cut(u16 x,u16 y,uint16 bk);

/* 回声系列 -----------------------------------------------------------------*/
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

/* 均衡系列 -----------------------------------------------------------------*/
void Seg1_Show(u16 x,u16 y,uint16 bk);
void Seg2_Show(u16 x,u16 y,uint16 bk);
void Seg3_Show(u16 x,u16 y,uint16 bk);
void Seg4_Show(u16 x,u16 y,uint16 bk);
void Seg5_Show(u16 x,u16 y,uint16 bk);
void Seg6_Show(u16 x,u16 y,uint16 bk);
void Seg7_Show(u16 x,u16 y,uint16 bk);
void Seg8_Show(u16 x,u16 y,uint16 bk);
void Seg9_Show(u16 x,u16 y,uint16 bk);

/* 移频系列 -----------------------------------------------------------------*/
void Frequency_shift_value(u16 x,u16 y,uint16 bk);
void Frequency_shift_switch(u16 x,u16 y,uint16 bk);

/* 动态范围压缩系列 ---------------------------------------------------------*/
void PreGain_Show(u16 x,u16 y,uint16 bk);
void Shold_Show(u16 x,u16 y,uint16 bk);
void Ratio_Show(u16 x,u16 y,uint16 bk);
void Attack_Show(u16 x,u16 y,uint16 bk);
void Release_Show(u16 x,u16 y,uint16 bk);

/* 界面显示  ----------------------------------------------------------------*/
void MIC_Reverb_page2(void);        //混响子界面
void MIC_Echo_page2(void);          //回声子界面
void MIC_Equili_page2(void);        //均衡子界面
void MIC_Frequenc_page2(void);      //移频子界面
void MIC_DR_page2(void);            //动态范围子界面
void Echo_Volume(void);             //回声音量          
#endif  /* _REVERB_H */
/**** Copyright (C)2016 Huang. All Rights Reserved **** END OF FILE ****/
