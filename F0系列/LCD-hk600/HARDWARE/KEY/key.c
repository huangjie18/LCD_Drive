/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： key.c
  * @作者       ： JieHuaHuang
  * @库版本     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年10月23
  * @摘要       ： 主函数 - 按键扫描
                   得到每个按键的键值
  ******************************************************************************/


/* 包含的头文件 --------------------------------------------------------------*/
#include "key.h"

u8 g_key_value[3][2]=
{
	1,  2,
	3,  4,
	5,  6,
};
/************************************************
函数名称 ： KEY_Init
功    能 ： 对按键对应引脚初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void KEY_Init(void)
{
	/////////////////上拉输入要配置ODR寄存器////////////////////////////
/////////////////////配置模拟输入和上拉//////////////////////////////////////
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC->AHBENR |= 1<<17;//开启GPIOA时钟
	RCC->AHBENR |= 1<<18;//开启GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                     //PA15引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                   //输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PB引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_7;         //PB3，4引脚输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置输出引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIOB
	
	//电源键
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化PA10
	
}

/************************************************
函数名称 ： KEY_Scan
功    能 ： 按键扫描
参    数 ： 无
返 回 值 ： 按键值
*************************************************/

u8 KEY_Scan(void)
{
	u8 scan_num=0; //扫描次数
	key5_Set;      //PB5=1
	key4_Set;      //PB6=1
	
	for(scan_num=0;scan_num<3;scan_num++)
	{
		switch(scan_num)
		{
			case 0: key4_Reset; key5_Set; break;
			case 1: key5_Reset; key4_Set; break;
			default: break;
		}
		
		if((!key1)||(!key2)||(!key3))   //有按键按下
		{
			if(!key1)
			{
				return g_key_value[0][scan_num];   //返回键值
			}
			else if(!key2)
			{
				return g_key_value[1][scan_num];
			}
			else if(!key3)
			{
				return g_key_value[2][scan_num];
			}
		} //end of if
		
	} //end of for
	
	return 0;  //按键没按下就返回0
}
