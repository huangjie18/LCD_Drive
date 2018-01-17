/**
  *********************************  STM32F0xx  ********************************
  * @文件名     ： key.h
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 
  ******************************************************************************/
/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "sys.h"

/* 宏定义 --------------------------------------------------------------------*/
//输入
#define  key1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) //读取PA15
#define  key2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)  //读取PB3
#define  key3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)  //读取PB4
#define  key6  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)  //读取PB7
//输出
#define  key5_Set    GPIO_SetBits(GPIOB,GPIO_Pin_5)      //PB5输出1
#define  key4_Set    GPIO_SetBits(GPIOB,GPIO_Pin_6)      //PB6输出1
#define  key4_Reset  GPIO_ResetBits(GPIOB,GPIO_Pin_6)    //PB6输出0
#define  key5_Reset  GPIO_ResetBits(GPIOB,GPIO_Pin_5)    //PB5输出0
#define  POWER_OFF   GPIO_ResetBits(GPIOA,GPIO_Pin_10)   //PA10输出0
#define  POWER_ON    GPIO_SetBits(GPIOA,GPIO_Pin_10)      //PA10输出1
/* 函数申明 ------------------------------------------------------------------*/
void KEY_Init(void);
u8 KEY_Scan(void);
#endif




