#include "para.h"
#include "parafont.h"


#if(parazimo==16)
//以下函数可以去掉i变量对LCD_qu可直接定义数字不用变量节省内存空间
//以下是各选项的显示函数
/************************混响选项*******************************************/
void ganshengbili(uint16 bk)
{
	diaoyong(list1_start,list1_end,4,bk,gansheng);
}
//列表2显示湿声比例
void shishengbili(uint16 bk)
{
	diaoyong(list2_start,list2_end,4,bk,shisheng);
}
//列表3显示立体声宽度
void litishengkuangdu(uint16 bk)
{
	diaoyong(list3_start,list3_end,3,bk,litisheng);
}
//列表4显示空间大小
void kongjiandaxiao(uint16 bk)
{
	diaoyong(list4_start,list4_end,4,bk,kongjian);
}
//列表5显示衰减程度
void shuaijianchengdu(uint16 bk)
{
	diaoyong(list5_start,list5_end,4,bk,shuaijian);
}	

/***********************回声选项*****************************/
void yanchishijian(uint16 bk)   //延迟时间
{
	diaoyong(list1_start,list1_end,4,bk,yanchi);
}

void huishengshuaijian(uint16 bk) //回声衰减幅度
{
	diaoyong(list2_start,list2_end,4,bk,huishengshuai);
}

void zhidasheng(uint16 bk)		  //直达声使能
{
	diaoyong(list3_start,list3_end,3,bk,zhida);
}

void dipingjiezhi(uint16 bk)	  //低频截止
{
	diaoyong(list4_start,list4_end,4,bk,dipingjie);
}


/*********************变调选项***********************************/
void yindiaokongzhi(uint16 bk)
{
	diaoyong(list1_start,list1_end,4,bk,yindiaokong);
}

/********************低频提升选项******************************/
void zhuangtaixianshi(uint16 bk)
{
	diaoyong(list4_start,list4_end,3,bk,zhuangtai);
}

void kai_guan(uint16 bk,uint8 c)   //c语言中不能在参数中直接赋默认值，
{
	//c=0代表开;c=2代表关
    LCD_qu((16*3),list4_start,(16*3)+15,list4_end);
	xianshi(&c,kaiguang,32,bk);
}
#endif
