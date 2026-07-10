#include "g1_app_symbols.h"
/* named: rate_limited_elapsed_seconds_tick */
/* globals referenced:
//   0x2000a0a0  g_progress_tick_ms           
*/
/* Reconstructed rate_limited_elapsed_seconds_tick @ 0x4a46c  (parity: 300/300 trials, PROVEN) */

extern int k_uptime_get_9(void);

void rate_limited_elapsed_seconds_tick(int *param_1, int param_2, int param_3)
{
    volatile int *arr = (volatile int*)((uintptr_t)&g_progress_tick_ms) /*=0x2000a0a0*/;
    int iVar3;
    if (param_3 == 0) {
        iVar3 = k_uptime_get_9();
        int iVar4 = arr[param_2];
        if (iVar4 == 0) {
            arr[param_2] = iVar3;
        } else if ((unsigned int)(iVar3 - iVar4) > 999) {
            unsigned int uVar5 = (unsigned int)(iVar3-iVar4)/1000;
            int iv = *param_1;
            arr[param_2] = uVar5*1000 + iVar4;
            *param_1 = iv + uVar5;
        }
    } else {
        int uVar2 = k_uptime_get_9();
        arr[param_2] = uVar2;
    }
}

