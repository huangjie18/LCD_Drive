#ifndef __INIT_H
#define __INIT_H
#include "sys.h"


void LED_Init(void);
void KEY_Init(void);
void EXTIX_Init(void);
void TIM3_Int_Init(u16 arr,u16 psc);
#endif
