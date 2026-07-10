#include "g1_app_symbols.h"
/* named: FUN_0004da90 */
/* Reconstructed FUN_0004da90 @ 0x4da90  (parity: 300/300 trials, PROVEN) */

extern void print_formatted(unsigned int param_1, unsigned int param_2);

void FUN_0004da90(unsigned int param_1, int param_2)
{
    unsigned int uVar1;
    if ((int)((unsigned int)param_2 << 0x1b) < 0) {
        return;
    }
    uVar1 = ((uintptr_t)&rodata_f5400) /*=0xf5400*/;
    if ((int)((unsigned int)param_2 << 0x1a) < 0) {
        uVar1 = "\r\n" /*=0xa8c94*/;
    }
    print_formatted(param_1, uVar1);
}

