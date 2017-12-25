/******************************************************************************
 * MenuConfig.C - �˵���������
 *
 * 
 * 2009/12/22, �˷棬QQ��178122887
 * 
 ******************************************************************************/

#ifndef __MENUCONFIG_H
#define __MENUCONFIG_H

#include "..\User\includes.h"

//���尴������
#define Key_Esc        keyokcode
#define Key_Enter      key1code
#define Key_Up         key2code
#define Key_Down       key3code

//--------�˵��ں˰�������
#define Key_First      Key_Up
#define Key_Last       Key_Down
#define Key_Prev       Key_Esc
#define Key_Next       Key_Enter

//----------------------------------------------lcdconfig
//��Ļ�����ʾ��
#define MaxScreenSize      2
//--------�˵������ж�
#define MenuIntDisable()                IntMasterDisable()
#define MenuIntEnable()                 IntMasterEnable()

#define Menu_LCD_Clr()                  Lcd_Clr()
#define Menu_LCD_Write_String(x,y,z)    LCD_Write_String(x,y,z)

//--------�˵��ڵ�����
#define MenuTotalNode      6

//--------�˵���ջ���
#define MenuStackDeep      5

//----------------------------------------------�˵��ں�
//--------�˵�״̬����
#define menufunc           0
#define numberfunc         1

//--------�˵���������
#define firstnode          1
#define lastnode           2
#define prevnode           3
#define nextnode           4

//--------�˵��ڵ�ṹ��
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

//--------�˵�����
typedef struct _MenuList
{
   struct _MenuNode *Point_Node[MenuTotalNode];
}MenuList;

//--------�˵��ں˱���
extern unsigned char MenuDeep;
extern unsigned char CurrentMenuStatus;

//--------�˵��ڵ���
extern MenuList MenuTotalList;
extern MenuNode *CurrentMenuNode;

//--------menuinit
extern void MenuListInit(void);
extern void MenuLoop(unsigned char key);

//--------�˵��ں�
extern MenuNode *SearchMenuNode(unsigned char nodeid,unsigned char searchtype);
extern MenuNode *SearchSomeOneMenuNode(unsigned char nodeid);
extern void MenuShow(void);
extern void MenuFunctionKey(unsigned char key);
extern void MenuNumberKey(unsigned char key);

//--------�˵���չ
extern void (*MenuNodeAction)(unsigned char key);

extern void MenuNode1Action(unsigned char key);
extern void MenuNode2Action(unsigned char key);
extern void MenuNode101Action(unsigned char key);
extern void MenuNode102Action(unsigned char key);
extern void MenuNode103Action(unsigned char key);
extern void MenuNode201Action(unsigned char key);

#endif