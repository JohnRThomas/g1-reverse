#include "g1_app_symbols.h"
/* named: FUN_000736ec */
/* Reconstructed FUN_000736ec @ 0x736ec  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_000736ec(unsigned int param_1)
{
    unsigned int uVar1;
    if (*(volatile unsigned short*)(param_1+0xe) < 0x80) {
        uVar1 = *(volatile unsigned int*)((uintptr_t)&g_sched_ready_runq_nonempty_flag) /*=0x2000b48c*/;
        if (uVar1 == 0) goto LAB;
        {
            int b = *(volatile signed char*)(param_1+0xe);
            int t = *(volatile int*)((uintptr_t)&g_sched_ready_runq_prio_cache) /*=0x2000b488*/;
            if (b >= t) {
                if ((*(volatile unsigned char*)(param_1+0xd) & 0x1f) == 0) {
                    uVar1 = param_1 - ((uintptr_t)&g_thread_dummy) /*=0x20006720*/;
                    if (uVar1 != 0) uVar1 = 1;
                    goto LAB;
                }
            }
        }
    }
    uVar1 = 0;
LAB:
    return uVar1 & 1;
}

