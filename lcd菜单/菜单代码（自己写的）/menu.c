
#include "G:\lm3s\lcd\menu.h"               //�����ײ�ͷ�ļ�
#include "G:\lm3s\lcd\lcd.h"

//------------------------------------------------------------------------------------
//                          �˵����ݲ������ݶ�̬���ӵķ�ʽ
//------------------------------------------------------------------------------------
//       ��ӭ����          |         �����Ӳ�             |      �Ӳ㷵���ϲ�
//           |             |             |                |           |
//  ��ʼ����һ�����ݼ����� | ���浱ǰ��״̬(״̬������ջ) | �ָ��ϲ�״̬(״̬���ݳ�ջ)
//           |             |             |                |           |
//    �����һ�㻭��       |    ��ʼ���Ӳ����ݼ�����      |     �ػ��ϲ�״̬����
//           |             |             |                |           |
// �����һ�㰴���¼����  |    �����Ӳ㰴���¼����      |   �����Ӳ㰴���¼����
//   |     |    |    |     |     |     |    |    |        |    |     |    |    | 
//  Esc  Enter  Up  Down   |    Esc  Enter  Up  Down      |   Esc  Enter  Up  Down 
//   |     |    |    |     |     |     |    |    |        |    |     |    |    |  
// �˳�  ����  ��Ļ ��Ļ   |    �˳�  ����  ��Ļ ��Ļ     |  �˳�  ����  ��Ļ ��Ļ 
// ����  ���  ���� ����   |    ����  ���  ���� ����     |  ����  ���  ���� ���� 
//       ѡ��  ���� ����   |    ����  ѡ��  ���� ����     |  ����  ѡ��  ���� ���� 
//       �Ĳ�              |    �ϲ�  �Ĳ�                |  �ϲ�  �Ĳ�      
//
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

#define Key_Esc        0x04                 //���尴������
#define Key_Enter      0x08
#define Key_Up         0x10
#define Key_Down       0x20

//--------------------------------------------------------
unsigned char KeyFuncIndex        =0;       //������������

unsigned char MaxScreenDisp       =4;       //��Ļ�����ʾ��

//--------------------------------------------------------
unsigned char CurrentMenuIndex    =0;       //��ǰ�˵��������
unsigned char CurrentMenuItem     =0;       //��ǰ�˵���Ŀ
unsigned char CurrentMenuItemNum  =0;       //��ǰ�˵���Ŀ��
unsigned char **CurrentMenuString =0;       //��ǰ�˵���ʾ����ָ��
unsigned char CurrentMenuCur      =0;       //��ǰ�˵��������Ļ��λ��
unsigned char CurrentMenuScroll   =0;       //��ǰ�˵���������

//--------------------------------------------------------
unsigned char MenuDeep            =0;       //��ǰ�˵���ջ���

//-------------------------------------------------------- �û��˵���ʾ����
//--------��������
unsigned char * TopMenuString[]     ={"1.menu","2.menu","3.menu","4.menu","5.menu",};
//--------ϵͳ����������
unsigned char * ParaMenuString[]    ={"1.1menu","1.2menu","1.3menu","1.4menu","1.5menu","1.6menu","1.7menu","1.8menu","1.9menu","1.10menu",};
//--------ϵͳʱ�������
unsigned char * TimeMenuString[]    ={"2.1menu","2.2menu","2.3menu","2.4menu","2.5menu",};
//--------ϵͳ��ѯ������
unsigned char * InquireMenuString[] ={"3.1menu","3.2menu","3.3menu","3.4menu","3.5menu",};
//--------ϵͳ��Ϣ������
unsigned char * MessageMenuString[] ={"4.1menu","4.2menu","4.3menu","4.4menu","4.5menu",};
//--------ϵͳ���Բ�����
unsigned char * TestMenuString[]    ={"5.1menu","5.2menu","5.3menu","5.4menu","5.5menu",};

//---------------------------------------------------------
//--------�˵��ṹ��
//--------�˵���ID, Ҳ���ǲ˵���������, �Ǹ��˵�˳�����ӵĽڵ�
//--------�˵��ı���,
//--------�˵�����Ŀ��
//--------�˵���ͼ��
//--------�˵�����ʾ����
//--------�˵�����ִ�к���
struct Menu
{
   unsigned char MenuID;
   unsigned char **MenuTitle;
   unsigned char MenuNum;
   unsigned char **MenuIco;
   unsigned char **MenuString;
   void* (*AddAction)();
};

