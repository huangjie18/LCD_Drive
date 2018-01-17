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
#ifndef __MIC_PAGE2_H
#define __MIC_PAGE2_H
/* 包含的头文件 --------------------------------------------------------------*/
#include "sys.h"
/* 变量的定义 --------------------------------------------------------------*/


/* 界面显示  ----------------------------------------------------------------*/
void Top_Init(void);                    //回声和均衡顶部初始化
//上下键
void Mic_Main_Switch_UP(void);          //主界面上键
void Mic_Main_Switch_Down(void);        //主界面下键
void Reverb_Page2_Switch_UP(void);   	//混响子界面上键选择
void Reverb_Page2_Switch_DOWN(void);	//混响子界面下键选择
void DR_Page2_Switch_UP(void);      	//动态范围界面上键选择
void DR_Page2_Switch_DOWN(void);    	//动态范围界面下键选择
void FS_Page2_Switch_UP(void);      	//移频上键选择
void FS_Page2_Switch_DOWN(void);    	//移频下键选择
void Equili_Page2_Switch_DOWN(void);    //均衡下键选择
void Equili_Page2_Switch_UP(void); 		//均衡上键选择
void Echo_Page2_Switch_DOWN(void);      //回声下键选择
void Echo_Page2_Switch_UP(void);        //回声上键选择

//确定退出键
void Mic_Main_Enter(void);              //主界面确定键
void Mic_Main_Esc(void);                //主界面退出键
#endif  /* _REVERB_H */
/**** Copyright (C)2016 Huang. All Rights Reserved **** END OF FILE ****/
