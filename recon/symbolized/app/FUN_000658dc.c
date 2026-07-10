#include "g1_app_symbols.h"
/* named: FUN_000658dc */
/* Reconstructed FUN_000658dc @ 0x658dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_000658dc(unsigned int param_1, unsigned int param_2)
{
    *(volatile uint32_t*)((uintptr_t)&g_ancs_notify_sync_field0_2bc8) /*=0x20002bc8*/ = param_1;
    *(volatile uint32_t*)((uintptr_t)&g_ancs_notify_sync_field1_2bcc) /*=0x20002bcc*/ = param_2;
}

