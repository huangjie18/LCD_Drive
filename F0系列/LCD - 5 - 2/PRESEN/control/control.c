/* 包含的头文件 --------------------------------------------------------------*/
#include "control.h"
#include "DISPLAY_TFT.h"
#include "key.h"
#include "flash.h"

/* 宏定义 --------------------------------------------------------------------*/
#define   interface_background     black 	 //界面背景
#define   zimo_backgroud           interface_background		 //字模背景
#define   xuan_backgroud           blue		 //选中背景

#define chushihua  1    //进行初始化
/* 变量 ----------------------------------------------------------------------*/
u8 buf_value[15];
//static 变量定义在全局
static uint16 sta=0x0001;
static uint8 putong = 0;//0普通界面，1音量界面
uint8 kai_flag = 0;
uint8 symbol = 1;//1为负数标志，0为正数标志

uint8 mode_volume=0;//音量界面清除设置

static uint8 i=0,mode=1,b=0; //i主界面选中标志;mode界面标志位;b子界面标志位
static uint8 kai_guang=0; //状态开关标志位

static uint8 number_1=0,number_3=0,number_4=0,
number_5=0,number_6=0,number_7=31;

static uint8 volume=50;  //音量

static uint16 number_8=20,number_9=10,number_2=0;	
/*************存放中间变量*************************/
uint16 sta_1=0x0000; //存放进入第二界面的sta变量
uint16 sta_2=0x0000; //存放进入第三界面的sta变量
//可以把number_1~number_9定义成一个结构体
/******************************
volume:音量
number_1:干声比例范围
number_2:湿声比例范围
number_3:立体声范围
number_4:空间大小范围
number_5:衰减程度范围
number_6:延迟时间范围
number_7:回声衰减范围
number_8:低频截止范围
number_9:音调控制范围
******************************/
//i：选中状态位；sta：标志不同模式的界面2和界面3；mode：确定界面
void jiemian(void)
{
	uint16 temp=0;
	static uint16 count1=0;	
	delay_ms(100);
	temp = 	KEY_Scan();
 /*****************************关机*****************************************/
	if(!key6)
	{
	  	count1++;
		if(count1>5)
		{
			count1=0;
			delay_ms(5);
			kai_flag = 0;  //关机标志位，启动关机操作
			BK_OFF;
			POWER_OFF; //关机
		}

	}
/*****************************音量加键功能*****************************************/
	else if(temp==1)
	{
		putong = 1;
		if(volume<100)
		{
			volume++;
		}
		if(mode_volume==0)
		{
		 	display_pic(interface_background);  //清屏
			volume_sub(zimo_backgroud);
			showchar(32,list4_start,20,zimo_backgroud);
			showshuzi(40,list4_start,volume,zimo_backgroud);
			mode_volume = 1;
		}
		else if(mode_volume==1)
		{
			showshuzi(40,list4_start,volume,zimo_backgroud);
		}
	}
/*****************************音量减键功能*****************************************/
	else if(temp==2)
	{
		putong = 1;
		if(volume>0)
		{
			volume--;
		}
		if(mode_volume==0)
		{
		 	display_pic(interface_background);  //清屏
			volume_sub(zimo_backgroud);
			showchar(32,list4_start,20,zimo_backgroud);
			showshuzi(40,list4_start,volume,zimo_backgroud);
			mode_volume = 1;
		}
		else if(mode_volume==1)
		{
			showshuzi(40,list4_start,volume,zimo_backgroud);
		}
	}
/*****************************向上键功能*******************************************/
	else if(temp==3)	    //红色光标向上移动
	{
		if(putong==0)
		{
			shang();
		}	
	}

/***********************************向下键功能*************************************/
	else if(temp==4)  //红色光标向下移动 
	{
		if(putong==0)
		{
			xia();
		}
	}
/***************************确定键************************************************/
	else if(temp==5)	 //确认键
	{
		if(putong==1)
		{
			putong = 0;
			mode_volume=0;
			if(mode==1)
			{
				xuanze_shang_1(&sta,&i);   //返回之前选中的界面1
			}
			else if(mode==2)
			{
			//为什么返回没反应，因为子界面是根据前一个sta来判断的
			//进入子界面后sta已经更改，所以无法实现
				sta = sta_1;  //把存储的sta值取出来作重新写界面的判断值	
				queding_2(); 
			}
			else
			{
			//增加一个存放变量，为了防止退出键影响对界面的刷新
			//如果没有这个变量当2->3->退出->音量->确定时，由于此时sta的值
			//变为2界面，mode=2;而返回2界面的时候是靠1界面的sta来判断的，所以无法显示
				sta = sta_2;
				queding_2();
			}
		}
		else
		{
			queding();
		}
	}
/*****************************退出键***********************************************/
    else if(temp==6)	 //退出键
	{
		if(putong==1)
		{
			putong = 0;
			mode_volume=0;
			if(mode==1)
			{
				xuanze_shang_1(&sta,&i);
			}
			else if(mode==2)
			{
			//为什么返回没反应，因为子界面是根据前一个sta来判断的
			//进入子界面后sta已经更改，所以无法实现
				sta = sta_1;  //把存储的sta值取出来作重新写界面的判断值	
				queding_2(); 
			}
			else
			{
				sta = sta_2;
				queding_2();
			}
		}
		else
		{
			tuichu();
		}
	}
	else
	{
		count1=0;
	}
}
/*************************主界面************************************/
void jiemian1(void)	   //主界面
{
	display_pic(interface_background);	//显示背景
	SetBkColor(0,xuan_backgroud);
	hunxiang(xuan_backgroud);
	huisheng(zimo_backgroud);
	biandiao(zimo_backgroud);
	dipingtisheng(zimo_backgroud);
	gaopingtisheng(zimo_backgroud);
	ganshikaiguang(zimo_backgroud);	
}

