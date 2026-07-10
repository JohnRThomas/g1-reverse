#include "g1_app_symbols.h"
/* named: smp_timeout */
/* Reconstructed smp_timeout @ 0x5e3e0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00083074(unsigned int, int, void*);
extern void smp_pairing_complete(int, int);
extern void atomic_set_bit(int, int);

void smp_timeout(int param_1)
{
    unsigned int local_10_arr[2];
    local_10_arr[0] = 2;
    local_10_arr[1] = "SMP Timeout" /*=0xf51ec*/;
    FUN_00083074(((uintptr_t)&tbl_880d8) /*=0x88180*/, 0x1040, local_10_arr);
    smp_pairing_complete(param_1 - 0x208, 8);
    atomic_set_bit(param_1 - 0x204, 4);
}

