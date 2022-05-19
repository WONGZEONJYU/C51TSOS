#include "cpu.h"
#include "RTOSCFG.h"

extern os_TCB os_tcb_list[];
extern Os_Console os_Console[];
extern void os_TaskSwitch(void);
extern void os_TickUpdate(void);

void os_Timer0_ISR(void) interrupt 1 using 0
{
    EA = 0;
    #pragma asm
    PUSH    7
    PUSH    6
    PUSH    5
    PUSH    4
    PUSH    3
    PUSH    2
    PUSH    1
    PUSH    0
    #pragma endasm

    os_tcb_list[os_Console->os_CurrTask_ID].TopofStack = SP;
    INT_STACK();
    os_TickUpdate();
    os_TaskSwitch();
    SP = os_tcb_list[os_Console->os_CurrTask_ID].TopofStack;

    #pragma asm
    POP     0
    POP     1
    POP     2
    POP     3
    POP     4
    POP     5
    POP     6
    POP     7
    #pragma endasm
    EA = 1;
}


