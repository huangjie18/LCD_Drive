#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

/****小小调度器开始**********************************************/
#define MAXTASKS 3
volatile unsigned char timers[MAXTASKS];
#define _SS static unsigned char _lc=0; switch(_lc){default: 
#define _EE ;}; _lc=0; return 255;

#define WaitX(tickets)  do { _lc=(__LINE__%255)+1; return tickets ;case (__LINE__%255)+1:;} while(0);
#define WaitUntil(A)    do { while(!A) WaitX(1);} while(0);

#define RunTask(TaskName,TaskID)  do { if (timers[TaskID]==0) timers[TaskID]=TaskName(); }  while(0); 
#define RunTaskA(TaskName,TaskID) do { if (timers[TaskID]==0) {timers[TaskID]=TaskName(); continue;}}while(0);   //前面的任务优先保证执行

#define CallSub(SubTaskName) do {unsigned char currdt; _lc=(__LINE__%255)+1; return 0; case (__LINE__%255)+1:  currdt=SubTaskName(); if(currdt!=255) return currdt;} while(0);
#define InitTasks() do {unsigned char i; for(i=MAXTASKS;i>0 ;i--) timers[i-1]=0; } while(0);
#define UpdateTimers() do{unsigned char i; for(i=MAXTASKS;i>0 ;i--){if((timers[i-1]!=0)&&(timers[i-1]!=255)) timers[i-1]--;}} while(0);

#define SEM unsigned int 
//初始化信号量
#define InitSem(sem) do{sem=0;}while(0);
//等待信号量
#define WaitSem(sem) do{ sem=1; WaitX(0); if (sem>0) return 1;} while(0);
//发送信号量
#define SendSem(sem)  do {sem=0;} while(0);

/*****小小调度器结束*******************************************************/
//LCD对象
typedef struct _LCD
{
	u16 width;     //lcd宽度
	u16 height;    //lcd高度
	u16 wramcmd;   //写gram指令
	u16 setxcmd;   //设置x坐标指令
	u16 setycmd;   //设置y坐标指令
}_LCD;
//创建lcd实例5510
_LCD LCD_5510=
{
	480,
	800,
	0X2C00,
	0X2A00,
	0X2B00,
};
#define CLASS(type) \
typedef struct type type; \
struct type
	


u8 LCD_D = 0;
int main(void)
{	
	u16 i=0,j=0;
	delay_init(168);	    //延时函数初始化	
	GPIO_5510_Init();
	LCD_Init();
	LCD_Clear(0);
	while(1)
	{
		if(i>=480)
		{
			i=0;
		}
		if(i/10==0)
		{
			LCD_D = 1;
		}
		else
		{
			LCD_D = 0;
		}
		if(LCD_D==0)
		{
			LCD_WR_REG(0X2A00);
			LCD_WR_DATA(i>>8);
			LCD_WR_REG(0X2A01);
			LCD_WR_DATA(i&0xff);
			LCD_WR_REG(0X2B00);
			LCD_WR_DATA(0);
			LCD_WR_REG(0X2B01);
			LCD_WR_DATA(0xff);
			LCD_WR_REG(0X2C00);
			LCD_WR_DATA(red);
			
			
			LCD_WR_REG(0X2A00);
			LCD_WR_DATA(i>>8);
			LCD_WR_REG(0X2A01);
			LCD_WR_DATA(i&0xff);
			LCD_WR_REG(0X2B00);
			LCD_WR_DATA(0);
			LCD_WR_REG(0X2B01);
			LCD_WR_DATA(0x0f);
			LCD_WR_REG(0X2C00);
			LCD_WR_DATA(0);
		}
		else
		{
			LCD_WR_REG(0X2A00);
			LCD_WR_DATA(i>>8);
			LCD_WR_REG(0X2A01);
			LCD_WR_DATA(i&0xff);
			LCD_WR_REG(0X2B00);
			LCD_WR_DATA(0);
			LCD_WR_REG(0X2B01);
			LCD_WR_DATA(0x0f);
			LCD_WR_REG(0X2C00);
			LCD_WR_DATA(red);
			
			LCD_WR_REG(0X2A00);
			LCD_WR_DATA(i>>8);
			LCD_WR_REG(0X2A01);
			LCD_WR_DATA(i&0xff);
			LCD_WR_REG(0X2B00);
			LCD_WR_DATA(0);
			LCD_WR_REG(0X2B01);
			LCD_WR_DATA(0xff);
			LCD_WR_REG(0X2C00);
			LCD_WR_DATA(0);
		}
		i++;
	}
}