//--------����˵�
struct Menu TopMenu=
{
   0,
   0,
   5,
   0,
   TopMenuString,
   (void*)0,
};

//--------ϵͳ������˵�
struct Menu ParaMenu=
{
   5,
   0,
   10,
   0,
   ParaMenuString,
   (void*)0,
};

//---------ϵͳʱ���˵�
struct Menu TimeMenu=
{
   10,
   0,
   5,
   0,
   TimeMenuString,
   (void*)0,
};

//--------ϵͳ��ѯ��˵�
struct Menu InquireMenu=
{
   15,
   0,
   5,
   0,
   InquireMenuString,
   (void*)0,
};

//--------ϵͳ��Ϣ��˵�
struct Menu MessageMenu=
{
   20,
   0,
   5,
   0,
   MessageMenuString,
   (void*)0,
};

//--------ϵͳ���Բ�˵�
struct Menu TestMenu=
{
   25,
   0,
   5,
   0,
   TestMenuString,
   (void*)0,
};

//------------------------------------------------------------�˵��ں�
//--------�˵��ػ�, �����ϲ�ʱ����
void ReDrawScreen(void);

//--------�˵���ջ
//--------�˵�ID, Ҳ����������
//--------�˵���
//--------�˵���Ŀ��
//--------�˵���ʾ����
//--------���λ��
//--------�˵���������
struct MenuStack
{
   unsigned char MenuStackIndex;
   unsigned char MenuStackItem;
   unsigned char MenuStackItemNum;
   unsigned char **MenuStackString;
   unsigned char MenuStackCur;
   unsigned char MenuStackScroll;
};

//--------�˵���ջ��ʼ��
struct MenuStack MenuDeepStack[10];

//--------��ǰ�˵���ջ
void PushMenuStack(void)
{
   IntMasterDisable();
   MenuDeep++;
   MenuDeepStack[MenuDeep].MenuStackIndex    = CurrentMenuIndex;
   MenuDeepStack[MenuDeep].MenuStackItem     = CurrentMenuItem;
   MenuDeepStack[MenuDeep].MenuStackItemNum  = CurrentMenuItemNum;
   MenuDeepStack[MenuDeep].MenuStackString   = CurrentMenuString;
   MenuDeepStack[MenuDeep].MenuStackCur      = CurrentMenuCur;
   MenuDeepStack[MenuDeep].MenuStackScroll   = CurrentMenuScroll;
   IntMasterEnable();
}

//--------�����ϲ�˵�, �˵���ջ
void PopMenuStack(void)
{
   IntMasterDisable();
   CurrentMenuIndex   = MenuDeepStack[MenuDeep].MenuStackIndex;
   CurrentMenuItem    = MenuDeepStack[MenuDeep].MenuStackItem;
   CurrentMenuItemNum = MenuDeepStack[MenuDeep].MenuStackItemNum;
   CurrentMenuString  = MenuDeepStack[MenuDeep].MenuStackString;
   CurrentMenuCur     = MenuDeepStack[MenuDeep].MenuStackCur;
   CurrentMenuScroll  = MenuDeepStack[MenuDeep].MenuStackScroll;
   KeyFuncIndex       = CurrentMenuIndex;
   MenuDeep--;
   IntMasterEnable();
}

//--------����˵�����
void DisMenuTopInit(void);
void DisMenuTopEsc(void);
void DisMenuTopEnter(void);
void DisMenuTopUp(void);
void DisMenuTopDown(void);

//--------ϵͳ���������
void DisMenuParaInit(void);
void DisMenuParaEsc(void);
void DisMenuParaEnter(void);
void DisMenuParaUp(void);
void DisMenuParaDown(void);

//--------ϵͳʱ������
void DisMenuTimeInit(void);
void DisMenuTimeEsc(void);
void DisMenuTimeEnter(void);
void DisMenuTimeUp(void);
void DisMenuTimeDown(void);

//--------ϵͳ��ѯ�����
void DisMenuInquireInit(void);
void DisMenuInquireEsc(void);
void DisMenuInquireEnter(void);
void DisMenuInquireUp(void);
void DisMenuInquireDown(void);

//--------ϵͳ��Ϣ�����
void DisMenuMessageInit(void);
void DisMenuMessageEsc(void);
void DisMenuMessageEnter(void);
void DisMenuMessageUp(void);
void DisMenuMessageDown(void);

//--------ϵͳ���Բ����
void DisMenuTestInit(void);
void DisMenuTestEsc(void);
void DisMenuTestEnter(void);
void DisMenuTestUp(void);
void DisMenuTestDown(void);

