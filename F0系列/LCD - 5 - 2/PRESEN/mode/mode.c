#include "mode.h"
#include "modefont.h"
#define  x   0		   //定义显示的x起点
#define  y   0		   //定义显示的y起点
  
//uint8 xend,yend;
/**********************调用函数*********************************************/
//num:显示多少个字
void diaoyong(uint8 list_start,uint8 list_end,uint8 num,uint16 bk,const uint8 (*p)[16])
{
	uint8 i,c=0;
	for(i=0;i<num;i++)
	{
		LCD_qu(x+(16*i),y+list_start,(16*i)+15,list_end);
		xianshi(&c,p,32,bk);
		c++;
	}
}
/*******************字模显示函数***************************/
void xianshi(uint8 *c,const uint8 (*p)[16],uint8 num,uint16 bk)
{
	uint8 temp;
	uint8 b,i=0,a;	 //i要赋值为零，否则i的值第二次是8，不会初始为零
	for(b=0;b<num;b++)
	{
		if(i>15)
		{
			i=0;			  //i代表数组中的列数
			(*c)++;			 //c代表数组中的行数
			temp = (*(*(p+*c)+i));	//提取字模数组对应数据
		}
		else
		{
			temp = *(*(p+*c)+i);
		}
		for(a=0;a<8;a++)
		{
			if(temp&(0x01<<a))
			{
				LCD_WR_data(fontcolor>>8,fontcolor&0x00ff);	//写字体颜色
			}
			else
			{
				LCD_WR_data(bk>>8,bk);//写背景色
			}
		}
		i++;
	}
}

#ifdef   hengping     //根据是否定义横屏来创建横屏函数或竖屏函数
#if(zimo==16)		  //创建字模大小为16的显示函数,只是提供一个模板
//以下函数可以去掉i变量来节省内存空间
//列表1显示混响
void  hunxiang(uint16 bk)
{
	diaoyong(list1_start,list1_end,2,bk,hunxian);
}
//列表2显示回声
void huisheng(uint16 bk)
{
	diaoyong(list2_start,list2_end,2,bk,huishen);
}
//列表3显示变调
void biandiao(uint16 bk)
{
	diaoyong(list3_start,list3_end,2,bk,biandia);
}
//列表4显示低频提升
void dipingtisheng(uint16 bk)
{
	diaoyong(list4_start,list4_end,4,bk,diping);
}
//列表5显示高频提升
void gaopingtisheng(uint16 bk)
{
	diaoyong(list5_start,list5_end,4,bk,gaoping);
}
//列表6显示干湿开关
void ganshikaiguang(uint16 bk)
{
	diaoyong(list6_start,list6_end,4,bk,ganshi);
}


#else
void  hunxiang(void)      //创建字模为40的显示函数
{
	uint8 a,i=0,c=0;
	uint8 temp,b;
	LCD_qu(x,y,xend+40-1,yend+40-1);
	xianshi(&c,hunxian,200);

} //写不了响字，因为40+40=80超了64
#endif
#endif

#ifdef  shuping		  //创建竖屏函数
#if(zimo==16)		  //创建字模大小为16的显示函数
void  hunxiang(void)
{
	uint8 c=0;
	LCD_qu(x,y,xend+16-1,yend+16-1);
	xianshi(&c,hunxian,32);
	LCD_qu(x,y+16,xend+15,yend+31);
	c++;
	xianshi(&c,hunxian,32);
}
#else
void  hunxiang(void)	 //创建字模大小为40的显示函数
{
	uint8 c=0;		 
	LCD_qu(x,y,xend+39,yend+39);//在显示屏开启一个局部显示区间
	xianshi(&c,hunxian,200);	//显示第一个字模内容
	LCD_qu(x,y+40,xend+39,yend+79);	//开辟下一个字模显示区间
	c++;				 //提取下一个字模内容
	xianshi(&c,hunxian,200); //显示下一个字模
}
//只需修改传入xianshi函数的字模数组和num，开区自己定义
void huisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,y+0,xend+39,yend+39);
	xianshi(&c,huishen,200);
	LCD_qu(x+0,y+40,xend+39,yend+79);
	c++;
	xianshi(&c,huishen,200);
}

void  biandiao(void)
{
	uint8 c=0;
	LCD_qu(x+0,y+0,xend+39,yend+39);
	xianshi(&c,biandia,200);
	LCD_qu(x+0,y+40,xend+39,yend+79);
	c++;
	xianshi(&c,biandia,200);
}

void  dipingtisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,0,xend+31,31);
	xianshi(&c,diping,128);
	LCD_qu(x+0,32,xend+31,63);
	c++;
	xianshi(&c,diping,128);
	LCD_qu(x+0,64,xend+31,95);
	c++;
	xianshi(&c,diping,128);
	LCD_qu(x+0,96,xend+31,127);
	c++;
	xianshi(&c,diping,128);
}

void  gaopingtisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,0,xend+31,31);
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,32,xend+31,63);
	c++;
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,64,xend+31,95);
	c++;
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,96,xend+31,127);
	c++;
	xianshi(&c,gaoping,128);
}


#endif
#endif

