#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			83  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
//定义接受数据状态
enum
{
	USART_WAIT,        //等待数据状态
	USART_STARE,       //开始接收数据
	USART_CONTINUE,    //持续接收数据
	USART_COMPLETE,    //接收完成状态
};		
enum
{
	USART_RX_BUF_LOCK=0, 
	USART_RX_BUF_UNLOCK=!USART_RX_BUF_LOCK,
};		
extern u8 check;
extern u8 check_sum;		
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u8 USART_jiaoyan;
extern u8 g_usart_curstate;
extern u8 USART_RX_BUF_STATE;
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