//--------��ǰ��˵���������
void (*KeyFuncPtr)();

//--------���������ṹ��
//--------����--�˵�������--����, ������ʼ������˵�
//--------�������ز���
//--------�����������
//--------�������ϲ���
//--------�������²���
//--------��������ִ�к���
typedef struct 
{
   unsigned char KeyStateIndex;
   unsigned char KeyEscState;
   unsigned char KeyEnterState;
   unsigned char KeyUpState;
   unsigned char KeyDownState;
   void (*CurrentOperate)();
}KeyFuncStruct;

//--------��������
KeyFuncStruct KeyTab[]=
{   
//  |---------------------------------> Index
//  |  |------------------------------> Esc
//  |  |  |---------------------------> Enter
//  |  |  |  |------------------------> Up
//  |  |  |  |  |---------------------> Down
//  |  |  |  |  |  |------------------> ���ܺ���
  { 0, 1, 2, 3, 4,(DisMenuTopInit)}, //-����
  { 1, 0, 0, 0, 0,(DisMenuTopEsc)},
  { 2, 0, 0, 0, 0,(DisMenuTopEnter)},
  { 3, 0, 0, 0, 0,(DisMenuTopUp)},
  { 4, 0, 0, 0, 0,(DisMenuTopDown)},
  
  { 5, 6, 7, 8, 9,(DisMenuParaInit)}, //-����
  { 6, 0, 0, 0, 0,(DisMenuParaEsc)},
  { 7, 0, 0, 0, 0,(DisMenuParaEnter)},
  { 8, 0, 0, 0, 0,(DisMenuParaUp)},
  { 9, 0, 0, 0, 0,(DisMenuParaDown)},
  
  {10,11,12,13,14,(DisMenuTimeInit)}, //-ʱ��
  {11, 0, 0, 0, 0,(DisMenuTimeEsc)},
  {12, 0, 0, 0, 0,(DisMenuTimeEnter)},
  {13, 0, 0, 0, 0,(DisMenuTimeUp)},
  {14, 0, 0, 0, 0,(DisMenuTimeDown)},
  
  {15,16,17,18,19,(DisMenuInquireInit)}, //-��ѯ
  {16, 0, 0, 0, 0,(DisMenuInquireEsc)},
  {17, 0, 0, 0, 0,(DisMenuInquireEnter)},
  {18, 0, 0, 0, 0,(DisMenuInquireUp)},
  {19, 0, 0, 0, 0,(DisMenuInquireDown)},
  
  {20,21,22,23,24,(DisMenuMessageInit)}, //-��Ϣ
  {21, 0, 0, 0, 0,(DisMenuMessageEsc)},
  {22, 0, 0, 0, 0,(DisMenuMessageEnter)},
  {23, 0, 0, 0, 0,(DisMenuMessageUp)},
  {24, 0, 0, 0, 0,(DisMenuMessageDown)},
  
  {25,26,27,28,29,(DisMenuTestInit)}, //-����
  {26, 0, 0, 0, 0,(DisMenuTestEsc)},
  {27, 0, 0, 0, 0,(DisMenuTestEnter)},
  {28, 0, 0, 0, 0,(DisMenuTestUp)},
  {29, 0, 0, 0, 0,(DisMenuTestDown)},
};

//--------��������
void OnKey(unsigned char key)
{ 
   switch(key)
   {
      case Key_Esc:
           KeyFuncIndex = KeyTab[KeyFuncIndex].KeyEscState;
           KeyFuncPtr   = KeyTab[KeyFuncIndex].CurrentOperate;
           (*KeyFuncPtr)();
           break;
           
      case Key_Enter:
           KeyFuncIndex = KeyTab[KeyFuncIndex].KeyEnterState;
           KeyFuncPtr   = KeyTab[KeyFuncIndex].CurrentOperate;
           (*KeyFuncPtr)();
           break;
           
      case Key_Up:
           KeyFuncIndex = KeyTab[KeyFuncIndex].KeyUpState;
           KeyFuncPtr   = KeyTab[KeyFuncIndex].CurrentOperate;
           (*KeyFuncPtr)();
           break;
           
      case Key_Down:
           KeyFuncIndex = KeyTab[KeyFuncIndex].KeyDownState;
           KeyFuncPtr   = KeyTab[KeyFuncIndex].CurrentOperate;
           (*KeyFuncPtr)();
           break;
         
      default :break;
   }
}

