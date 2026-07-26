/* net-core FUN_010208b0 @ 0x10208b0  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

#define DAT_010208c8 ((unsigned int)G1_NRF_RADIO_NS_BASE)

void FUN_010208b0(void)
{
    unsigned int iVar1 = DAT_010208c8;
    *(volatile unsigned int *)(DAT_010208c8 + 0x200) = *(volatile unsigned int *)(DAT_010208c8 + 0x200) & 0xffffffbf;
    *(volatile unsigned int *)(iVar1 + 0x560) = 0;
    return;
}

