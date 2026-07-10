#include "g1_net_symbols.h"
/* net-core FUN_0102def4 @ 0x102def4  (parity 300 trials PROVEN) */
extern int FUN_0102cc34(int,int,int,int);
int FUN_0102def4(unsigned int param_1)
{
    return FUN_0102cc34(((uintptr_t)&g_net_periodic_work_obj) /*=0x2100086c*/, (int)param_1, 0, 0);
}

