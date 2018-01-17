/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： mic_page2.c
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 第二页界面设计
                   
  ******************************************************************************/
  
/* 包含的头文件 --------------------------------------------------------------*/
#include "mic_page2_1.h"
#include "DISPLAY_TFT.h"
#include "lcd.h"
#include "mic_page2.h"

/* 变量定义  -----------------------------------------------------------------*/
MIC_STATE mic_state=
{
	Reverb_flag,
	0,
};

u8 Choose_place = 1;     //选条位置
/* 混响系列     --------------------------------------------------------------*/
/************************************************
函数名称 ： Dry_voice
功    能 ： 指定位置显示“干声音量”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Dry_voice(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,50,16,1);    //显示“干”
	LCD_ShowChar_CN(x+16,y,10,16,1); //显示“声”
	LCD_ShowChar_CN(x+32,y,48,16,1); //显示“音”
	LCD_ShowChar_CN(x+48,y,78,16,1); //显示“量”
}

/************************************************
函数名称 ： Wet_voice
功    能 ： 指定位置显示“湿声音量”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Wet_voice(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,52,16,1);    //显示“湿”
	LCD_ShowChar_CN(x+16,y,10,16,1); //显示“声”
	LCD_ShowChar_CN(x+32,y,48,16,1); //显示“音”
	LCD_ShowChar_CN(x+48,y,78,16,1); //显示“量”
}

/************************************************
函数名称 ： Echo_time_delay
功    能 ： 指定位置显示“回声延时”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Echo_time_delay(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,8,16,1);     //显示“回”
	LCD_ShowChar_CN(x+16,y,10,16,1); //显示“声”
	LCD_ShowChar_CN(x+32,y,54,16,1); //显示“延”
	LCD_ShowChar_CN(x+48,y,56,16,1); //显示“时”
}

/************************************************
函数名称 ： Echo_Gain
功    能 ： 指定位置显示“回声增益”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Echo_Gain(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,8,16,1);     //显示“回”
	LCD_ShowChar_CN(x+16,y,10,16,1); //显示“声”
	LCD_ShowChar_CN(x+32,y,58,16,1); //显示“增”
	LCD_ShowChar_CN(x+48,y,60,16,1); //显示“益”
}

/************************************************
函数名称 ： Reverb_Time
功    能 ： 指定位置显示“混响时间”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Reverb_Time(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,0,16,1);     //显示“混”
	LCD_ShowChar_CN(x+16,y,2,16,1);  //显示“响”
	LCD_ShowChar_CN(x+32,y,56,16,1); //显示“时”
	LCD_ShowChar_CN(x+48,y,62,16,1); //显示“间”
}

/************************************************
函数名称 ： HightorLow_Cut
功    能 ： 指定位置显示“高低切”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void HightorLow_Cut(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,20,16,1);     //显示“高”
	LCD_ShowChar_CN(x+16,y,64,16,1);  //显示“低”
	LCD_ShowChar_CN(x+32,y,66,16,1);  //显示“切”
}


/* 回声系列 -----------------------------------------------------------------*/
/************************************************
函数名称 ： Advance_Delay_A
功    能 ： 指定位置显示“预延时A”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Advance_Delay_A(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,68,16,1);     //显示“预”
	LCD_ShowChar_CN(x+16,y,54,16,1);  //显示“延”
	LCD_ShowChar_CN(x+32,y,56,16,1);  //显示“时”
	LCD_ShowChar(x+48,y,'A',16,1);    //显示“A”
}

/************************************************
函数名称 ： Main_Delay_A
功    能 ： 指定位置显示“主延时A”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Main_Delay_A(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,70,16,1);     //显示“主”
	LCD_ShowChar_CN(x+16,y,54,16,1);  //显示“延”
	LCD_ShowChar_CN(x+32,y,56,16,1);  //显示“时”
	LCD_ShowChar(x+48,y,'A',16,1);    //显示“A”
}

/************************************************
函数名称 ： Feedback_Value_A
功    能 ： 指定位置显示“反馈值A”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Feedback_Value_A(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,72,16,1);     //显示“反”
	LCD_ShowChar_CN(x+16,y,74,16,1);  //显示“馈”
	LCD_ShowChar_CN(x+32,y,42,16,1);  //显示“值”
	LCD_ShowChar(x+48,y,'A',16,1);    //显示“A”
}

/************************************************
函数名称 ： Volume_Out_A
功    能 ： 指定位置显示“音量A”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Volume_Out_A(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,48,16,1);     //显示“音”
	LCD_ShowChar_CN(x+16,y,78,16,1);  //显示“量”
//	LCD_ShowChar(x+32,y,'A',16,1);    //显示“A”
	LCD_ShowString(x+32,y,32,16,16,"OutA");
}

/************************************************
函数名称 ： Filter_A
功    能 ： 指定位置显示“滤波器A”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Filter_A(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,24,16,1);     //显示“滤”
	LCD_ShowChar_CN(x+16,y,26,16,1);  //显示“波”
	LCD_ShowChar_CN(x+32,y,28,16,1);  //显示“器”
	LCD_ShowChar(x+48,y,'A',16,1);    //显示“A”
}

/************************************************
函数名称 ： Advance_Delay_B
功    能 ： 指定位置显示“预延时B”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Advance_Delay_B(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,68,16,1);     //显示“预”
	LCD_ShowChar_CN(x+16,y,54,16,1);  //显示“延”
	LCD_ShowChar_CN(x+32,y,56,16,1);  //显示“时”
	LCD_ShowChar(x+48,y,'B',16,1);    //显示“B”
}

/************************************************
函数名称 ： Main_Delay_B
功    能 ： 指定位置显示“主延时B”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Main_Delay_B(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,70,16,1);     //显示“主”
	LCD_ShowChar_CN(x+16,y,54,16,1);  //显示“延”
	LCD_ShowChar_CN(x+32,y,56,16,1);  //显示“时”
	LCD_ShowChar(x+48,y,'B',16,1);    //显示“B”
}

/************************************************
函数名称 ： Feedback_Value_B
功    能 ： 指定位置显示“反馈值B”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Feedback_Value_B(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,72,16,1);     //显示“反”
	LCD_ShowChar_CN(x+16,y,74,16,1);  //显示“馈”
	LCD_ShowChar_CN(x+32,y,42,16,1);  //显示“值”
	LCD_ShowChar(x+48,y,'B',16,1);    //显示“B”
}

/************************************************
函数名称 ： Volume_Out_B
功    能 ： 指定位置显示“音量B”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Volume_Out_B(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,48,16,1);     //显示“音”
	LCD_ShowChar_CN(x+16,y,78,16,1);  //显示“量”
//	LCD_ShowChar(x+32,y,'B',16,1);    //显示“B”
	LCD_ShowString(x+32,y,32,16,16,"OutB");
}

/************************************************
函数名称 ： Filter_B
功    能 ： 指定位置显示“滤波器B”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Filter_B(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,24,16,1);     //显示“滤”
	LCD_ShowChar_CN(x+16,y,26,16,1);  //显示“波”
	LCD_ShowChar_CN(x+32,y,28,16,1);  //显示“器”
	LCD_ShowChar(x+48,y,'B',16,1);    //显示“B”
}

/* 均衡系列 -----------------------------------------------------------------*/
/************************************************
函数名称 ： Seg1_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg1_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg1");
}

/************************************************
函数名称 ： Seg2_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg2_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg2");
}

/************************************************
函数名称 ： Seg3_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg3_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg3");
}

/************************************************
函数名称 ： Seg4_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg4_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg4");
}

/************************************************
函数名称 ： Seg5_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg5_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg5");
}

/************************************************
函数名称 ： Seg6_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg6_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg6");
}

/************************************************
函数名称 ： Seg7_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg7_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg7");
}

/************************************************
函数名称 ： Seg8_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg8_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg8");
}

/************************************************
函数名称 ： Seg9_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Seg9_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,32,16,16,"Seg9");
}

/* 移频系列 -----------------------------------------------------------------*/
/************************************************
函数名称 ： Frequency_shift_value
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Frequency_shift_value(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,12,16,1);     //显示“移”
	LCD_ShowChar_CN(x+16,y,14,16,1);  //显示“频”
	LCD_ShowChar_CN(x+32,y,42,16,1);  //显示“值”
}

/************************************************
函数名称 ： Frequency_shift_switch
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Frequency_shift_switch(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,12,16,1);     //显示“移”
	LCD_ShowChar_CN(x+16,y,14,16,1);  //显示“频”
	LCD_ShowChar_CN(x+32,y,80,16,1);  //显示“开”
	LCD_ShowChar_CN(x+48,y,82,16,1);  //显示“关”
}

/* 动态范围压缩系列 ---------------------------------------------------------*/
/************************************************
函数名称 ： PreGain_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void PreGain_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,56,16,16,"PreGain");
}

/************************************************
函数名称 ： Shold_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Shold_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,40,16,16,"Shold");
}

/************************************************
函数名称 ： Ratio_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Ratio_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,40,16,16,"Ratio");
}

/************************************************
函数名称 ： Attack_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Attack_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,48,16,16,"Attack");
}

/************************************************
函数名称 ： Release_Show
功    能 ： 指定位置显示
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Release_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowString(x,y,56,16,16,"Release");
}

/************************************************
函数名称 ： MIC_Reverb_page2
功    能 ： 混响子界面显示
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MIC_Reverb_page2(void)
{
	Choose_place = 1;
	mic_state.mic_state_2 = Dry_flag;
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	Dry_voice(0,0,Elect_color);             //显示干声音量
	Wet_voice(0,18,Common_color);           //显示湿声音量
	Echo_time_delay(0,36,Common_color);     //显示回声延时
	Echo_Gain(0,54,Common_color);           //显示回声增益
	Reverb_Time(0,72,Common_color);         //显示混响时间
	HightorLow_Cut(0,90,Common_color);      //显示高低切
	
}

/************************************************
函数名称 ： MIC_Echo_page2
功    能 ： 回声子界面显示
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MIC_Echo_page2(void)
{
	mic_state.mic_state_2 = ADelay_A_flag;
	Choose_place = 1;
	Top_Init();  //顶部重新选择
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	Advance_Delay_A(0,0,Elect_color);       //显示预延时A
	Main_Delay_A(0,18,Common_color);        //显示主延时A
	Feedback_Value_A(0,36,Common_color);    //显示反馈值A
	Volume_Out_A(0,54,Common_color);        //显示音量OutA
	Filter_A(0,72,Common_color);            //显示滤波器A
	Advance_Delay_B(0,90,Common_color);     //显示预延时B
	Main_Delay_B(0,108,Common_color);       //显示主延时B
	
}

/************************************************
函数名称 ： MIC_Equili_page2
功    能 ： 均衡子界面显示
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MIC_Equili_page2(void)
{
	mic_state.mic_state_2 = Seg1_flag;
	Choose_place = 1;
	Top_Init(); //顶部重新选择
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	Seg1_Show(0,0,Elect_color);             //显示Seg1
	Seg2_Show(0,18,Common_color);           //显示Seg2
	Seg3_Show(0,36,Common_color);           //显示Seg3
	Seg4_Show(0,54,Common_color);           //显示Seg4
	Seg5_Show(0,72,Common_color);           //显示Seg5
	Seg6_Show(0,90,Common_color);           //显示Seg6
	Seg7_Show(0,108,Common_color);          //显示Seg7
	
}

/************************************************
函数名称 ： MIC_Frequenc_page2
功    能 ： 移频子界面显示
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MIC_Frequenc_page2(void)
{
	mic_state.mic_state_2 = FS_value_flag;
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	Frequency_shift_value(0,0,Elect_color);     //显示移频值
	Frequency_shift_switch(0,18,Common_color);  //显示显示开关
}

/************************************************
函数名称 ： MIC_DR_page2
功    能 ： 动态范围子界面显示
参    数 ： 无
返 回 值 ： 无
*************************************************/
void MIC_DR_page2(void)
{
	mic_state.mic_state_2 = PerGain_flag;
	Choose_place = 1;
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	PreGain_Show(0,0,Elect_color);             //显示PreGain
	Shold_Show(0,18,Common_color);             //显示Shold
	Ratio_Show(0,36,Common_color);             //显示Rati
	Attack_Show(0,54,Common_color);            //显示Attack
	Release_Show(0,72,Common_color);           //显示Release
}

/************************************************
函数名称 ： Echo_Volume
功    能 ： 回声音量界面
参    数 ： 无
返 回 值 ： 无
*************************************************/
void Echo_Volume(void)
{
	
}