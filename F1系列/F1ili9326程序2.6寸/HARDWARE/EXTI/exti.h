#ifndef __EXTI_H
#define __EXTI_H
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 
#define IR_INPUT GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)




extern u8 irflag;
void EXTIX_Init(void);

#endif
