
#include "G:\lm3s\lcd\menu.h"               //包含底层头文件
#include "G:\lm3s\lcd\lcd.h"

//------------------------------------------------------------------------------------
//                          菜单数据采用数据动态链接的方式
//------------------------------------------------------------------------------------
//       欢迎画面          |         进入子层             |      子层返回上层
//           |             |             |                |           |
//  初始化第一屏数据及画面 | 保存当前层状态(状态数据入栈) | 恢复上层状态(状态数据出栈)
//           |             |             |                |           |
//    进入第一层画面       |    初始化子层数据及画面      |     重绘上层状态画面
//           |             |             |                |           |
// 进入第一层按键事件检测  |    进入子层按键事件检测      |   进入子层按键事件检测
//   |     |    |    |     |     |     |    |    |        |    |     |    |    | 
//  Esc  Enter  Up  Down   |    Esc  Enter  Up  Down      |   Esc  Enter  Up  Down 
//   |     |    |    |     |     |     |    |    |        |    |     |    |    |  
// 退出  进入  屏幕 屏幕   |    退出  进入  屏幕 屏幕     |  退出  进入  屏幕 屏幕 
// 本层  光标  向上 向下   |    本层  光标  向上 向下     |  本层  光标  向上 向下 
//       选定  滚动 滚动   |    返回  选定  滚动 滚动     |  返回  选定  滚动 滚动 
//       的层              |    上层  的层                |  上层  的层      
//
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

#define Key_Esc        0x04                 //定义按键编码
#define Key_Enter      0x08
#define Key_Up         0x10
#define Key_Down       0x20

//--------------------------------------------------------
unsigned char KeyFuncIndex        =0;       //按键动作索引

unsigned char MaxScreenDisp       =4;       //屏幕最大显示项

//--------------------------------------------------------
unsigned char CurrentMenuIndex    =0;       //当前菜单索引编号
unsigned char CurrentMenuItem     =0;       //当前菜单项目
unsigned char CurrentMenuItemNum  =0;       //当前菜单项目数
unsigned char **CurrentMenuString =0;       //当前菜单显示内容指针
unsigned char CurrentMenuCur      =0;       //当前菜单光标在屏幕的位置
unsigned char CurrentMenuScroll   =0;       //当前菜单滚动次数

//--------------------------------------------------------
unsigned char MenuDeep            =0;       //当前菜单堆栈深度

//-------------------------------------------------------- 用户菜单显示内容
//--------顶层内容
unsigned char * TopMenuString[]     ={"1.menu","2.menu","3.menu","4.menu","5.menu",};
//--------系统参数层内容
unsigned char * ParaMenuString[]    ={"1.1menu","1.2menu","1.3menu","1.4menu","1.5menu","1.6menu","1.7menu","1.8menu","1.9menu","1.10menu",};
//--------系统时间层内容
unsigned char * TimeMenuString[]    ={"2.1menu","2.2menu","2.3menu","2.4menu","2.5menu",};
//--------系统查询层内容
unsigned char * InquireMenuString[] ={"3.1menu","3.2menu","3.3menu","3.4menu","3.5menu",};
//--------系统信息层内容
unsigned char * MessageMenuString[] ={"4.1menu","4.2menu","4.3menu","4.4menu","4.5menu",};
//--------系统测试层内容
unsigned char * TestMenuString[]    ={"5.1menu","5.2menu","5.3menu","5.4menu","5.5menu",};

//---------------------------------------------------------
//--------菜单结构体
//--------菜单的ID, 也就是菜单的索引号, 是各菜单顺利链接的节点
//--------菜单的标题,
//--------菜单的项目数
//--------菜单的图标
//--------菜单的显示内容
//--------菜单动作执行函数
struct Menu
{
   unsigned char MenuID;
   unsigned char **MenuTitle;
   unsigned char MenuNum;
   unsigned char **MenuIco;
   unsigned char **MenuString;
   void* (*AddAction)();
};

