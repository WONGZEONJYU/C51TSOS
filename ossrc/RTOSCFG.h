#ifndef _RTOSCFG_H_
#define _RTOSCFG_H_

#define CPU_FREQ                    (24000000u)
#define TIMING                      (1000u)
#define USE_12T                     (0u)

#if USE_12T > 0u
#define TIM_H   ((0xffffu-((CPU_FREQ)/(TIMING))) >> 8u)
#define TIM_L   (0xffffu-((CPU_FREQ)/(TIMING))
#else
#define TIM_H   ((0xffffu-((CPU_FREQ)/(TIMING)/12)) >> 8u)
#define TIM_L   (0xffffu-((CPU_FREQ)/(TIMING)/12))
#endif

#define OS_DELAY_MAX                (0xfffffffful)
#define OS_TASK_NUMBER              (8u)
#define OS_IDLE_TASK_NUMBER         (1u)

#include "task.h"
#include "stc15.h"
#include "cpu.h"
#include "intrins.h"

#endif //_RTOSCFG_H_


