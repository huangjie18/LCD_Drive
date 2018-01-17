#ifndef __OS_H
#define __OS_H
#include "sys.h"

#define OS_STASK_MAX   (1)    //���������������
typedef  struct 
{
   // Pointer to the task (must be a 'void (void)' function)
   void (* pTask)(void);  

   // Delay (ticks) until the function will (next) be run
   // - see SCH_Add_Task() for further details
   u8 Delay;       

   // Interval (ticks) between subsequent runs.
   // - see SCH_Add_Task() for further details
   u8 Period;       

   // Incremented (by scheduler) when task is due to execute
   u8 RunMe;       
} sTask; 

void OS_Init(void);                //�����ʼ��
void OS_Delete_Task(u8 TASK_INDEX);   //ɾ������
#endif