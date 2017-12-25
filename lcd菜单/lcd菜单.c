#define Key_Esc 	 0x04    //按键编码
#define Key_Enter 	 0x08
#define Key_Up		 0x10
#define Key_Down     0x20

unsigned char KeyFuncIndex			= 0; //按键动作按照ID索引
unsigned char MaxScreenDisp			= 4; //屏幕最大显示项

unsigned char CurrentMenuIndex      = 0; //当前菜单ID
unsigned char CurrentMenuItem       = 0; //当前菜单项目
unsigned char CurrentMenuItemNum    = 0; //当前菜单项目数
unsigned char **CurrentMenuString   = 0; //当前菜单显示内容指针
unsigned char CurrentMenuCur        = 0; //当前菜单光标在屏幕的位置
unsigned char CurrentMenuScroll     = 0; //当前菜单滚动次数

struct Menu
{
	unsigned char MenuID;        //各菜单的ID识别
	unsigned char **MenuTitle;   //菜单的标题
	unsigned char MenuNum;       //菜单的项目数
	unsigned char **MenuIco;     //菜单的图标
	unsigned char **MenuString;  //菜单的显示内容
	void* (*AddAction)();        //菜单动作执行函数
};

unsigned char * TopMenustring[] = {"1.menu", "2.menu", "3.menu", "4.menu", "5.menu",};

struct Menu TopMenu =
{
	0,
	0,
	5,
	0,
	TopMenustring,
	(void*)0,
};

void DispMenu(void)
{
	LCD_write_string(2, 0, "欢迎画面");
}


void AmendKeyIndex(unsigned char menuid)
{
	KeyFuncIndex = menuid;
}

void DisMenuTopInit(void)
{
	unsigned char i, MaxDisp = 0;
	lcd_clr();   //清屏
	CurrentMenuIndex   =  TopMenu.MenuID;   //菜单ID
	CurrentMenuItem    =  1;                //菜单光标指向项目
	CurrentMenuItemNum = TopMenu.MenuNum;   //菜单项目数
	CurrentMenuString  = TopMenu.MenuString;//菜单显示内容
	CurrentMenuCur     = 1;					//光标位置
	CurrentMenuScroll  = 0;                 //滚动次数

	AmendKeyIndex(CurrentMenuIndex);

	if (CurrentMenuItemNum < MaxScreenDisp) //当前菜单项目小于最大屏幕显示项目数
	{
		MaxDisp = CurrentMenuItemNum;
	}
	else
	{
		MaxDisp = MaxScreenDisp;
	}

	LCD_write_string(0, CurrentMenuCur - 1, "->"); //绘制光标
	for (i = 0; i < MaxDisp; i++)
	{
		LCD_write_string(1, i, *(CurrentMenuString + CurrentMenuScroll + i)); //绘制菜单
	}
}

void DisMenuTopEsc(void)
{
	AmendKeyIndex(CurrentMenuIndex);  //修正当前层ID
}

void DisMenuTopEnter(void)
{
	AmendKeyIndex(CurrentMenuIndex);

	switch (CurrentMenuItem)
	{
	case 1:
		lcd_clr();
		TurnToNextMenu(ParaMenu.MenuID);
		break;
	case 2:
		lcd_clr();
		TurnToNextMenu(TimeMenu.MenuID);
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

	default : break;
	}
}


//上键选择
void DisMenuTopUp(void)
{
	unsigned char i, MaxDisp = 0;
	lcd_clr();   //清屏

	AmendKeyIndex(CurrentMenuIndex);  //修正当前层按键ID

	CurrentMenuCur--;

	if (CurrentMenuItem > 1)       //1是当前菜单项，菜单项未到顶，减1
	{
		CurrentMenuItem--;
	}

	if ((CurrentMenuCur == 0) && (CurrentMenuScroll > 0)) //当光标位置到0，并且屏幕还有下滚记录
	{
		CurrentMenuScroll--;  //屏幕向上滚动
	}
	if (CurrentMenuCur == 0) //光标到顶为1，当为0时是用来判断上滚记录的
	{
		CurrentMenuCur++;  //修正光标位置
	}

	if (CurrentMenuItemNum < MaxScreenDisp)
	{
		MaxDisp = CurrentMenuItemNum;
	}
	else
	{
		MaxDisp = MaxScreenDisp;
	}

	LCD_write_string(0, CurrentMenuCur - 1, "->"); //绘光标
	for (i = 0; i < MaxDisp; i++)
	{
		LCD_write_string(1, i, *(CurrentMenuString + CurrentMenuScroll + i)); //绘菜单
	}
}
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
} KeyFuncStruct;

