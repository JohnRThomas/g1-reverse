#include "g1_app_symbols.h"
/* named: find_message_pool_entry_by_id */
/* Reconstructed find_message_pool_entry_by_id @ 0x33c18  (parity: 300/300 trials, PROVEN) */

int find_message_pool_entry_by_id(int param_1)
{
    int iVar1 = 10;
    volatile int *piVar2 = *(volatile int**)((uintptr_t)&tbl_33afc) /*=0x33c44*/;
    while ((*(volatile char*)((int)piVar2+8) == 0) ||
           (*(volatile char*)((int)piVar2+6) != 0) ||
           (piVar2[0] != param_1)) {
        iVar1 = iVar1 + 1;
        piVar2 = (volatile int*)((char*)piVar2 + 0x1b4);
        if (iVar1 == 0x14) {
            return 0;
        }
    }
    return iVar1 * 0x1b4 + *(volatile int*)((uintptr_t)&tbl_33afc) /*=0x33c48*/;
}