//--------顶层菜单
struct Menu TopMenu=
{
   0,
   0,
   5,
   0,
   TopMenuString,
   (void*)0,
};

//--------系统参数层菜单
struct Menu ParaMenu=
{
   5,
   0,
   10,
   0,
   ParaMenuString,
   (void*)0,
};

//---------系统时间层菜单
struct Menu TimeMenu=
{
   10,
   0,
   5,
   0,
   TimeMenuString,
   (void*)0,
};

//--------系统查询层菜单
struct Menu InquireMenu=
{
   15,
   0,
   5,
   0,
   InquireMenuString,
   (void*)0,
};

//--------系统信息层菜单
struct Menu MessageMenu=
{
   20,
   0,
   5,
   0,
   MessageMenuString,
   (void*)0,
};

//--------系统测试层菜单
struct Menu TestMenu=
{
   25,
   0,
   5,
   0,
   TestMenuString,
   (void*)0,
};

//------------------------------------------------------------菜单内核
//--------菜单重绘, 返回上层时调用
void ReDrawScreen(void);

//--------菜单堆栈
//--------菜单ID, 也就是索引号
//--------菜单项
//--------菜单项目数
//--------菜单显示内容
//--------光标位置
//--------菜单滚动次数
struct MenuStack
{
   unsigned char MenuStackIndex;
   unsigned char MenuStackItem;
   unsigned char MenuStackItemNum;
   unsigned char **MenuStackString;
   unsigned char MenuStackCur;
   unsigned char MenuStackScroll;
};

//--------菜单堆栈初始化
struct MenuStack MenuDeepStack[10];

//--------当前菜单入栈
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

//--------返回上层菜单, 菜单出栈
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

//--------顶层菜单操作
void DisMenuTopInit(void);
void DisMenuTopEsc(void);
void DisMenuTopEnter(void);
void DisMenuTopUp(void);
void DisMenuTopDown(void);

//--------系统参数层操作
void DisMenuParaInit(void);
void DisMenuParaEsc(void);
void DisMenuParaEnter(void);
void DisMenuParaUp(void);
void DisMenuParaDown(void);

//--------系统时间层操作
void DisMenuTimeInit(void);
void DisMenuTimeEsc(void);
void DisMenuTimeEnter(void);
void DisMenuTimeUp(void);
void DisMenuTimeDown(void);

//--------系统查询层操作
void DisMenuInquireInit(void);
void DisMenuInquireEsc(void);
void DisMenuInquireEnter(void);
void DisMenuInquireUp(void);
void DisMenuInquireDown(void);

//--------系统信息层操作
void DisMenuMessageInit(void);
void DisMenuMessageEsc(void);
void DisMenuMessageEnter(void);
void DisMenuMessageUp(void);
void DisMenuMessageDown(void);

//--------系统测试层操作
void DisMenuTestInit(void);
void DisMenuTestEsc(void);
void DisMenuTestEnter(void);
void DisMenuTestUp(void);
void DisMenuTestDown(void);

//--------当前层菜单操作函数
void (*KeyFuncPtr)();

//--------按键操作结构体
//--------按键--菜单索引号--操作, 用来初始化本层菜单
//--------按键返回操作
//--------按键进入操作
//--------按键向上操作
//--------按键向下操作
//--------按键动作执行函数
typedef struct 
{
   unsigned char KeyStateIndex;
   unsigned char KeyEscState;
   unsigned char KeyEnterState;
   unsigned char KeyUpState;
   unsigned char KeyDownState;
   void (*CurrentOperate)();
}KeyFuncStruct;

