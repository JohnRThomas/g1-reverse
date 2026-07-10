#include "g1_app_symbols.h"
/* named: FUN_00051fe4 */
/* Reconstructed FUN_00051fe4 @ 0x51fe4  (parity: 300/300 trials, PROVEN) */

extern unsigned int memset_bytes(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00051fe4(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
    unsigned int iVar1 = memset_bytes(((uintptr_t)&img_mgmt_state) /*=0x2000ab80*/, 0, 0x2c, ((uintptr_t)&img_mgmt_state) /*=0x2000ab80*/, p3);
    *(volatile unsigned int*)(iVar1 - 4) = 0xffffffffUL;
}

