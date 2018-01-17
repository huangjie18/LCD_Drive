/**
  *********************************  STM32F0xx  ********************************
  * @�ļ���     �� reverb.h
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� 
  ******************************************************************************/
  
/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __REVERB_H
#define __REVERB_H
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "sys.h"
/* �ṹ�嶨��   --------------------------------------------------------------*/

/* ��������  ---- ------------------------------------------------------------*/
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
