/**
  *********************************  STM32F0xx  ********************************
  * @�ļ���     �� key.h
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� 
  ******************************************************************************/
/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "sys.h"

/* �궨�� --------------------------------------------------------------------*/
//����
#define  key1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) //��ȡPA15
#define  key2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)  //��ȡPB3
#define  key3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)  //��ȡPB4
#define  key6  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)  //��ȡPB7
//���
#define  key5_Set    GPIO_SetBits(GPIOB,GPIO_Pin_5)      //PB5���1
#define  key4_Set    GPIO_SetBits(GPIOB,GPIO_Pin_6)      //PB6���1
#define  key4_Reset  GPIO_ResetBits(GPIOB,GPIO_Pin_6)    //PB6���0
#define  key5_Reset  GPIO_ResetBits(GPIOB,GPIO_Pin_5)    //PB5���0
#define  POWER_OFF   GPIO_ResetBits(GPIOA,GPIO_Pin_10)   //PA10���0
#define  POWER_ON    GPIO_SetBits(GPIOA,GPIO_Pin_10)      //PA10���1
/* �������� ------------------------------------------------------------------*/
void KEY_Init(void);
u8 KEY_Scan(void);
#endif




