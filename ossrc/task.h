#ifndef _TASK_H_
#define _TASK_H_

#include "cpu.h"

typedef struct OS_TaskControlBlock {
    os_timeType volatile TimesLiceCtr;
    os_timeType volatile TimesLice;
    os_BaseType volatile Reday;
    os_StackType volatile TopofStack;
}os_TCB;


typedef struct OS_CTRL
{
    os_tickType volatile TickCnt;
    os_BaseType TaskNumber;
    os_BaseType volatile os_CurrTask_ID;
}Os_Console;


void os_Create_Task(os_BaseType const taskid,os_timeType const TimesLice,
                    os_StackType  * pStack,os_funcType const taskenter);

void os_Init(void);
void os_Start(void);
void os_Delay(os_tickType const tick);


#endif  //_TASK_H_
