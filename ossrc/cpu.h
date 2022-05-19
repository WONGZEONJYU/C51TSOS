#ifndef _CPU_H_
#define _CPU_H_

#if 1
#define _IDATA_ idata
#define _XDATA_ xdata
#define _BDATA_ bdata
#else
#define _IDATA_ 
#define _XDATA_ 
#define _BDATA_ 
#endif

#define os_taskStackType    os_StackType _IDATA_
#define SP_INIT()       {SP = 0xEBu;}
#define INT_STACK()     {SP = 0xEBu;}

#define APPLY_TEMPSP()  os_StackType tempsp
#define BACK_SP()       {tempsp = SP;}
#define RESTORE_SP()    {SP = tempsp;}

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;
typedef unsigned long u32;
typedef u8 os_StackType;
typedef u8 os_BaseType;
typedef u16 os_ShortType;
typedef u32 os_UlongType;
typedef void( * os_funcType )(void);
typedef u16 os_timeType;
typedef u32 os_tickType;



#endif //_CPU_H_

