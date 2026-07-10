#include "g1_app_symbols.h"
/* named: driver_stop_active_timer */
/* Reconstructed driver_stop_active_timer @ 0x84c2c  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_timer_stop(int);
int driver_stop_active_timer(int param_1)
{
    int iVar3 = *(int*)(param_1 + 0x10);
    int iVar4 = **(int**)(param_1 + 4);
    int iVar2 = *(int*)(iVar3 + 0xc);
    if (*(int*)(iVar2 + 8) == 0) {
        return 0xfffffff2;
    }
    *(char*)(iVar2 + 0xcd) = 0;
    z_impl_k_timer_stop(*(int*)(iVar3 + 0xc) + 0x20);
    *(int*)(iVar4 + 0xc) = 1;
    return 0;
}