//--------������һ��˵�
void TurnToNextMenu(unsigned char menuid)
{
   PushMenuStack();
   KeyFuncPtr   = KeyTab[menuid].CurrentOperate;
   (*KeyFuncPtr)();
}

//--------������һ��˵�
void TurnToAboveMenu(void)
{
   PopMenuStack();
   ReDrawScreen();
}

//--------��������˵���������
void AmendKeyIndex(unsigned char menuid)
{
   KeyFuncIndex = menuid;
}

//--------��Ļ�ػ�, �˵�����ʱ����
void ReDrawScreen(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

//----------------------------------------------------------- �˵�����
//--------��ӭ����
void DispMenu(void)
{
   LCD_write_string(2,0,"��ӭ����");
}

//--------�����ʼ��, ��ÿ��ĳ�ʼֻ���ڽ�������˵�ʱ��ʼ��
void DisMenuTopInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                                    //����

   CurrentMenuIndex    = TopMenu.MenuID;         //������ʼ��
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = TopMenu.MenuNum;
   CurrentMenuString   = TopMenu.MenuString;
   CurrentMenuCur      = 1;
   CurrentMenuScroll   = 0;

   AmendKeyIndex(CurrentMenuIndex);             //������ǰ�㰴������
   
   if(CurrentMenuItemNum<MaxScreenDisp)         //��ǰ����Ŀ��С�������Ļ��ʾ��
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");    //����
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));    //��˵�
   }
}

void DisMenuTopEsc(void)
{
   AmendKeyIndex(CurrentMenuIndex);       //������ǰ�㰴������
}
void DisMenuTopEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);       //������ǰ�㰴������
   
   switch(CurrentMenuItem)                //�����²�˵�
   {
      case 1:
           lcd_clr();
           TurnToNextMenu(ParaMenu.MenuID);   //��������Ӳ˵�
           break;
           
      case 2:
           TurnToNextMenu(TimeMenu.MenuID);   //����ʱ���Ӳ˵�
           break;
           
      case 3:
           TurnToNextMenu(InquireMenu.MenuID);  //�����ѯ�Ӳ˵�
           break;
           
      case 4:
           TurnToNextMenu(MessageMenu.MenuID);  //������Ϣ�Ӳ˵�
           break;
           
      case 5:
           TurnToNextMenu(TestMenu.MenuID);   //��������Ӳ˵�
           break;
           
      default :break;
   }
}

void DisMenuTopUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                           //����
   
   AmendKeyIndex(CurrentMenuIndex);     //������ǰ�㰴������

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)                //1�ǵ�ǰ�˵���Ķ�, �˵���δ����, ��һ
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))  //������λ�õ�0, ������Ļ�������¹�����¼
   {
      CurrentMenuScroll--;                         //��Ļ���Ϲ���
   }

   if(CurrentMenuCur==0)                           //1�ǹ��Ķ�, �����Ϊ0ʱ
   {
      CurrentMenuCur++;                            //�������λ��
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)            //��ǰ��˵���Ŀ��С����Ļ�����ʾ����
   {
      MaxDisp = CurrentMenuItemNum;                //��ɨ������Ϊ��ǰ��˵�����
   }
   else
   {
      MaxDisp = MaxScreenDisp;                     //��ɨ������Ϊ��Ļ�����ʾ����
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");      //����
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));    //��˵�
   }
}   

void DisMenuTopDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                                    //����
   
   AmendKeyIndex(CurrentMenuIndex);              //������ǰ�㰴������

   CurrentMenuCur++;                             //�������
   
   if(CurrentMenuItem<CurrentMenuItemNum)        //��ǰ��С�ڵ�ǰ�˵��������Ŀ��
   {
      CurrentMenuItem++;                         //��ǰ�����һ
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))      //��굽������Ļ��, ��ʾ��Ŀ����û�е��� 
   {
      CurrentMenuScroll++;                        //��Ļ����һ��, ��ʾ��ǰ��ѡ��
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))       //����������Ļ��, ������˵�ǰ���˵�����
   {
      CurrentMenuCur--;                           //�������λ��
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)           //��ǰ��˵���Ŀ��С����Ļ�����ʾ����
   {
      MaxDisp = CurrentMenuItemNum;               //��ɨ������Ϊ��ǰ��˵�����
   }
   else
   {
      MaxDisp = MaxScreenDisp;                    //��ɨ������Ϊ��Ļ�����ʾ����
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");     //����
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));   //��˵�
   }
}