//--------按键索引
KeyFuncStruct KeyTab[] =
{
//  |---------------------------------> Index
//  |  |------------------------------> Esc
//  |  |  |---------------------------> Enter
//  |  |  |  |------------------------> Up
//  |  |  |  |  |---------------------> Down
//  |  |  |  |  |  |------------------> 功能函数
	{ 0, 1, 2, 3, 4, (DisMenuTopInit)}, //-顶层
	{ 1, 0, 0, 0, 0, (DisMenuTopEsc)},
	{ 2, 0, 0, 0, 0, (DisMenuTopEnter)},
	{ 3, 0, 0, 0, 0, (DisMenuTopUp)},
	{ 4, 0, 0, 0, 0, (DisMenuTopDown)},

	{ 5, 6, 7, 8, 9, (DisMenuParaInit)}, //-参数
	{ 6, 0, 0, 0, 0, (DisMenuParaEsc)},
	{ 7, 0, 0, 0, 0, (DisMenuParaEnter)},
	{ 8, 0, 0, 0, 0, (DisMenuParaUp)},
	{ 9, 0, 0, 0, 0, (DisMenuParaDown)},

	{10, 11, 12, 13, 14, (DisMenuTimeInit)}, //-时间
	{11, 0, 0, 0, 0, (DisMenuTimeEsc)},
	{12, 0, 0, 0, 0, (DisMenuTimeEnter)},
	{13, 0, 0, 0, 0, (DisMenuTimeUp)},
	{14, 0, 0, 0, 0, (DisMenuTimeDown)},

	{15, 16, 17, 18, 19, (DisMenuInquireInit)}, //-查询
	{16, 0, 0, 0, 0, (DisMenuInquireEsc)},
	{17, 0, 0, 0, 0, (DisMenuInquireEnter)},
	{18, 0, 0, 0, 0, (DisMenuInquireUp)},
	{19, 0, 0, 0, 0, (DisMenuInquireDown)},

	{20, 21, 22, 23, 24, (DisMenuMessageInit)}, //-信息
	{21, 0, 0, 0, 0, (DisMenuMessageEsc)},
	{22, 0, 0, 0, 0, (DisMenuMessageEnter)},
	{23, 0, 0, 0, 0, (DisMenuMessageUp)},
	{24, 0, 0, 0, 0, (DisMenuMessageDown)},

	{25, 26, 27, 28, 29, (DisMenuTestInit)}, //-测试
	{26, 0, 0, 0, 0, (DisMenuTestEsc)},
	{27, 0, 0, 0, 0, (DisMenuTestEnter)},
	{28, 0, 0, 0, 0, (DisMenuTestUp)},
	{29, 0, 0, 0, 0, (DisMenuTestDown)},
};
//进入下一层菜单
void TurnToNextMenu(unsigned char menuid)
{
	PushMenuStack();
	KeyFuncPtr = KeyTab[menuid].CurrenOperate;  //获得对应初始化函数
	(*KeyFuncPtr)();  //执行初始化函数
}
//返回上一层菜单
void TurnToAboveMenu(void)
{
	PopMenuStack();
	ReDrawScreen();  //屏幕重画
}

