#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "lcd.h"
#include "mode.h"
#include "para.h"
#include "volume.h"

extern uint8 kai_flag;
/**************************���庯��***************************************/
void jiemian(void);
void jiemian1(void);
void jiemian_hun(uint16 *sta,uint8 *b);	 //��ʾ�����ӽ���
void jiemian_hui(uint16 *sta,uint8 *b);	 //��ʾ�����ӽ���
void shang(void);	 //���ϼ�ʵ�ֺ���
void xia(void);		 //���¼�ʵ�ֺ���
void queding(void);	 //ȷ����ʵ�ֺ���
void tuichu(void);	 //�˳���ʵ�ֺ���
void queding_2(void); 
void kaiji(void);   //��������
void xuanze_shang_1(uint16 *sta,uint8 *i);//ѡ��������1��ʾ
void switch_i(uint16 *sta,uint8 *i);  //iѡ�����
void switch_b_hun(uint16 *sta,uint8 *b);  //����bѡ�����
void switch_b_hui(uint16 *sta,uint8 *b);  //����bѡ�����
void Write_Flash(void);

#endif