void jiemian_hun(uint16 *sta,uint8 *b)	//混响子界面
{
	display_pic(interface_background);  //清屏
	ganshengbili(zimo_backgroud);	//写列表1为干声比例
	shishengbili(zimo_backgroud);	//写列表2为湿声比例和背景
	litishengkuangdu(zimo_backgroud);	  //写列表3为立体声
	kongjiandaxiao(zimo_backgroud);	  //写列表4为空间大小
	shuaijianchengdu(zimo_backgroud);	  //写列表5位衰减程度
	switch_b_hun(sta,b);
}

void jiemian_hui(uint16 *sta,uint8 *b)	  //回声子界面
{
	display_pic(interface_background); //清屏
	yanchishijian(zimo_backgroud);	 //选中延迟时间
	huishengshuaijian(zimo_backgroud); //显示回声衰减
	zhidasheng(zimo_backgroud);		//显示直达声使能
	dipingjiezhi(zimo_backgroud);	//显示低频
	switch_b_hui(sta,b);
}
/*****************************向上键功能*******************************************/
void shang(void)
{
	if(mode==1&&sta)
	{
		if(i==0)
		{
			i=5;
		}
		else
		{
			i--;
		}
		switch_i(&sta,&i);
	}
	else if(mode==2)
	{
		//界面2 混响子选项
		if(sta&0x0001)
		{
			if(b==0)
			{
				b=4;
			}
			else
			{
				b--;
			}
			switch_b_hun(&sta,&b);
		}
		//界面2 回声子选项
		else if(sta&0x0002)
		{
			if(b==0)
			{
				b=3;
			}
			else
			{
				b--;
			}
			switch_b_hui(&sta,&b);
		}
		//修改显示的状态，kai_guang用来标志各个状态:1为开,0为关
		//0x01为低频提升标志位;0x02为高频提升标志位;0x04为干湿开关标志位
		else if((sta&0x0008)|(sta&0x0010)|(sta&0x0020))
		{
			if(sta==0x0008)	//修改低频提升的状态
			{
				if(kai_guang&0x01) //判断低频提升标志位是否为开状态
				{
					kai_guan(zimo_backgroud,2);//修改状态为关
					kai_guang &= 0xfe;	//清除低频提升标志位
				}
				else
				{
					kai_guan(zimo_backgroud,0);	//修改状态为开
					kai_guang |= 0x01;	 //置1低频提升标志位
				}
			}
			else if(sta==0x0010) //修改高频提升的状态
			{
				if(kai_guang&0x02)	//判断高频提升标志位是否为开状态
				{
					kai_guan(zimo_backgroud,2);	 //修改状态为关
					kai_guang &= 0xfd;	   //清除高频提升标志位
				}
				else
				{
					kai_guan(zimo_backgroud,0);
					kai_guang |= 0x02;	 //置1高频提升标志位
				}
			}
			else if(sta==0x0020)  //修改干湿开关的状态
			{
				if(kai_guang&0x04)
				{
					kai_guan(zimo_backgroud,2);	//修改状态为关
					kai_guang &= 0xfb;	 //清除干湿开关标志位
				}
				else
				{
					kai_guan(zimo_backgroud,0);	//修改状态为开
					kai_guang |= 0x04;	 //置1干湿开关标志位
				}
			}
		}

	}
	else if(mode==3)
	{
//		//向上键功能，第三界面
			if(sta&0x0001) //判断是否属于混响的子界面
			{
				if(sta==0x0041)	//判断是否属于干声比例界面
				{
					if(number_1<200) //干声比例的范围为0~200%
					{
						number_1++;
						showshuzi(0,list4_start,number_1,zimo_backgroud);
					}
				}
				else if(sta==0x0081)//判断是否属于湿声比例界面
				{
					if(number_2<300)//范围在0~300%
					{
						number_2++;
						showshuzi(0,list4_start,number_2,zimo_backgroud);
					}
				}
				else if(sta==0x0101)//判断是否属于立体声界面
				{
					if(number_3<100) //范围在0~100%
					{
						number_3++;
						showshuzi(0,list4_start,number_3,zimo_backgroud);
					}
				}
				else if(sta==0x0201) //判断是否属于空间大小界面
				{
					if(number_4<100) //范围在0~100%
					{
						number_4++;
						showshuzi(0,list4_start,number_4,zimo_backgroud);
					}
				}
				else if(sta==0x0401)//判断是否属于衰减程度
				{
					if(number_5<100) //范围在0~100%
					{
						number_5++;
						showshuzi(0,list4_start,number_5,zimo_backgroud);
					}
				}
			}
			else if(sta&0x0002)//判断是否属于回声子界面
			{
				if(sta==0x0802)	//判断是否属于延迟时间界面
				{
					if(number_6<250) //范围在0~250ms
					{
						number_6++;
						showshuzi(0,list4_start,number_6,zimo_backgroud);
					}
				}
				else if(sta==0x1002) //判断是否属于回声衰减界面
				{
					if(number_7>1)	//范围在-31~-1dB
					{
						number_7--;
						showshuzi(8,list4_start,number_7,zimo_backgroud);
						showchar(32,list4_start,13,zimo_backgroud);
					}
				}
				else if(sta==0x2002) //判断是否属于直达声
				{
					if(kai_guang&0x08) //判断此时使能状态标志位是否为1
					{
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xf7;	//清除标志位
					}
					else
					{
						kai_guan(zimo_backgroud,0);	//第二个参数0时,状态为开;2时，状态为关
						kai_guang |= 0x08;	//置1标志位
					}
				}
				else if(sta==0x4002) //判断是否属于低频截止
				{
					if(number_8<20000) //范围在20~20000Hz
					{
						number_8++;
						showshuzi(0,list4_start,number_8,zimo_backgroud);
					}
				}
			}
			else if(sta&0x0004)
			{
				if(symbol==1)  //负数显示
				{
					if(number_9>0)
					{
						number_9--;
						if(number_9==0)
						{
							symbol=1;
							showchar(0,list4_start,19,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
						else
						{
							showchar(0,list4_start,17,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
					}
				}
				else		   //正数显示
				{
					if(number_9<1200)
					{
						number_9++;
					}
					showchar(0,list4_start,19,zimo_backgroud);
					showshuzi(8,list4_start,number_9,zimo_backgroud);
					showchar(40,list4_start,18,zimo_backgroud);
				}
			}
	}
}

/***********************************向下键功能*************************************/
void xia(void)
{
	//主界面
		if(mode==1&&sta)
		{
			i++;
			switch(i)
			{
				case 1:		   //选中回声
					sta = 0x0002;	  
					SetBkColor(list2_start,xuan_backgroud);
					huisheng(xuan_backgroud);
					SetBkColor(list1_start,zimo_backgroud);
					hunxiang(zimo_backgroud);
					break;
				case 2:		  //选中变调
					sta = 0x0004;
					SetBkColor(list3_start,xuan_backgroud);
					biandiao(xuan_backgroud);
					SetBkColor(list2_start,zimo_backgroud);
					huisheng(zimo_backgroud);
					break;
				case 3:		  //选中低频提升
					sta = 0x0008;
					SetBkColor(list4_start,xuan_backgroud);
					dipingtisheng(xuan_backgroud);
					SetBkColor(list3_start,zimo_backgroud);
					biandiao(zimo_backgroud);
					break;
				case 4:		 //选中高频提升
					sta = 0x0010;
					SetBkColor(list5_start,xuan_backgroud);
					gaopingtisheng(xuan_backgroud);
					SetBkColor(list4_start,zimo_backgroud);
					dipingtisheng(zimo_backgroud);
					break;
				case 5:		 //选中干湿开关
					sta = 0x0020;
					SetBkColor(list6_start,xuan_backgroud);
					ganshikaiguang(xuan_backgroud);
					SetBkColor(list5_start,zimo_backgroud);
					gaopingtisheng(zimo_backgroud);
					break;
				case 6:		 //选中混响
					sta = 0x0001;
					SetBkColor(list1_start,xuan_backgroud);
					hunxiang(xuan_backgroud);
					SetBkColor(list6_start,zimo_backgroud);
					ganshikaiguang(zimo_backgroud);
					i=0;
					break;
			}
		}
		//界面2 混响子选项
		if(mode==2)
		{
			b++;
			//混响子选项
			if(sta&0x0001)
			{
				switch(b)
				{
					case 1:
						 //选中湿声比例 
						sta = 0x0081;
						SetBkColor(list2_start,xuan_backgroud);
						shishengbili(xuan_backgroud);
						SetBkColor(list1_start,zimo_backgroud);
						ganshengbili(zimo_backgroud);
						
						break;
					case 2:
						 //选中立体声
						sta = 0x0101;
						SetBkColor(list3_start,xuan_backgroud);
						litishengkuangdu(xuan_backgroud);
						SetBkColor(list2_start,zimo_backgroud);
						shishengbili(zimo_backgroud);
						break;
					case 3:
						//选中空间大小
						sta = 0x0201;
						SetBkColor(list4_start,xuan_backgroud);
						kongjiandaxiao(xuan_backgroud);
						SetBkColor(list3_start,zimo_backgroud);
						litishengkuangdu(zimo_backgroud);
						break;
					case 4:
						//选中衰减程度
						sta = 0x0401;
						SetBkColor(list5_start,xuan_backgroud);
						shuaijianchengdu(xuan_backgroud);
						SetBkColor(list4_start,zimo_backgroud);
						kongjiandaxiao(zimo_backgroud);
						break;
					case 5:
						 //选中干声比例
						sta = 0x0041;
						SetBkColor(list1_start,xuan_backgroud);
						ganshengbili(xuan_backgroud);
						SetBkColor(list5_start,zimo_backgroud);
						shuaijianchengdu(zimo_backgroud);
						b=0;
						break;
						
				}
			}
			//界面2 回声子选项
			else if(sta&0x0002)
			{
				switch(b)
				{
					case 1:
						 //选中回声衰减
						sta = 0x1002; 
						SetBkColor(list2_start,xuan_backgroud);
						huishengshuaijian(xuan_backgroud);
						SetBkColor(list1_start,zimo_backgroud);
						yanchishijian(zimo_backgroud);
						
						break;
					case 2:
						 //选中直达声
						sta = 0x2002;
						SetBkColor(list3_start,xuan_backgroud);
						zhidasheng(xuan_backgroud);
						SetBkColor(list2_start,zimo_backgroud);
						huishengshuaijian(zimo_backgroud);
						break;
					case 3:
						//选中低频截止
						sta = 0x4002;
						SetBkColor(list4_start,xuan_backgroud);
						dipingjiezhi(xuan_backgroud);
						SetBkColor(list3_start,zimo_backgroud);
						zhidasheng(zimo_backgroud);
						break;
					case 4:
						//选中延迟时间
						sta = 0x0802;
						SetBkColor(list1_start,xuan_backgroud);
						yanchishijian(xuan_backgroud);
						SetBkColor(list4_start,zimo_backgroud);
						dipingjiezhi(zimo_backgroud);
						b=0;
						break;
						
				}
			}
		//判断是否属于低频提升，高频提升，干湿开关子界面
			else if((sta&0x0008)|(sta&0x0010)|(sta&0x0020))
			{
				if(sta==0x0008)//判断是否属于低频提升的开关状态
				{
					if(kai_guang&0x01) //判断低频提升开关标志位
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfe; //清除标志位
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x01; //置1标志位
					}
				}
				else if(sta==0x0010) //判断是否属于高频提升的开关状态
				{
					if(kai_guang&0x02) //判断高频提升开关标志位
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfd; //清除标志位
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x02;	//置1标志位
					}
				}
				else if(sta==0x0020) //判断是否属于干湿开关的开关状态
				{
					if(kai_guang&0x04)	//判断标志位
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfb; //清除标志位
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x04; //置1标志位
					}
				}
			}
		}
		else if(mode==3)
		{
		//向下键功能，第三界面实现
			if(sta&0x0001) //判断是否属于混响的第三界面
			{
				if(sta==0x0041)	 //判断是否属于干声比例的第三界面
				{
					if(number_1>0)
					{
						number_1--;
						showshuzi(0,list4_start,number_1,zimo_backgroud);
					}	
				}
				else if(sta==0x0081) //判断是否属于湿声比例的第三界面
				{
					if(number_2>0)
					{
						number_2--;
						showshuzi(0,list4_start,number_2,zimo_backgroud);
					}
				}
				else if(sta==0x0101)//判断是否属于立体声的第三界面
				{
					if(number_3>0)
					{
						number_3--;
						showshuzi(0,list4_start,number_3,zimo_backgroud);
					}
				}
				else if(sta==0x0201) //空间大小
				{
					if(number_4>0)
					{
						number_4--;
						showshuzi(0,list4_start,number_4,zimo_backgroud);
					}
				}
				else if(sta==0x0401) //衰减程度
				{
					if(number_5>0)
					{
						number_5--;
						showshuzi(0,list4_start,number_5,zimo_backgroud);
					}
				}
			}
			//回声第三界面实现
			else if(sta&0x0002)
			{
				if(sta==0x0802)//判断是否属于延迟时间的第三界面
				{
					if(number_6>0)
					{
						number_6--;
						showshuzi(0,list4_start,number_6,zimo_backgroud);
					}	
				}
				else if(sta==0x1002)  //回声衰减
				{
					if(number_7<31)
					{
						number_7++;
						showshuzi(8,list4_start,number_7,zimo_backgroud);
						showchar(32,list4_start,13,zimo_backgroud);
					}
				}
				else if(sta==0x2002)  //直达声
				{
					if(kai_guang&0x08)
					{
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xf7;	
					}
					else 
					{
						kai_guan(zimo_backgroud,0);	//第二个参数0时,状态为开;2时，状态为关
						kai_guang |= 0x08;
					}
				}
				else if(sta==0x4002) //低频截止
				{
					if(number_8>20)
					{
						number_8--;
						qingqu(8,list4_start,zimo_backgroud);
						showshuzi(0,list4_start,number_8,zimo_backgroud);

					}
				}	
			}
		//变调第三界面实现
			else if(sta&0x0004)
			{
				if(symbol==1)  //负数
				{
				tack:
					if(number_9<1200)
					{
						number_9++;
						showchar(0,list4_start,17,zimo_backgroud);
						showshuzi(8,list4_start,number_9,zimo_backgroud);
						showchar(40,list4_start,18,zimo_backgroud);
					}
				}
				else		   //正数
				{
					if(number_9>=0)
					{
						if(number_9==0)	 //保证0属于正数，让向上键正确运行
						{
							symbol = 0;
							goto tack;
						}
						else
						{
							number_9--;
							showchar(0,list4_start,19,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
					}
						
				}
			}
		}
}
/***************************确定键************************************************/
void queding(void)
{
	//先判断在什么界面里，如果在音频界面中，则提取出存起来的sta和mode
	//如果在普通界面里就直接执行程序
		if(mode<4)
		{
			if(mode<2)
			{
				mode++;
			}
			//因为低频提升，高频提升，干湿开关没有第三界面，所以添加控制条件
			else if((sta&0x07c1)|(sta&0x7802)|(sta&0x8004))
			{
				if(mode<3)	  //当mode=2时由第二界面进入第三界面
				{
					mode++;
				}
				else	   //当mode=3时返回第一界面
				{
					mode=1;
					sta = sta_1;
					b=0;
					xuanze_shang_1(&sta,&i);
					mode_volume=0;
	
				}
			}
			else
			{
				mode=1;
				sta = sta_1;
				b=0;
				xuanze_shang_1(&sta,&i);
				mode_volume=0;
			}
			
		}
		queding_2();
}

/*****************************退出键***********************************************/
void tuichu(void)
{
	//根据判断界面标志mode来重新显示图像
	if(mode==1)
	{
	}
	else
	{
		if(mode>1)
		{
			mode--;
		}
		if(mode==1)
		{
			sta = sta_1;
			b=0;
			xuanze_shang_1(&sta,&i);
			mode_volume=0;	
		}
		else if(mode==2)
		{
			sta = sta_2;
			if(sta&0x0001) //混响子界面
			{
				display_pic(interface_background);  //清屏
				ganshengbili(zimo_backgroud);	//写列表1为干声比例
				shishengbili(zimo_backgroud);	//写列表2为湿声比例和背景
				litishengkuangdu(zimo_backgroud);	  //写列表3为立体声
				kongjiandaxiao(zimo_backgroud);	  //写列表4为空间大小
				shuaijianchengdu(zimo_backgroud);  //写列表5位衰减程度
				switch_b_hun(&sta,&b);
			}
			else if(sta&0x0002)	//回声子界面
			{	
				display_pic(interface_background); //清屏
				yanchishijian(zimo_backgroud);	 //选中延迟时间
				huishengshuaijian(zimo_backgroud); //显示回声衰减
				zhidasheng(zimo_backgroud);		//显示直达声使能
				dipingjiezhi(zimo_backgroud);	//显示低频
				switch_b_hui(&sta,&b);
			}
			else if(sta&0x0004)	//变调子界面
			{
				display_pic(interface_background);				
				SetBkColor(0,xuan_backgroud);
				yindiaokongzhi(xuan_backgroud);	
			}	
		}	
	}
	
}

void queding_2(void)	 //界面2和界面3的显示
{
	if(mode==2)	 //界面2  子选项显示实现
	{
		sta_1 = sta;  //把sta存起来用来作音量界面的返回普通界面的判断值
		switch(sta)
		{
		case 0x0001:
			jiemian_hun(&sta,&b); //混响子界面显示
			break;
		case 0x0002:
			jiemian_hui(&sta,&b); //回声子界面显示
			break;
		case 0x0004:   //变调子界面显示
			display_pic(interface_background);
			SetBkColor(0,xuan_backgroud);
			yindiaokongzhi(xuan_backgroud);
			break;
		case 0x0008:  //低频提升
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x01)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);	//第二个参数0时,状态为开;2时，状态为关
			}
			break;
		case 0x0010: //高频提升
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x02)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);
			}
			break;
		case 0x0020:  //干湿开关
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x04)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);
			}
			break;
		}
	}
	//第三界面显示实现
	else if(mode==3)
	{
		sta_2 = sta; //把sta存起来用来作音量界面的返回普通界面的判断值
		display_pic(interface_background);//清屏
		if(sta&0x0001)	//混响第三界面
		{
			if(sta==0x0041)	  //干声比例子界面的第三界面显示
			{
				showshuzi(0,list4_start,number_1,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0081) //湿声比例
			{
				showshuzi(0,list4_start,number_2,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0101) //立体声
			{
				showshuzi(0,list4_start,number_3,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0201) //空间大小
			{
				showshuzi(0,list4_start,number_4,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0401)  //衰减程度
			{
				showshuzi(0,list4_start,number_5,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
		}
		//回声第三界面的显示实现
		else if(sta&0x0002)
		{
			if(sta==0x0802)	//延迟时间
			{
				showshuzi(0,list4_start,number_6,zimo_backgroud);
				showchar(32,list4_start,11,zimo_backgroud);
				showchar(40,list4_start,12,zimo_backgroud);
			}
			else if(sta==0x1002) //回声衰减
			{
				if(number_7==0)
				{
					number_7=1;
				}
				showchar(0,list4_start,17,zimo_backgroud);
				showshuzi(8,list4_start,number_7,zimo_backgroud);
				showchar(32,list4_start,13,zimo_backgroud);
				showchar(40,list4_start,14,zimo_backgroud);
			}
			else if(sta==0x2002) //直达声
			{
				zhuangtaixianshi(zimo_backgroud);
				if(kai_guang&0x08)
				{
					kai_guan(zimo_backgroud,0);
				}
				else
				{
					kai_guan(zimo_backgroud,2);	//第二个参数0时,状态为开;2时，状态为关
				}
			}
			else if(sta==0x4002) //低频截止
			{
				showshuzi(0,list4_start,number_8,zimo_backgroud);
				showchar(40,list4_start,15,zimo_backgroud);
				showchar(48,list4_start,16,zimo_backgroud);
			}
		}
		//变调第三界面显示实现
		else if(sta&0x0004)
		{
			if(symbol==1)
			{
				showchar(0,list4_start,17,zimo_backgroud);
				showshuzi(8,list4_start,number_9,zimo_backgroud);
				showchar(40,list4_start,18,zimo_backgroud);
			}
			else
			{
				showchar(0,list4_start,19,zimo_backgroud);
				showshuzi(8,list4_start,number_9,zimo_backgroud);
				showchar(40,list4_start,18,zimo_backgroud);
			}
		}
	}
}
//*********************************
//*********开机函数****************
//*********************************
void kaiji(void)
{
	unsigned char count=0;
	unsigned char xuan=2;
	u8 buf_value_1[35]; 
	while(!kai_flag)	           //开机循环判断
	{
	 	if(!key6)                      //长短按设置
		{
			count++;
			if(count>5)
			{
				kai_flag=1;
				POWER_ON;
			}
		}
		else
		{
			count = 0;
		}
		delay_ms(500);
	} //跳出开机循环
	
	
	//开机完成后需要把用到的参数初始化
	sta=0x0001;
	putong = 0;
	
	mode_volume = 0;
	i = 0;
	mode = 1;
	b = 0;
	sta_1 = 0x0000;
	FLASH_ReadNWord((uint16_t *)buf_value_1,FLASH_SAVE_ADDR,15);
	//读取存放在eprom中的数据
	if(chushihua)
	{
//		while(xuan--)						   //读取两次，因为读取一次时发现数据有错误
//		{									   //可能优化有问题，所以加多一个循环
			symbol = buf_value_1[14];	 //符号标志读取
			kai_guang = buf_value_1[13];	 //开关标志读取
			volume = buf_value_1[0];	 //音量数据读取
			number_1=buf_value_1[1];	 //干声比例数据读取
			number_3=buf_value_1[2];	 //立体声数据读取
			number_4=buf_value_1[3];	 //空间大小
			number_5=buf_value_1[4];	 //衰减程度
			number_6=buf_value_1[5];	 //延迟时间
			number_7=buf_value_1[6];	 //回声衰减

			number_8=buf_value_1[7];	 //低频截止
			number_8 = (number_8<<8) | buf_value_1[8];

			number_9=buf_value_1[9];	 //音调控制
			number_9 = (number_9<<8) | buf_value_1[10];

			number_2=buf_value_1[11];	 //湿声比例
			number_2 = (number_2<<8) | buf_value_1[12];
//		}
		
	}
			
}
/****************************按键向上显示功能函数********************************/
void xuanze_shang_1(uint16 *sta,uint8 *i)
{
	display_pic(interface_background);	//显示蓝色
	hunxiang(zimo_backgroud);
	huisheng(zimo_backgroud);
	biandiao(zimo_backgroud);
	dipingtisheng(zimo_backgroud);
	gaopingtisheng(zimo_backgroud);
	ganshikaiguang(zimo_backgroud);
	switch_i(sta,i);

}

//对主界面切换函数
void switch_i(uint16 *sta,uint8 *i)
{
	switch(*i)
	{
		case 0:
			*sta = 0x0001;	 //选中混响
			SetBkColor(list2_start,zimo_backgroud);
			huisheng(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			hunxiang(xuan_backgroud);
			*i=0;
			break;
		case 1:
			*sta = 0x0002;	 //选中回声
			SetBkColor(list3_start,zimo_backgroud);
			biandiao(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			huisheng(xuan_backgroud);
			break;
		case 2:
			*sta = 0x0004;	//选中变调
			SetBkColor(list4_start,zimo_backgroud);
			dipingtisheng(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			biandiao(xuan_backgroud);
			break;
		case 3:
			*sta = 0x0008;	//选中低频提升
			SetBkColor(list5_start,zimo_backgroud);
			gaopingtisheng(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			dipingtisheng(xuan_backgroud);
			break;
		case 4:
			*sta = 0x0010;  //选中高频提升
			SetBkColor(list6_start,zimo_backgroud);
			ganshikaiguang(zimo_backgroud);
			SetBkColor(list5_start,xuan_backgroud);
			gaopingtisheng(xuan_backgroud);
			break;
		case 5:
			*sta = 0x0020;   //选中干湿开关
			SetBkColor(list1_start,zimo_backgroud);
			hunxiang(zimo_backgroud);
			SetBkColor(list6_start,xuan_backgroud);
			ganshikaiguang(xuan_backgroud);
			break;
	}
}
	
//对混响子界面切换函数
void switch_b_hun(uint16 *sta,uint8 *b)
{
	switch(*b)
	{
		case 0:
			//选中干声比例
			*sta = 0x0041;
			SetBkColor(list2_start,zimo_backgroud);
			shishengbili(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			ganshengbili(xuan_backgroud);
			*b=0;
			break;
		case 1:
			//选中湿声比例
			*sta = 0x0081;
			SetBkColor(list3_start,zimo_backgroud);
			litishengkuangdu(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			shishengbili(xuan_backgroud);
			break;
		case 2:
			//选中立体声
			*sta = 0x0101;
			SetBkColor(list4_start,zimo_backgroud);
			kongjiandaxiao(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			litishengkuangdu(xuan_backgroud);
			break;
		case 3:
			//选中空间大小
			*sta = 0x0201;
			SetBkColor(list5_start,zimo_backgroud);
			shuaijianchengdu(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			kongjiandaxiao(xuan_backgroud);
			break;
		case 4:
			//选中衰减程度
			*sta = 0x0401;
			SetBkColor(list1_start,zimo_backgroud);
			ganshengbili(zimo_backgroud);
			SetBkColor(list5_start,xuan_backgroud);
			shuaijianchengdu(xuan_backgroud);
			break;
	}
}

void switch_b_hui(uint16 *sta,uint8 *b)
{
	switch(*b)
	{
		case 0:
			//选中延迟时间
			*sta = 0x0802;
			SetBkColor(list2_start,zimo_backgroud);
			huishengshuaijian(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			yanchishijian(xuan_backgroud);
			*b=0;
			break;
		case 1:
			//选中回声衰减幅度
			*sta = 0x1002;
			SetBkColor(list3_start,zimo_backgroud);
			zhidasheng(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			huishengshuaijian(xuan_backgroud);
			break;
		case 2:
			//选中直达声使能
			*sta = 0x2002;
			SetBkColor(list4_start,zimo_backgroud);	
			dipingjiezhi(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			zhidasheng(xuan_backgroud);
			break;
		case 3:
			//选中低频截止频率
			*sta = 0x4002;
			SetBkColor(list1_start,zimo_backgroud);
			yanchishijian(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			dipingjiezhi(xuan_backgroud);
			break;
	}
}


/************************************************
函数名称 ： Write_Flash
功    能 ： 数据保存
参    数 ： 无
返 回 值 ： 无
作    者 ： huangjiehua
*************************************************/
void Write_Flash(void)
{
	u8 data_buf[15];
	data_buf[0] = volume;
	data_buf[1] = number_1;
	data_buf[2] = number_3;
	data_buf[3] = number_4;
	data_buf[4] = number_5;
	data_buf[5] = number_6;
	data_buf[6] = number_7;
	data_buf[7] = number_8>>8;
	data_buf[8] = number_8&0xff;
	data_buf[9] = number_9>>8;
	data_buf[10] = number_9&0xff;
	data_buf[11] = number_2>>8;
	data_buf[12] = number_2&0xff;
	data_buf[13] = kai_guang;
	data_buf[14] = symbol;
//	data_buf[0] = 48;
//	data_buf[1] = 49;
//	data_buf[2] = 50;
//	data_buf[3] = 55;
//	data_buf[4] = 59;
//	data_buf[5] = number_6;
//	data_buf[6] = number_7;
//	data_buf[7] = number_8>>8;
//	data_buf[8] = number_8&0xff;
//	data_buf[9] = number_9>>8;
//	data_buf[10] = number_9&0xff;
//	data_buf[11] = number_2>>8;
//	data_buf[12] = number_2&0xff;
//	data_buf[13] = kai_guang;
//	data_buf[14] = symbol;
	FLASH_WriteNWord((uint16_t *)data_buf,FLASH_SAVE_ADDR,15);
}

