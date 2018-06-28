#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "spi.h"
#include "timer.h"


/****СС��������ʼ**********************************************/
#define MAXTASKS 3
volatile unsigned char timers[MAXTASKS];
#define _SS static unsigned char _lc=0; switch(_lc){default: 
#define _EE ;}; _lc=0; return 255;

#define WaitX(tickets)  do { _lc=(__LINE__%255)+1; return tickets ;case (__LINE__%255)+1:;} while(0);
#define WaitUntil(A)    do { while(!A) WaitX(1);} while(0);

#define RunTask(TaskName,TaskID)  do { if (timers[TaskID]==0) timers[TaskID]=TaskName(); }  while(0); 
#define RunTaskA(TaskName,TaskID) do { if (timers[TaskID]==0) {timers[TaskID]=TaskName(); continue;}}while(0);   //ǰ����������ȱ�ִ֤��

#define CallSub(SubTaskName) do {unsigned char currdt; _lc=(__LINE__%255)+1; return 0; case (__LINE__%255)+1:  currdt=SubTaskName(); if(currdt!=255) return currdt;} while(0);
#define InitTasks() do {unsigned char i; for(i=MAXTASKS;i>0 ;i--) timers[i-1]=0; } while(0);
#define UpdateTimers() do{unsigned char i; for(i=MAXTASKS;i>0 ;i--){if((timers[i-1]!=0)&&(timers[i-1]!=255)) timers[i-1]--;}} while(0);

#define SEM unsigned int 
//��ʼ���ź���
#define InitSem(sem) do{sem=0;}while(0);
//�ȴ��ź���
#define WaitSem(sem) do{ sem=1; WaitX(0); if (sem>0) return 1;} while(0);
//�����ź���
#define SendSem(sem)  do {sem=0;} while(0);

/*****СС����������*******************************************************/
//LCD����
typedef struct _LCD
{
	u16 width;     //lcd���
	u16 height;    //lcd�߶�
	u16 wramcmd;   //дgramָ��
	u16 setxcmd;   //����x����ָ��
	u16 setycmd;   //����y����ָ��
}_LCD;
//����lcdʵ��5510
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
	

u32 time_lcd=0; //��������ˢ��ʱ��
u8 LCD_D = 0;
int main(void)
{	
	u16 i=0,j=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);	    //��ʱ������ʼ��	
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GPIO_5510_Init();       //���ų�ʼ�� 
	SPI1_Init();           //SPI��ʼ��
	LCD_Init();
	LCD_Init();
//	LCD_Clear(blue);      //IO����
	display_test();       //spi����
	
	
//	TIM3_Int_Init(5000-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms
	TIM3_Int_Init(999,84-1);//��ʱ1ms
	
	
	while(1)
	{
//		LCD_Clear(blue);
		//��ɫ
		time_lcd = 0;
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(RED>>8);
				LCD_WR_DATA(RED&0xff);
			}
		}
		printf("REDˢ��ʱ��Ϊ:%d\r\n",time_lcd);
		time_lcd = 0;
		delay_ms(300);
		//��ɫ
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(GREEN>>8);
				LCD_WR_DATA(GREEN&0xff);
			}
		}
		printf("GREENˢ��ʱ��Ϊ:%d\r\n",time_lcd);
		time_lcd = 0;
		delay_ms(300);
		//��ɫ
		for(i = 0; i < 240; i++)
		{
			for(j = 0; j < 240; j++)
			{
				LCD_WR_DATA(BLUE>>8);
				LCD_WR_DATA(BLUE&0xff);
			}
		}
		printf("\r\nBLUEˢ��ʱ��Ϊ:%d\r\n",time_lcd);
		delay_ms(300);
	}
}


