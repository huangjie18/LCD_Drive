#define Key_Esc 	 0x04    //按键编码
#define Key_Enter 	 0x08
#define Key_Up		 0x10
#define Key_Down     0x20

unsigned char KeyFuncIndex			= 0; //按键动作索引
unsigned char MaxScreenDisp			= 4; //屏幕最大显示项

unsigned char CurrentMenuIndex      = 0; //当前菜单索引编号
unsigned char CurrentMenuItem       = 0; //当前菜单项目
unsigned char CurrentMenuItemNum    = 0; //当前菜单项目数
unsigned char **CurrentMenuString   = 0; //当前菜单显示内容指针
unsigned char CurrentMenuCur        = 0; //当前菜单光标在屏幕的位置
unsigned char CurrentMenuScroll     = 0; //当前菜单滚动次数


