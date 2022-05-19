#include "RTOSCFG.h"

// #define READ_BIT(var,bit)       ((var) & (1u << (bit)))
// #define SET_BIT(var,bit)        ((var) |= (1u << (bit)))
// #define CLR_BIT(var,bit)        ((var) &= (~(1u << (bit))))

os_TCB os_tcb_list[OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER];
Os_Console os_Console[1u];


static os_taskStackType os_Idle_Task_Stack[20];
static void os_Idle_Task(void)
{
    for(;;)
    {
        P12 = !P12;
    }
}


void os_Init(void)
{
    os_BaseType i;

    os_Console->os_CurrTask_ID = 0;
    os_Console->TaskNumber = 0;
    os_Console->TickCnt = 0;

    for (i = 0; i < (OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER); i++){
       os_tcb_list[i].Reday = 0;
       os_tcb_list[i].TimesLice = 0;
       os_tcb_list[i].TimesLiceCtr = 0;
       os_tcb_list[i].TopofStack = 0;
    }

#if USE_12T > 0u

    AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
#else
    AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
#endif
    TL0 = TIM_L;
	TH0 = TIM_H;
    TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0开始计时
    ET0 = 0;
}


void os_Create_Task(os_BaseType const taskid,os_timeType const TimesLice,
                    os_StackType * pStack,os_funcType const taskenter)
{
    os_BaseType i;
    os_ShortType func = 0;
    os_StackType * stack;

    if ((os_Console->TaskNumber + 1) >= (OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER)){
        return;
    }
    
    for  (i = 0; i < (OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER); i++){
        stack = (os_StackType *)os_tcb_list[i].TopofStack;
        func |= stack[1];
        func |= (os_ShortType)(stack[2] << 8u);
        if ((os_ShortType)taskenter == func){
            return;
        }
    }

    *++pStack = (os_BaseType)((os_ShortType)taskenter);
    *++pStack = (os_BaseType)((os_ShortType)taskenter >> 8u);
    os_tcb_list[taskid].TopofStack = (os_StackType)(pStack + 13u);
    os_tcb_list[taskid].TimesLice = TimesLice;
    os_tcb_list[taskid].TimesLiceCtr = TimesLice;
    os_tcb_list[taskid].Reday = 1u;

    if (os_Console->TaskNumber < (OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER)){
        ++os_Console->TaskNumber;
    }
}

void os_TickUpdate(void)
{
    ++os_Console->TickCnt;
}


void os_TaskSwitch(void)
{
    if ((os_tcb_list[os_Console->os_CurrTask_ID].TimesLiceCtr > 0u) && 
                            os_tcb_list[os_Console->os_CurrTask_ID].Reday)
    {
        os_tcb_list[os_Console->os_CurrTask_ID].TimesLiceCtr--;
        return;
    }
    else
    {
        os_tcb_list[os_Console->os_CurrTask_ID].TimesLiceCtr = os_tcb_list[os_Console->os_CurrTask_ID].TimesLice;
    }
    
    for (;;)
    {
        ++os_Console->os_CurrTask_ID;

        if (os_Console->os_CurrTask_ID > (OS_TASK_NUMBER + OS_IDLE_TASK_NUMBER))
        {
            os_Console->os_CurrTask_ID = 0u;
        }
        
        if (os_tcb_list[os_Console->os_CurrTask_ID].Reday)
        {
            return;
        }
    }
}


void os_Start(void)
{
    os_Create_Task(OS_TASK_NUMBER,1,os_Idle_Task_Stack,os_Idle_Task);

    SP = (os_tcb_list[0].TopofStack - 13u);
    ET0 = 1u;
    TR0 = 1u;		
    EA = 1u;
}

void os_Delay(os_tickType const tick)
{
    os_tickType currtick = os_Console->TickCnt;
    os_tickType wait = tick;

    if (tick <= OS_DELAY_MAX){
        wait +=  1u;
    }
    while ((os_Console->TickCnt - currtick) < wait);
}

