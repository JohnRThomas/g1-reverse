#include "g1_app_symbols.h"
/* named: l2cap_chan_tx_init */
/* Reconstructed l2cap_chan_tx_init @ 0x574ec  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_queue_init(unsigned int a, unsigned int b);
extern void FUN_000732d4(unsigned int a, unsigned int b);

void l2cap_chan_tx_init(int param_1)
{
    *(volatile unsigned int*)(param_1+0x24) = 0;
    *(volatile unsigned int*)(param_1+0x28) = 0;
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    unsigned int uVar1 = *(volatile unsigned int*)(param_1+0x2c);
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    z_impl_k_queue_init(param_1+0x30, uVar1);
    FUN_000732d4(param_1+0x50, ((uintptr_t)&rodata_818dd) /*=0x818dd*/);
}

