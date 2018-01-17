#ifndef __STATE_H
#define __STATE_H
#include "sys.h"


//定义状态
typedef enum
{
	Interface_1,     //界面1状态
	Interface_2,     //界面2状态
	Interface_3,     //界面3状态
	volume_stae,     //音量状态
	NB_STATE,
}State_t;
//定义按键事件
typedef enum
{
	EVENT0,         //空事件
	EVENT1,         //音量+
	EVENT2,         //音量-
	EVENT3,         //上键
	EVENT4,         //下键
	EVENT5,         //确定
	EVENT6,         //退出
	EVENT7,         //
	NB_EVENTS,
}Event_t;

//定义一个状态机
typedef struct FsmTable_s
{
//	u8 event;   //事件
	u8 CurState;  //当前状态
	void (*eventActFun)();  //函数指针
	u8 NextState;  //下一个状态
	u8 LastState;  //上一个状态
}FsmTable_t;

void InitFsm(FsmTable_t* pFsm);    //初始化状态机
void FSM_EventHandle(FsmTable_t* pFsm,u8 event);  //分发事件
void Switch_state_up(void);                       //上键事件分发
void Switch_state_down(void);                     //下键事件分发
void FSM_StateTransfer(FsmTable_t* pFsm,u8 state);//状态转移
#endif
