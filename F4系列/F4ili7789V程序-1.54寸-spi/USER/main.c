#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "spi.h"
#include "timer.h"


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
	

u32 time_lcd=0; //用来计算刷屏时间
u8 LCD_D = 0;
int main(void)
{	
	u16 i=0,j=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);	    //延时函数初始化	
	uart_init(115200);	 //串口初始化为115200
	GPIO_5510_Init();       //引脚初始化 
	SPI1_Init();           //SPI初始化
	LCD_Init();
	LCD_Init();
//	LCD_Clear(blue);      //IO测试
	display_test();       //spi测试
	
	
//	TIM3_Int_Init(5000-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms
	TIM3_Int_Init(999,84-1);//定时1ms
	
	
	while(1)
	{
//		LCD_Clear(blue);
		//红色
		time_lcd = 0;
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(RED>>8);
				LCD_WR_DATA(RED&0xff);
			}
		}
		printf("RED刷屏时间为:%d\r\n",time_lcd);
		time_lcd = 0;
		delay_ms(300);
		//绿色
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(GREEN>>8);
				LCD_WR_DATA(GREEN&0xff);
			}
		}
		printf("GREEN刷屏时间为:%d\r\n",time_lcd);
		time_lcd = 0;
		delay_ms(300);
		//蓝色
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(BLUE>>8);
				LCD_WR_DATA(BLUE&0xff);
			}
		}
		printf("\r\nBLUE刷屏时间为:%d\r\n",time_lcd);
		delay_ms(300);
	}
}


