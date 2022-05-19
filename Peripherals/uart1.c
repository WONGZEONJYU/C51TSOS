#include "STC15.H"
#include "uart1.h"

void Uart1_Init(void)
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xCC;		//设置定时初始值
	T2H = 0xFF;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
}


void Uart1_Send(unsigned char dat)
{
    SBUF = dat;
	while (0u == TI);
	TI = 0u;
}


