#include "g1_app_symbols.h"
/* named: now_has_persist_task */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed now_has_persist_task @ 0x2be64  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cdf8(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char*)((uintptr_t)&g_persist_task_status_lock) /*=0x20018d9c*/;
    while (*pcVar1 != 0) {
        FUN_0007cdf8();
    }
    int *p = *(int**)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char*)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 3) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}

