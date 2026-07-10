#include "g1_app_symbols.h"
/* named: FUN_00072fdc */
/* Reconstructed FUN_00072fdc @ 0x72fdc  (parity: 300/300 trials, PROVEN) */

extern void k_work_submit_to_queue(unsigned int, unsigned int);
void FUN_00072fdc(unsigned int param_1)
{
    k_work_submit_to_queue(((uintptr_t)&g_audio_module_spinlock) /*=0x200068d0*/, param_1);
}

