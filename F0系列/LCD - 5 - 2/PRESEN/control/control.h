#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
#include "lcd.h"
#include "mode.h"
#include "para.h"
#include "volume.h"

extern uint8 kai_flag;
/**************************定义函数***************************************/
void jiemian(void);
void jiemian1(void);
void jiemian_hun(uint16 *sta,uint8 *b);	 //显示混响子界面
void jiemian_hui(uint16 *sta,uint8 *b);	 //显示回声子界面
void shang(void);	 //向上键实现函数
void xia(void);		 //向下键实现函数
void queding(void);	 //确定键实现函数
void tuichu(void);	 //退出键实现函数
void queding_2(void); 
void kaiji(void);   //开机函数
void xuanze_shang_1(uint16 *sta,uint8 *i);//选中主界面1显示
void switch_i(uint16 *sta,uint8 *i);  //i选择界面
void switch_b_hun(uint16 *sta,uint8 *b);  //混响b选择界面
void switch_b_hui(uint16 *sta,uint8 *b);  //回声b选择界面
void Write_Flash(void);

#endif

