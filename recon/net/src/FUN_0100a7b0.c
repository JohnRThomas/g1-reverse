/* net-core FUN_0100a7b0 @ 0x100a7b0  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_0100a718(void);
extern void FUN_0100a760(void);
#define DAT_0100a7c8 ((unsigned int)G1_NRF_DPPIC_NS_BASE)

void FUN_0100a7b0(void)
{
    FUN_0100a718();
    FUN_0100a760();
    *(volatile unsigned int *)(DAT_0100a7c8 + 0x508) = 0x1ff8;
    return;
}