//重绘屏幕
void ReDrawScreen(void)
{
	unsigned char i, MaxDisp = 0;
	lcd_clr(); //清屏

	if (CurrentMenuItemNum < MaxScreenDisp)
	{
		MaxDisp = CurrentMenuItemNum;
	}
	else
	{
		MaxDisp = MaxScreenDisp;
	}

	LCD_write_string(0, CurrentMenuCur - 1, "->");

	for (i = 0; i < MaxDisp; i++)
	{
		LCD_write_string(1, i, *(CurrentMenuString + CurrentMenuScroll + 1)); //返回上一层画面，要注意是否有滚动
	}
}
unsigned char MenuDeep            = 0;      //当前菜单堆栈深度
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
//当前菜单入栈
void PushMenuStack(void)
{
	MenuDeep++;
	MenuDeepStack[MenuDeep].MenuStackIndex 			= CurrentMenuIndex;   //当前菜单ID
	MenuDeepStack[MenuDeep].MenuStackItem 			= CurrentMenuItem;    //当前菜单项目
	MenuDeepStack[MenuDeep].MenuStackItemNum 		= CurrentMenuItemNum; //当前菜单层项目数
	MenuDeepStack[MenuDeep].MenuStackString 		= CurrentMenuString;  //当前菜单层显示内容
	MenuDeepStack[MenuDeep].MenuStackCur 			= CurrentMenuCur;     //当前菜单层光标位置
	MenuDeepStack[MenuDeep].MenuStackScroll 		= CurrentMenuScroll;  //当前菜单层滚动次数

}

//返回上层菜单，菜单出栈
void PopMenuStack(void)
{
	CurrentMenuIndex   = MenuDeepStack[MenuDeep].MenuStackIndex;
	CurrentMenuItem    = MenuDeepStack[MenuDeep].MenuStackItem;
	CurrentMenuItemNum = MenuDeepStack[MenuDeep].MenuStackItemNum;
	CurrentMenuString  = MenuDeepStack[MenuDeep].MenuStackString;
	CurrentMenuCur     = MenuDeepStack[MenuDeep].MenuStackCur;
	CurrentMenuScroll  = MenuDeepStack[MenuDeep].MenuStackScroll;
	KeyFuncIndex       = CurrentMenuIndex;
	MenuDeep--;
}

void DisMenuTopDown(void)
{
	unsigned char i, MaxDisp = 0;
	lcd_clr();                                    //清屏

	AmendKeyIndex(CurrentMenuIndex);              //修正当前层按键索引

	CurrentMenuCur++;                             //光标向下

	if (CurrentMenuItem < CurrentMenuItemNum)     //当前项小于当前菜单层最大项目数
	{
		CurrentMenuItem++;                         //当前层项加一
	}

	if ((CurrentMenuCur == (MaxScreenDisp + 1)) && (CurrentMenuScroll + MaxScreenDisp < CurrentMenuItemNum)) //光标到过了屏幕顶, 显示项目数还没有到顶
	{
		CurrentMenuScroll++;                        //屏幕滚动一行, 显示当前所选项
	}

	if ((CurrentMenuCur == (MaxScreenDisp + 1)) || (CurrentMenuCur == (CurrentMenuItemNum + 1))) //当光标过了屏幕顶, 或光标过了当前最大菜单项数
	{
		CurrentMenuCur--;                           //修正光标位置
	}

	if (CurrentMenuItemNum < MaxScreenDisp)        //当前层菜单项目数小于屏幕最大显示项数
	{
		MaxDisp = CurrentMenuItemNum;               //屏扫描项数为当前层菜单项数
	}
	else
	{
		MaxDisp = MaxScreenDisp;                    //屏扫描项数为屏幕最大显示项数
	}

	LCD_write_string(0, CurrentMenuCur - 1, "->"); //绘光标
	for (i = 0; i < MaxDisp; i++)
	{
		LCD_write_string(1, i, *(CurrentMenuString + CurrentMenuScroll + i)); //绘菜单
	}
}


void OnKey(unsigned char key)
{
	switch (key)
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

	default : break;
	}
}


//总结：LCD菜单实现有循环方式：循环查表；查询方式：链表；状态机方式：状态机；
//该例程使用方式： 循环方式；
//逻辑：这个对按键处理的事件分派其实是利用数组来进行动作函数分派
//实现：对于界面的写可以参考该代码的结构体来做，有面向对象的做法
