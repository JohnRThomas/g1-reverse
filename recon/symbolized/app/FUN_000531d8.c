#include "g1_app_symbols.h"
/* named: FUN_000531d8 */
/* Reconstructed FUN_000531d8 @ 0x531d8  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00073424(unsigned int a, void *b);
unsigned int FUN_000531d8(void *param_1)
{
    return FUN_00073424(((uintptr_t)&g_sys_work_q) /*=0x20005d38*/, param_1);
}

