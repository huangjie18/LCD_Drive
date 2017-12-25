/******************************************************************************
 * MenuConfig.C - 菜单参数配置
 *
 * 
 * 2009/12/22, 潘锋，QQ：178122887
 * 
 ******************************************************************************/

#ifndef __MENUCONFIG_H
#define __MENUCONFIG_H

#include "..\User\includes.h"

//定义按键编码
#define Key_Esc        keyokcode
#define Key_Enter      key1code
#define Key_Up         key2code
#define Key_Down       key3code

//--------菜单内核按键定义
#define Key_First      Key_Up
#define Key_Last       Key_Down
#define Key_Prev       Key_Esc
#define Key_Next       Key_Enter

//----------------------------------------------lcdconfig
//屏幕最大显示项
#define MaxScreenSize      2
//--------菜单开关中断
#define MenuIntDisable()                IntMasterDisable()
#define MenuIntEnable()                 IntMasterEnable()

#define Menu_LCD_Clr()                  Lcd_Clr()
#define Menu_LCD_Write_String(x,y,z)    LCD_Write_String(x,y,z)

//--------菜单节点总数
#define MenuTotalNode      6

//--------菜单堆栈深度
#define MenuStackDeep      5

//----------------------------------------------菜单内核
//--------菜单状态类型
#define menufunc           0
#define numberfunc         1

//--------菜单索引类型
#define firstnode          1
#define lastnode           2
#define prevnode           3
#define nextnode           4

//--------菜单节点结构体
typedef struct _MenuNode
{
   unsigned int  MenuNodeID;
   unsigned char *MenuString;
   unsigned char MenuStatus;
   struct _MenuNode *First_Node;
   struct _MenuNode *Last_Node;
   struct _MenuNode *Prev_Node;
   struct _MenuNode *Next_Node;
   void(*Action)(unsigned char in);
}MenuNode;

//--------菜单链表
typedef struct _MenuList
{
   struct _MenuNode *Point_Node[MenuTotalNode];
}MenuList;

//--------菜单内核变量
extern unsigned char MenuDeep;
extern unsigned char CurrentMenuStatus;

//--------菜单节点链
extern MenuList MenuTotalList;
extern MenuNode *CurrentMenuNode;

//--------menuinit
extern void MenuListInit(void);
extern void MenuLoop(unsigned char key);

//--------菜单内核
extern MenuNode *SearchMenuNode(unsigned char nodeid,unsigned char searchtype);
extern MenuNode *SearchSomeOneMenuNode(unsigned char nodeid);
extern void MenuShow(void);
extern void MenuFunctionKey(unsigned char key);
extern void MenuNumberKey(unsigned char key);

//--------菜单扩展
extern void (*MenuNodeAction)(unsigned char key);

extern void MenuNode1Action(unsigned char key);
extern void MenuNode2Action(unsigned char key);
extern void MenuNode101Action(unsigned char key);
extern void MenuNode102Action(unsigned char key);
extern void MenuNode103Action(unsigned char key);
extern void MenuNode201Action(unsigned char key);

#endif