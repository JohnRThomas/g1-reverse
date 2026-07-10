#include "g1_app_symbols.h"
/* named: FUN_00053580 */
/* Reconstructed FUN_00053580 @ 0x53580  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_hex(unsigned int a, unsigned int b);
extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);

void FUN_00053580(unsigned int param_1, int param_2)
{
    unsigned short uVar1;
    unsigned int local_28;
    unsigned int local_24;
    unsigned int uStack_20;
    unsigned int local_1c;
    unsigned int uStack_18;
    unsigned short local_14;

    uVar1 = *(unsigned short *)(param_2 + 0x10);
    uStack_18 = bt_hex(*(unsigned int *)(param_2 + 0xc), (unsigned int)uVar1);
    local_24 = "Unhandled event 0x%02x len %u: %s" /*=0xf2df8*/;
    local_14 = 0x402;
    local_28 = 0x01000005UL;
    uStack_20 = param_1;
    local_1c = (unsigned int)uVar1;
    FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x2c80, &local_28);
}

