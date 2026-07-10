#include "g1_app_symbols.h"
/* named: lock_device_mutex */
/* Reconstructed lock_device_mutex @ 0x7c8b0  (parity: 300/300 trials, PROVEN) */

extern void thunk_FUN_000723b8(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void lock_device_mutex(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 0) {
        thunk_FUN_000723b8(*(unsigned int *)(param_1 + 0x10), param_2, 0xffffffffU, 0xffffffffU, param_4);
    }
}

