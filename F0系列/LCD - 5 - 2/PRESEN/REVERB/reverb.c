/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： reverb.c
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 第一界面设计
                   
  ******************************************************************************/
  
/* 包含的头文件 --------------------------------------------------------------*/
#include "reverb.h"
#include "DISPLAY_TFT.h"
#include "lcd.h"
#include "mic_page2_1.h"
/* 宏定义  -------------------------------------------------------------------*/
static u8 MIC_Options_flag=0;
/************************************************
函数名称 ： Reverb_Show
功    能 ： 指定位置显示“混响”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Reverb_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,0,16,1);    //显示“混”
	LCD_ShowChar_CN(x+16,y,2,16,1); //显示“响”
}

/************************************************
函数名称 ： Equili_Show
功    能 ： 指定位置显示“均衡”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Equili_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,4,16,1);    //显示“均”
	LCD_ShowChar_CN(x+16,y,6,16,1); //显示“衡”
}

/************************************************
函数名称 ： Echo_Show
功    能 ： 指定位置显示“回声”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Echo_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,8,16,1);       //显示“回”
	LCD_ShowChar_CN(x+16,y,10,16,1);   //显示“声”
}

/************************************************
函数名称 ： Frequenc_shift_Show
功    能 ： 指定位置显示“移频”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Frequenc_shift_Show(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,12,16,1);       //显示“移”
	LCD_ShowChar_CN(x+16,y,14,16,1);    //显示“频”
}

/************************************************
函数名称 ： DR_compress
功    能 ： 指定位置显示“动态范围压缩”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void DR_compress(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,84,16,1);       //显示“动”
	LCD_ShowChar_CN(x+16,y,86,16,1);    //显示“态”
	LCD_ShowChar_CN(x+32,y,88,16,1);    //显示“范”
	LCD_ShowChar_CN(x+48,y,90,16,1);    //显示“围”
}

/************************************************
函数名称 ： Noise_shold
功    能 ： 指定位置显示“噪声门阈”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Noise_shold(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,36,16,1);       //显示“噪”
	LCD_ShowChar_CN(x+16,y,10,16,1);    //显示“声”
	LCD_ShowChar_CN(x+32,y,38,16,1);    //显示“门”
	LCD_ShowChar_CN(x+48,y,40,16,1);    //显示“阈”
}

/************************************************
函数名称 ： Input_qualcomm
功    能 ： 指定位置显示“噪声门阈”
参    数 ： x:水平位置;y:垂直位置;bk:画笔颜色
返 回 值 ： 无
*************************************************/
void Input_qualcomm(u16 x,u16 y,uint16 bk)
{
	POINT_COLOR = bk;
	LCD_ShowChar_CN(x,y,16,16,1);       //显示“噪”
	LCD_ShowChar_CN(x+16,y,18,16,1);    //显示“声”
	LCD_ShowChar_CN(x+32,y,20,16,1);    //显示“门”
	LCD_ShowChar_CN(x+48,y,22,16,1);    //显示“阈”
}
/************************************************
函数名称 ： Mic_Main_interface
功    能 ： 显示主界面
参    数 ： 无
返 回 值 ： 无
*************************************************/
void Mic_Main_interface(void)
{
	mic_state.mic_state_1 = Reverb_flag;
	gui_draw_arcrectangle(0,0,64,18,3,1,gui_elect);
	Reverb_Show(0,0,Elect_color); 		      //显示混响
	Equili_Show(0,18,Common_color);           //显示均衡
	Echo_Show(0,36,Common_color);       	  //显示回声
	Frequenc_shift_Show(0,54,Common_color);   //显示移频
	Noise_shold(0,72,Common_color);           //显示噪声门阈
	DR_compress(0,90,Common_color);           //显示动态范围
	Input_qualcomm(0,108,Common_color);       //显示输入高通
}

