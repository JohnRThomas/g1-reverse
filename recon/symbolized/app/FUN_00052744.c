#include "g1_app_symbols.h"
/* named: FUN_00052744 */
/* Reconstructed FUN_00052744 @ 0x52744  (parity: 300/300 trials, PROVEN) */

extern void net_buf_destroy_default(unsigned int a);
extern void k_work_submit_to_queue(unsigned int a, unsigned int b);

void FUN_00052744(int param_1)
{
    net_buf_destroy_default(param_1 + 0x10);
    k_work_submit_to_queue(((uintptr_t)&g_audio_buf_release_workq) /*=0x20005bb8*/, param_1);
}

