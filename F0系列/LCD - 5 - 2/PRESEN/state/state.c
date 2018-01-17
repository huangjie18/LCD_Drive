#include "main.h"
#include "state.h"
#include "main.h"

typedef void(*action)();  //定义一个函数指针
//函数指针查表;列：事件对应的函数；行：当前状态
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
	},//状态Interface_1
	
	{
	 NULL,
	 NULL,
	 NULL,
     Switch_state_up,
	 Switch_state_down,
	 NULL,
	 Mic_Main_Esc,
	 NULL,
	},//状态Interface_2
	
	{
	 NULL,
	 NULL,
	 NULL,
     NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	},//状态Interface_3
	
	{
	 NULL,
	 NULL,
	 NULL,
     NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	},//volume_stae状态
};

//状态转换查表；列:事件产生后的状态转换；行：当前状态
static const State_t transitions[NB_STATE][NB_EVENTS]=
{   
	//              音量+       音量-       上键          下键       确定         退出
	//  0             1           2          3            4          5            6           7
	{0,          volume_stae,volume_stae,Interface_1,Interface_1,Interface_2,Interface_1,          0},  //Interface_1状态
	{0,          volume_stae,volume_stae,Interface_2,Interface_2,Interface_3,Interface_1,          0},  //Interface_2状态
	{0,          volume_stae,volume_stae,Interface_3,Interface_3,Interface_1,Interface_2,          0},  //Interface_3状态
	{0,          volume_stae,volume_stae,volume_stae,volume_stae,   NB_STATE,   NB_STATE,          0},  //volume_stae状态
};
/************************************************
函数名称 ： 初始化FSM
功    能 ： 初始状态
参    数 ： 无
返 回 值 ： 无
*************************************************/
void InitFsm(FsmTable_t* pFsm)
{
	pFsm->CurState = Interface_1;   //初始化状态为界面1
}
/************************************************
函数名称 ： FSM_EventHandle
功    能 ： 事件处理
参    数 ： 事件类型
返 回 值 ： 无
*************************************************/
void FSM_EventHandle(FsmTable_t* pFsm,u8 event)
{
	void (*enventActFun)() = NULL;  //事件处理函数指针为零
	u8 CurState = pFsm->CurState;   //现状态
	u8 NexState = transitions[CurState][event];  //下一个状态    
	
	enventActFun = actions[CurState][event];  //得到动作函数
	if(enventActFun) //有动作产生
	{
		enventActFun();                 //运行函数
		FSM_StateTransfer(pFsm,NexState); //状态迁移
	}
}

/************************************************
函数名称 ： FSM_StateTransfer
功    能 ： 状态转移
参    数 ： 无
返 回 值 ： 无
*************************************************/
void FSM_StateTransfer(FsmTable_t* pFsm,u8 state)
{
	if(state==volume_stae)
	{
		pFsm->LastState = pFsm->CurState;  //保存现状态
		pFsm->CurState = state;            //转为下一个状态
	}
	else if(state==NB_STATE)
	{
		pFsm->CurState = pFsm->LastState;  //返回原状态
	}
	else
	{
		pFsm->CurState = state;            //下一个状态
	}
}
/************************************************
函数名称 ： Switch_state_up
功    能 ： 上键事件分发
参    数 ： 无
返 回 值 ： 无
*************************************************/
void Switch_state_up(void)
{
	switch(mic_state.mic_state_1)  //判断应该选哪一个子界面操作
	{
		case Reverb_flag:
			Reverb_Page2_Switch_UP();  //混响上键事件处理
			break;
		
		case Equili_flag:
			Equili_Page2_Switch_UP();  //均衡
			break;
		
		case Echo_flag:
			Echo_Page2_Switch_UP();    //回声
			break;
		
		case Frequenc_flag:
			FS_Page2_Switch_UP();      //移频
			break;
		
		case DR_flag:
			DR_Page2_Switch_UP();      //动态
			break;
		
		default:
			break;
	}
}

/************************************************
函数名称 ： Switch_state_down
功    能 ： 下键事件分发
参    数 ： 无
返 回 值 ： 无
*************************************************/
void Switch_state_down(void)
{
	switch(mic_state.mic_state_1)  //判断应该选哪一个子界面操作
	{
		case Reverb_flag:
			Reverb_Page2_Switch_DOWN();  //混响子界面下键事件处理
			break;
		
		case Equili_flag:
			Equili_Page2_Switch_DOWN();  //均衡
			break;
		
		case Echo_flag:
			Echo_Page2_Switch_DOWN();    //回声
			break;
		
		case Frequenc_flag:
			FS_Page2_Switch_DOWN();      //移频
			break;
		
		case DR_flag:
			DR_Page2_Switch_DOWN();      //动态
			break;
		
		default:
			break;
	}
}