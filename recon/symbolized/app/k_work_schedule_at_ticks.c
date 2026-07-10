#include "g1_app_symbols.h"
/* named: k_work_schedule_at_ticks */
/* Reconstructed k_work_schedule_at_ticks @ 0x531cc  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007332c(uint32_t, int);
int k_work_schedule_at_ticks(int param_1){
    return FUN_0007332c(((uintptr_t)&g_sys_work_q) /*=0x20005d38*/, param_1);
}

