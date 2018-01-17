#include "main.h"
#include "state.h"
#include "main.h"

typedef void(*action)();  //����һ������ָ��
//����ָ����;�У��¼���Ӧ�ĺ������У���ǰ״̬
static  action actions[NB_STATE][NB_EVENTS] =
{
	{
	 NULL,                         //EVENT0
	 NULL,                         //EVENT1
	 NULL,                         //EVENT2
     Mic_Main_Switch_UP,           //EVENT3
	 Mic_Main_Switch_Down,         //EVENT4
	 Mic_Main_Enter,               //EVENT5
	 NULL,                         //EVENT6
	 NULL,                         //EVENT7
	},//״̬Interface_1
	
	{
	 NULL,
	 NULL,
	 NULL,
     Switch_state_up,
	 Switch_state_down,
	 NULL,
	 Mic_Main_Esc,
	 NULL,
	},//״̬Interface_2
	
	{
	 NULL,
	 NULL,
	 NULL,
     NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	},//״̬Interface_3
	
	{
	 NULL,
	 NULL,
	 NULL,
     NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	},//volume_stae״̬
};

//״̬ת�������:�¼��������״̬ת�����У���ǰ״̬
static const State_t transitions[NB_STATE][NB_EVENTS]=
{   
	//              ����+       ����-       �ϼ�          �¼�       ȷ��         �˳�
	//  0             1           2          3            4          5            6           7
	{0,          volume_stae,volume_stae,Interface_1,Interface_1,Interface_2,Interface_1,          0},  //Interface_1״̬
	{0,          volume_stae,volume_stae,Interface_2,Interface_2,Interface_3,Interface_1,          0},  //Interface_2״̬
	{0,          volume_stae,volume_stae,Interface_3,Interface_3,Interface_1,Interface_2,          0},  //Interface_3״̬
	{0,          volume_stae,volume_stae,volume_stae,volume_stae,   NB_STATE,   NB_STATE,          0},  //volume_stae״̬
};
/************************************************
�������� �� ��ʼ��FSM
��    �� �� ��ʼ״̬
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void InitFsm(FsmTable_t* pFsm)
{
	pFsm->CurState = Interface_1;   //��ʼ��״̬Ϊ����1
}
/************************************************
�������� �� FSM_EventHandle
��    �� �� �¼�����
��    �� �� �¼�����
�� �� ֵ �� ��
*************************************************/
void FSM_EventHandle(FsmTable_t* pFsm,u8 event)
{
	void (*enventActFun)() = NULL;  //�¼�������ָ��Ϊ��
	u8 CurState = pFsm->CurState;   //��״̬
	u8 NexState = transitions[CurState][event];  //��һ��״̬    
	
	enventActFun = actions[CurState][event];  //�õ���������
	if(enventActFun) //�ж�������
	{
		enventActFun();                 //���к���
		FSM_StateTransfer(pFsm,NexState); //״̬Ǩ��
	}
}

/************************************************
�������� �� FSM_StateTransfer
��    �� �� ״̬ת��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void FSM_StateTransfer(FsmTable_t* pFsm,u8 state)
{
	if(state==volume_stae)
	{
		pFsm->LastState = pFsm->CurState;  //������״̬
		pFsm->CurState = state;            //תΪ��һ��״̬
	}
	else if(state==NB_STATE)
	{
		pFsm->CurState = pFsm->LastState;  //����ԭ״̬
	}
	else
	{
		pFsm->CurState = state;            //��һ��״̬
	}
}
/************************************************
�������� �� Switch_state_up
��    �� �� �ϼ��¼��ַ�
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Switch_state_up(void)
{
	switch(mic_state.mic_state_1)  //�ж�Ӧ��ѡ��һ���ӽ������
	{
		case Reverb_flag:
			Reverb_Page2_Switch_UP();  //�����ϼ��¼�����
			break;
		
		case Equili_flag:
			Equili_Page2_Switch_UP();  //����
			break;
		
		case Echo_flag:
			Echo_Page2_Switch_UP();    //����
			break;
		
		case Frequenc_flag:
			FS_Page2_Switch_UP();      //��Ƶ
			break;
		
		case DR_flag:
			DR_Page2_Switch_UP();      //��̬
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Switch_state_down
��    �� �� �¼��¼��ַ�
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Switch_state_down(void)
{
	switch(mic_state.mic_state_1)  //�ж�Ӧ��ѡ��һ���ӽ������
	{
		case Reverb_flag:
			Reverb_Page2_Switch_DOWN();  //�����ӽ����¼��¼�����
			break;
		
		case Equili_flag:
			Equili_Page2_Switch_DOWN();  //����
			break;
		
		case Echo_flag:
			Echo_Page2_Switch_DOWN();    //����
			break;
		
		case Frequenc_flag:
			FS_Page2_Switch_DOWN();      //��Ƶ
			break;
		
		case DR_flag:
			DR_Page2_Switch_DOWN();      //��̬
			break;
		
		default:
			break;
	}
}