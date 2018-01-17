#ifndef __STATE_H
#define __STATE_H
#include "sys.h"


//����״̬
typedef enum
{
	Interface_1,     //����1״̬
	Interface_2,     //����2״̬
	Interface_3,     //����3״̬
	volume_stae,     //����״̬
	NB_STATE,
}State_t;
//���尴���¼�
typedef enum
{
	EVENT0,         //���¼�
	EVENT1,         //����+
	EVENT2,         //����-
	EVENT3,         //�ϼ�
	EVENT4,         //�¼�
	EVENT5,         //ȷ��
	EVENT6,         //�˳�
	EVENT7,         //
	NB_EVENTS,
}Event_t;

//����һ��״̬��
typedef struct FsmTable_s
{
//	u8 event;   //�¼�
	u8 CurState;  //��ǰ״̬
	void (*eventActFun)();  //����ָ��
	u8 NextState;  //��һ��״̬
	u8 LastState;  //��һ��״̬
}FsmTable_t;

void InitFsm(FsmTable_t* pFsm);    //��ʼ��״̬��
void FSM_EventHandle(FsmTable_t* pFsm,u8 event);  //�ַ��¼�
void Switch_state_up(void);                       //�ϼ��¼��ַ�
void Switch_state_down(void);                     //�¼��¼��ַ�
void FSM_StateTransfer(FsmTable_t* pFsm,u8 state);//״̬ת��
#endif
