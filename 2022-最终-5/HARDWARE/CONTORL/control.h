#ifndef  __CONTROL_H
#define  __CONTROL_H
#include "sys.h"
#include "usart.h"
#include "key.h"

#define SEND_BUF_SIZE 53
extern u8 SendBuff[SEND_BUF_SIZE];
extern u8 KeyValue;

void SendBuff_Init(void);
void KOGNZHI_1(void);
void USART_Light(void);
void ENCODER_Value_chuli(void);
void ENCODER_SW_1(void);
void ENCODER_SW_2(void);
void ENCODER_SW_3(void);
void ENCODER_SW_4(void);
u8 USART_check(void);
#endif