//----------------------------------------------------
//--------ϵͳ������
void DisMenuParaInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   CurrentMenuIndex    = ParaMenu.MenuID;
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = ParaMenu.MenuNum;
   CurrentMenuString   = ParaMenu.MenuString;
   CurrentMenuCur      = 1;
   CurrentMenuScroll   =0;
   
   AmendKeyIndex(CurrentMenuIndex);
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuParaEsc(void)
{
   TurnToAboveMenu();
}

void DisMenuParaEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);
   
}

void DisMenuParaUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))
   {
      CurrentMenuScroll--;
   }

   if(CurrentMenuCur==0)
   {
      CurrentMenuCur++;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuParaDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur++;
   
   if(CurrentMenuItem<CurrentMenuItemNum)
   {
      CurrentMenuItem++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))
   {
      CurrentMenuScroll++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))
   {
      CurrentMenuCur--;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

//--------------------------------------------------------------
//-------ϵͳʱ��
void DisMenuTimeInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   CurrentMenuIndex    = TimeMenu.MenuID;
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = TimeMenu.MenuNum;
   CurrentMenuString   = TimeMenu.MenuString;
   CurrentMenuCur      =1;
   CurrentMenuScroll   =0;
   
   AmendKeyIndex(CurrentMenuIndex);
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuTimeEsc(void)
{
   TurnToAboveMenu();
}

void DisMenuTimeEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);
}

void DisMenuTimeUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))
   {
      CurrentMenuScroll--;
   }

   if(CurrentMenuCur==0)
   {
      CurrentMenuCur++;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuTimeDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur++;
   
   if(CurrentMenuItem<CurrentMenuItemNum)
   {
      CurrentMenuItem++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))
   {
      CurrentMenuScroll++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))
   {
      CurrentMenuCur--;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

//----------------------------------------------------------------
//--------ϵͳ��ѯ
void DisMenuInquireInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   CurrentMenuIndex    = InquireMenu.MenuID;
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = InquireMenu.MenuNum;
   CurrentMenuString   = InquireMenu.MenuString;
   CurrentMenuCur      =1;
   CurrentMenuScroll   =0;
   
   AmendKeyIndex(CurrentMenuIndex);
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuInquireEsc(void)
{
   TurnToAboveMenu();
}

void DisMenuInquireEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);
}

void DisMenuInquireUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))
   {
      CurrentMenuScroll--;
   }

   if(CurrentMenuCur==0)
   {
      CurrentMenuCur++;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuInquireDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur++;
   
   if(CurrentMenuItem<CurrentMenuItemNum)
   {
      CurrentMenuItem++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))
   {
      CurrentMenuScroll++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))
   {
      CurrentMenuCur--;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

//------------------------------------------------------------------
//-------ϵͳ��Ϣ
void DisMenuMessageInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   CurrentMenuIndex    = MessageMenu.MenuID;
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = MessageMenu.MenuNum;
   CurrentMenuString   = MessageMenu.MenuString;
   CurrentMenuCur      =1;
   CurrentMenuScroll   =0;
   
   AmendKeyIndex(CurrentMenuIndex);
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}
void DisMenuMessageEsc(void)
{
   TurnToAboveMenu();
}

void DisMenuMessageEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);
}

void DisMenuMessageUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))
   {
      CurrentMenuScroll--;
   }

   if(CurrentMenuCur==0)
   {
      CurrentMenuCur++;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuMessageDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur++;
   
   if(CurrentMenuItem<CurrentMenuItemNum)
   {
      CurrentMenuItem++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))
   {
      CurrentMenuScroll++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))
   {
      CurrentMenuCur--;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

//-----------------------------------------------------------------------
//--------ϵͳ����
void DisMenuTestInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();

   CurrentMenuIndex    = TestMenu.MenuID;
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = TestMenu.MenuNum;
   CurrentMenuString   = TestMenu.MenuString;
   CurrentMenuCur      =1;
   CurrentMenuScroll   =0;
   
   AmendKeyIndex(CurrentMenuIndex);
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuTestEsc(void)
{
   TurnToAboveMenu();
}

void DisMenuTestEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);
}

void DisMenuTestUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))
   {
      CurrentMenuScroll--;
   }

   if(CurrentMenuCur==0)
   {
      CurrentMenuCur++;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}

void DisMenuTestDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();
   
   AmendKeyIndex(CurrentMenuIndex);

   CurrentMenuCur++;
   
   if(CurrentMenuItem<CurrentMenuItemNum)
   {
      CurrentMenuItem++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))
   {
      CurrentMenuScroll++;
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))
   {
      CurrentMenuCur--;
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));
   }
}