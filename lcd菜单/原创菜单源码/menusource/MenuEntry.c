/******************************************************************************
 * MenuEntry.C - 菜单初始化入口及菜单主循环
 *
 * 
 * 2009/12/22, 潘锋，QQ：178122887
 * 
 ******************************************************************************/

#include "menuconfig.h"

//
//the menu node 
//        Prev
//         |
//--Down--Node--Up
//         |
//        Next
//
//esample the menunode list:NodeId rule:the fathernodeid+thisnodelistorder
//--------------------------------------Node2----------------------------------------Node1
//                                        |                                            |
//             Node202-----------------Node201               Node102----------------Node101
//                |                       |                     |                      |
// Node20202---Node20201  Node20102---Node20101  Node10102---Node10201  Node10102---Node10101
//

//--------当前菜单信息
MenuNode MenuNode1 ={1,"1",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode1Action};
MenuNode MenuNode2 ={2,"2",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode2Action};
MenuNode MenuNode101={101,"101",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode101Action};
MenuNode MenuNode102={102,"102",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode102Action};
MenuNode MenuNode103={103,"103",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode103Action};
MenuNode MenuNode201={201,"201",0,(void*)0,(void*)0,(void*)0,(void*)0,MenuNode201Action};

//--------菜单初始化
void MenuListInit(void)
{
   unsigned char i;
   MenuNode *InitMenuNode;
   CurrentMenuNode=&MenuNode1;
   MenuTotalList.Point_Node[0]=&MenuNode1;
   MenuTotalList.Point_Node[1]=&MenuNode2;
   MenuTotalList.Point_Node[2]=&MenuNode101;
   MenuTotalList.Point_Node[3]=&MenuNode102;
   MenuTotalList.Point_Node[4]=&MenuNode103;
   MenuTotalList.Point_Node[5]=&MenuNode201;
   for(i=0;i<MenuTotalNode;i++)
   {
      InitMenuNode=MenuTotalList.Point_Node[i];
      (*InitMenuNode).First_Node=SearchMenuNode((*InitMenuNode).MenuNodeID,firstnode);
      (*InitMenuNode).Last_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,lastnode);
      (*InitMenuNode).Prev_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,prevnode);
      (*InitMenuNode).Next_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,nextnode);
   }
}

//--------菜单主操作
void MenuLoop(unsigned char key)
{
   MenuListInit();
   MenuShow();
   while(1)
   {
      key=KeyGet();
      if(key==0XFF)
        continue;
      switch(CurrentMenuStatus)
      {
         case menufunc:
              switch(key)
              {
                 case keyokcode:break;
                 case key0code:
                 case key1code:
                 case key2code:
                 case key3code:
                 case key4code:
                 case key5code:
                 case key6code:
                 case key7code:
                 case key8code:
                 case key9code:MenuFunctionKey(key);MenuShow();break;
                 case key10code:break;
                 case key11code:if(MenuDeep>0){CurrentMenuStatus=numberfunc;MenuNumberKey(0xff);}break;
                 default:break;
              }
              break;
         case numberfunc:
              switch(key)
              {
                 case keyokcode:break;
                 case key0code:
                 case key1code:
                 case key2code:
                 case key3code:
                 case key4code:
                 case key5code:
                 case key6code:
                 case key7code:
                 case key8code:
                 case key9code:
                 case key10code:MenuNumberKey(key);break;
                 case key11code:CurrentMenuStatus=menufunc;MenuShow();break;
                 default:break;
              }
              break;
         default:break;
      }
      //SysCtlDelay(10*(SysCtlClockGet()/1000));
   }
}