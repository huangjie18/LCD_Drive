/**
  *********************************  STM32F0xx  ********************************
  * @�ļ���     �� mic_page2.h
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� 
  ******************************************************************************/
  
/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __MIC_PAGE2_H
#define __MIC_PAGE2_H
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "sys.h"
/* �����Ķ��� --------------------------------------------------------------*/


/* ������ʾ  ----------------------------------------------------------------*/
void Top_Init(void);                    //�����;��ⶥ����ʼ��
//���¼�
void Mic_Main_Switch_UP(void);          //�������ϼ�
void Mic_Main_Switch_Down(void);        //�������¼�
void Reverb_Page2_Switch_UP(void);   	//�����ӽ����ϼ�ѡ��
void Reverb_Page2_Switch_DOWN(void);	//�����ӽ����¼�ѡ��
void DR_Page2_Switch_UP(void);      	//��̬��Χ�����ϼ�ѡ��
void DR_Page2_Switch_DOWN(void);    	//��̬��Χ�����¼�ѡ��
void FS_Page2_Switch_UP(void);      	//��Ƶ�ϼ�ѡ��
void FS_Page2_Switch_DOWN(void);    	//��Ƶ�¼�ѡ��
void Equili_Page2_Switch_DOWN(void);    //�����¼�ѡ��
void Equili_Page2_Switch_UP(void); 		//�����ϼ�ѡ��
void Echo_Page2_Switch_DOWN(void);      //�����¼�ѡ��
void Echo_Page2_Switch_UP(void);        //�����ϼ�ѡ��

//ȷ���˳���
void Mic_Main_Enter(void);              //������ȷ����
void Mic_Main_Esc(void);                //�������˳���
#endif  /* _REVERB_H */
/**** Copyright (C)2016 Huang. All Rights Reserved **** END OF FILE ****/
