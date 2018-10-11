#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			83  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
//�����������״̬
enum
{
	USART_WAIT,        //�ȴ�����״̬
	USART_STARE,       //��ʼ��������
	USART_CONTINUE,    //������������
	USART_COMPLETE,    //�������״̬
};		
enum
{
	USART_RX_BUF_LOCK=0, 
	USART_RX_BUF_UNLOCK=!USART_RX_BUF_LOCK,
};		
extern u8 check;
extern u8 check_sum;		
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern u8 USART_jiaoyan;
extern u8 g_usart_curstate;
extern u8 USART_RX_BUF_STATE;
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


