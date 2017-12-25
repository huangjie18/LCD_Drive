/******************************************************************************
 * MenuFrame.C - 菜单内核
 *
 * 
 * 2009/12/22, 潘锋，QQ：178122887
 * 
 ******************************************************************************/

#include "menuconfig.h"

//--------菜单内核堆栈
unsigned char CurrentMenuStatus   =0;
unsigned char CurrentMenuCur      =0;
unsigned char MenuDeep            =0;
unsigned char MenuCurStack[MenuStackDeep];

//--------菜单变量
MenuList MenuTotalList;
MenuNode *CurrentMenuNode;

MenuNode *SearchMenuNode(unsigned char nodeid,unsigned char searchtype)
{
   unsigned char i;
   unsigned int  fathernodeid;
   MenuNode *SearchMenuNode;
   MenuNode *ReturnMenuNode=NULL;
   
   fathernodeid=nodeid/100;
   unsigned int searchnodeid=0;
   
   switch(searchtype)
   {
      case firstnode:
           searchnodeid=nodeid-1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case lastnode:
           searchnodeid=nodeid+1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case prevnode:
           searchnodeid=fathernodeid;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case nextnode:
           searchnodeid=nodeid*100+1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      default:break;
   }
   return ReturnMenuNode;
}

//--------查找任一菜单节点
MenuNode *SearchSomeOneMenuNode(unsigned char nodeid)
{
   unsigned char i;
   MenuNode *SearchMenuNode;
   MenuNode *ReturnMenuNode=NULL;
   
   for(i=0;i<MenuTotalNode;i++)
   {
      SearchMenuNode=MenuTotalList.Point_Node[i];
      if((*SearchMenuNode).MenuNodeID==nodeid)
      {
         ReturnMenuNode=SearchMenuNode;
         break;
      }
   }
   return ReturnMenuNode;
}

//--------菜单显示
void MenuShow(void)
{
   unsigned char i;
   static MenuNode *ShowMenuNode;
   switch(CurrentMenuStatus)
   {
      case menufunc:
           Menu_LCD_Clr();
           ShowMenuNode=SearchSomeOneMenuNode((*CurrentMenuNode).MenuNodeID-CurrentMenuCur);
           Menu_LCD_Write_String(0,CurrentMenuCur,"->");
           for(i=0;i<MaxScreenSize;i++)
           {
              Menu_LCD_Write_String(2,i,(*ShowMenuNode).MenuString);
              if((*ShowMenuNode).Last_Node!=NULL)
              {
                 ShowMenuNode=(*ShowMenuNode).Last_Node;
              }
              else
                break;
           }
           break;
      case numberfunc:
           break;
      default:break;
   }
}

//--------菜单索引操作
void MenuFunctionKey(unsigned char key)
{
   MenuIntDisable();
   switch(key)
   {
      case Key_First:
           if((*CurrentMenuNode).First_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).First_Node;
             if(CurrentMenuCur>0)
                CurrentMenuCur--;
           }
           break;
      case Key_Last:
           if((*CurrentMenuNode).Last_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Last_Node;
             if(CurrentMenuCur<(MaxScreenSize-1))
                CurrentMenuCur++;
           }
           break;
      case Key_Prev:
           if((*CurrentMenuNode).Prev_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Prev_Node;
             MenuDeep--;
             CurrentMenuCur=MenuCurStack[MenuDeep];
           }
           break;
      case Key_Next:
           if((*CurrentMenuNode).Next_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Next_Node;
             MenuCurStack[MenuDeep]=CurrentMenuCur;
             CurrentMenuCur=0;
             MenuDeep++;
           }
           break;
      default:break;
   }
   MenuIntEnable();
}

//--------菜单扩展操作功能
void (*MenuNodeAction)(unsigned char key);

//--------菜单按键功能, 扩展功能
void MenuNumberKey(unsigned char key)
{
   MenuIntDisable();
   MenuNodeAction=(*CurrentMenuNode).Action;
   MenuIntEnable();
   (*MenuNodeAction)(key);
}