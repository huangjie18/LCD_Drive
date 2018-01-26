#ifndef __EXTI_H
#define __EXTI_H
#include "sys.h"

#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	
#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 
#define IR_INPUT GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

extern u8 irflag;
void EXTIX_Init(void);
#endif