//--------按键索引
KeyFuncStruct KeyTab[]=
{   
//  |---------------------------------> Index
//  |  |------------------------------> Esc
//  |  |  |---------------------------> Enter
//  |  |  |  |------------------------> Up
//  |  |  |  |  |---------------------> Down
//  |  |  |  |  |  |------------------> 功能函数
  { 0, 1, 2, 3, 4,(DisMenuTopInit)}, //-顶层
  { 1, 0, 0, 0, 0,(DisMenuTopEsc)},
  { 2, 0, 0, 0, 0,(DisMenuTopEnter)},
  { 3, 0, 0, 0, 0,(DisMenuTopUp)},
  { 4, 0, 0, 0, 0,(DisMenuTopDown)},
  
  { 5, 6, 7, 8, 9,(DisMenuParaInit)}, //-参数
  { 6, 0, 0, 0, 0,(DisMenuParaEsc)},
  { 7, 0, 0, 0, 0,(DisMenuParaEnter)},
  { 8, 0, 0, 0, 0,(DisMenuParaUp)},
  { 9, 0, 0, 0, 0,(DisMenuParaDown)},
  
  {10,11,12,13,14,(DisMenuTimeInit)}, //-时间
  {11, 0, 0, 0, 0,(DisMenuTimeEsc)},
  {12, 0, 0, 0, 0,(DisMenuTimeEnter)},
  {13, 0, 0, 0, 0,(DisMenuTimeUp)},
  {14, 0, 0, 0, 0,(DisMenuTimeDown)},
  
  {15,16,17,18,19,(DisMenuInquireInit)}, //-查询
  {16, 0, 0, 0, 0,(DisMenuInquireEsc)},
  {17, 0, 0, 0, 0,(DisMenuInquireEnter)},
  {18, 0, 0, 0, 0,(DisMenuInquireUp)},
  {19, 0, 0, 0, 0,(DisMenuInquireDown)},
  
  {20,21,22,23,24,(DisMenuMessageInit)}, //-信息
  {21, 0, 0, 0, 0,(DisMenuMessageEsc)},
  {22, 0, 0, 0, 0,(DisMenuMessageEnter)},
  {23, 0, 0, 0, 0,(DisMenuMessageUp)},
  {24, 0, 0, 0, 0,(DisMenuMessageDown)},
  
  {25,26,27,28,29,(DisMenuTestInit)}, //-测试
  {26, 0, 0, 0, 0,(DisMenuTestEsc)},
  {27, 0, 0, 0, 0,(DisMenuTestEnter)},
  {28, 0, 0, 0, 0,(DisMenuTestUp)},
  {29, 0, 0, 0, 0,(DisMenuTestDown)},
};

//--------按键动作
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

//--------进入下一层菜单
void TurnToNextMenu(unsigned char menuid)
{
   PushMenuStack();
   KeyFuncPtr   = KeyTab[menuid].CurrentOperate;
   (*KeyFuncPtr)();
}

//--------返回上一层菜单
void TurnToAboveMenu(void)
{
   PopMenuStack();
   ReDrawScreen();
}

//--------修正本层菜单按键索引
void AmendKeyIndex(unsigned char menuid)
{
   KeyFuncIndex = menuid;
}

//--------屏幕重绘, 菜单返回时调用
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

//----------------------------------------------------------- 菜单操作
//--------欢迎画面
void DispMenu(void)
{
   LCD_write_string(2,0,"欢迎画面");
}

//--------顶层初始化, 在每层的初始只有在进入这个菜单时初始化
void DisMenuTopInit(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                                    //清屏

   CurrentMenuIndex    = TopMenu.MenuID;         //变量初始化
   CurrentMenuItem     = 1;
   CurrentMenuItemNum  = TopMenu.MenuNum;
   CurrentMenuString   = TopMenu.MenuString;
   CurrentMenuCur      = 1;
   CurrentMenuScroll   = 0;

   AmendKeyIndex(CurrentMenuIndex);             //修正当前层按键索引
   
   if(CurrentMenuItemNum<MaxScreenDisp)         //当前层项目数小于最大屏幕显示数
   {
      MaxDisp = CurrentMenuItemNum;
   }
   else
   {
      MaxDisp = MaxScreenDisp;
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");    //绘光标
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));    //绘菜单
   }
}

