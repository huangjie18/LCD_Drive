/******************************************************************************
 * MenuAction.C - 菜单扩展功能代码
 *
 * 
 * 2009/12/22, 潘锋，QQ：178122887
 * 
 ******************************************************************************/

#include "menuconfig.h"

//--------菜单扩展功能
unsigned char num101=0;
unsigned char tab101[8]={0};
unsigned char num102=0;
unsigned char tab102[8]={0};
unsigned char num103=0;
unsigned char tab103[8]={0};
unsigned char num104=0;
unsigned char tab104[8]={0};
unsigned char num201=0;
unsigned char tab201[8]={0};

void MenuNode1Action(unsigned char key)
{
   
}

void MenuNode2Action(unsigned char key)
{
   
}

void MenuNode101Action(unsigned char key)
{
   Lcd_Clr();
   switch(key)
   {
      case key0code:
      case key1code:
      case key2code:
      case key3code:
      case key4code:
      case key5code:
      case key6code:
      case key7code:
      case key8code:
      case key9code:if(num101<8){tab101[num101]=key;num101++;}break;
      case key10code:if(num101>0){num101--;tab101[num101]=0;}break;
      default:break;
   }
   LCD_Write_String(0,0,"101请输入:");
   LCD_Write_Number(0,1,tab101,num101);
}

void MenuNode102Action(unsigned char key)
{
   Lcd_Clr();
   switch(key)
   {
      case key0code:
      case key1code:
      case key2code:
      case key3code:
      case key4code:
      case key5code:
      case key6code:
      case key7code:
      case key8code:
      case key9code:if(num102<8){tab102[num102]=key;num102++;}break;
      case key10code:if(num102>0){num102--;tab102[num102]=0;}break;
      default:break;
   }
   LCD_Write_String(0,0,"102请输入:");
   LCD_Write_Number(0,1,tab102,num102);
}

void MenuNode103Action(unsigned char key)
{
   Lcd_Clr();
   switch(key)
   {
      case key0code:
      case key1code:
      case key2code:
      case key3code:
      case key4code:
      case key5code:
      case key6code:
      case key7code:
      case key8code:
      case key9code:if(num103<8){tab103[num103]=key;num103++;}break;
      case key10code:if(num103>0){num103--;tab103[num103]=0;}break;
      default:break;
   }
   LCD_Write_String(0,0,"103请输入:");
   LCD_Write_Number(0,1,tab103,num103);
}

void MenuNode104Action(unsigned char key)
{
   Lcd_Clr();
   LCD_Write_String(0,0,"104请输入:");
   LCD_Write_Number(0,1,tab104,num104);
}

void MenuNode201Action(unsigned char key)
{
   Lcd_Clr();
   switch(key)
   {
      case key0code:
      case key1code:
      case key2code:
      case key3code:
      case key4code:
      case key5code:
      case key6code:
      case key7code:
      case key8code:
      case key9code:if(num201<8){tab201[num201]=key;num201++;}break;
      case key10code:if(num201>0){num201--;tab201[num201]=0;}break;
      default:break;
   }
   LCD_Write_String(0,0,"201请输入:");
   LCD_Write_Number(0,1,tab201,num201);
}