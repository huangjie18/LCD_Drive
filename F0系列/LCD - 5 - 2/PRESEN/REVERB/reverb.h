/**
  *********************************  STM32F0xx  ********************************
  * @文件名     ： reverb.h
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 
  ******************************************************************************/
  
/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __REVERB_H
#define __REVERB_H
/* 包含的头文件 --------------------------------------------------------------*/
#include "sys.h"
/* 结构体定义   --------------------------------------------------------------*/

/* 函数定义  ---- ------------------------------------------------------------*/
void Reverb_Show(u16 x,u16 y,uint16 bk);
void Equili_Show(u16 x,u16 y,uint16 bk);
void Echo_Show(u16 x,u16 y,uint16 bk);
void Frequenc_shift_Show(u16 x,u16 y,uint16 bk);
void DR_compress(u16 x,u16 y,uint16 bk);
void Noise_shold(u16 x,u16 y,uint16 bk);
void Input_qualcomm(u16 x,u16 y,uint16 bk);
void Mic_Main_interface(void);
#endif  /* _REVERB_H */
/**** Copyright (C)2016 Huang. All Rights Reserved **** END OF FILE ****/
