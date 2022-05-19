#include "main.h"
#include "RTOSCFG.h"


static os_taskStackType task0_stack[20];
static void task0(void)
{
    while (1u)
    {
        P10 = !P10;
    }
    
}

static os_taskStackType task1_stack[20];
static void task1(void)
{
    while (1u)
    {
        P11 = !P11;
    }
    
}


int main(void)
{
    SP_INIT();
    os_Init();
    os_Create_Task(0,500,task0_stack,task0);
    os_Create_Task(1,500,task1_stack,task1);
    os_Start();

    for (;;)
    {
        
    }

}