void DisMenuTopEsc(void)
{
   AmendKeyIndex(CurrentMenuIndex);       //修正当前层按键索引
}
void DisMenuTopEnter(void)
{
   AmendKeyIndex(CurrentMenuIndex);       //修正当前层按键索引
   
   switch(CurrentMenuItem)                //进入下层菜单
   {
      case 1:
           lcd_clr();
           TurnToNextMenu(ParaMenu.MenuID);   //进入参数子菜单
           break;
           
      case 2:
           TurnToNextMenu(TimeMenu.MenuID);   //进入时间子菜单
           break;
           
      case 3:
           TurnToNextMenu(InquireMenu.MenuID);  //进入查询子菜单
           break;
           
      case 4:
           TurnToNextMenu(MessageMenu.MenuID);  //进入信息子菜单
           break;
           
      case 5:
           TurnToNextMenu(TestMenu.MenuID);   //进入测试子菜单
           break;
           
      default :break;
   }
}

void DisMenuTopUp(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                           //清屏
   
   AmendKeyIndex(CurrentMenuIndex);     //修正当前层按键索引

   CurrentMenuCur--;
   
   if(CurrentMenuItem>1)                //1是当前菜单项的顶, 菜单项未到顶, 减一
   {
      CurrentMenuItem--;
   }
   
   if((CurrentMenuCur==0)&&(CurrentMenuScroll>0))  //当光标的位置到0, 并且屏幕还有向下滚动记录
   {
      CurrentMenuScroll--;                         //屏幕向上滚动
   }

   if(CurrentMenuCur==0)                           //1是光标的顶, 当光标为0时
   {
      CurrentMenuCur++;                            //修正光标位置
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)            //当前层菜单项目数小于屏幕最大显示项数
   {
      MaxDisp = CurrentMenuItemNum;                //屏扫描项数为当前层菜单项数
   }
   else
   {
      MaxDisp = MaxScreenDisp;                     //屏扫描项数为屏幕最大显示项数
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");      //绘光标
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));    //绘菜单
   }
}   

void DisMenuTopDown(void)
{
   unsigned char i,MaxDisp=0;
   lcd_clr();                                    //清屏
   
   AmendKeyIndex(CurrentMenuIndex);              //修正当前层按键索引

   CurrentMenuCur++;                             //光标向下
   
   if(CurrentMenuItem<CurrentMenuItemNum)        //当前项小于当前菜单层最大项目数
   {
      CurrentMenuItem++;                         //当前层项加一
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))&&(CurrentMenuScroll+MaxScreenDisp<CurrentMenuItemNum))      //光标到过了屏幕顶, 显示项目数还没有到顶 
   {
      CurrentMenuScroll++;                        //屏幕滚动一行, 显示当前所选项
   }
   
   if((CurrentMenuCur==(MaxScreenDisp+1))||(CurrentMenuCur==(CurrentMenuItemNum+1)))       //当光标过了屏幕顶, 或光标过了当前最大菜单项数
   {
      CurrentMenuCur--;                           //修正光标位置
   }
   
   if(CurrentMenuItemNum<MaxScreenDisp)           //当前层菜单项目数小于屏幕最大显示项数
   {
      MaxDisp = CurrentMenuItemNum;               //屏扫描项数为当前层菜单项数
   }
   else
   {
      MaxDisp = MaxScreenDisp;                    //屏扫描项数为屏幕最大显示项数
   }
   
   LCD_write_string(0,CurrentMenuCur-1,"->");     //绘光标
   for(i=0;i<MaxDisp;i++)
   {
      LCD_write_string(1,i,*(CurrentMenuString+CurrentMenuScroll+i));   //绘菜单
   }
}

//----------------------------------------------------
//--------系统参数层
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
//-------系统时间
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
//--------系统查询
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
//-------系统信息
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
//--------系统测试
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