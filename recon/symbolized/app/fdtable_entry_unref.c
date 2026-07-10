#include "g1_app_symbols.h"
/* named: fdtable_entry_unref */
/* globals referenced:
//   0x20002548  g_posix_fd_table             
*/
/* Reconstructed fdtable_entry_unref @ 0x4b048  (parity: 300/300 trials, PROVEN) */

void fdtable_entry_unref(int param_1)
{
    int iVar1;
    int iVar2;
    volatile int *piVar3;

    iVar1 = ((uintptr_t)&g_posix_fd_table) /*=0x20002548*/;
    piVar3 = (volatile int *)(param_1 * 0x28 + 8 + ((uintptr_t)&g_posix_fd_table) /*=0x20002548*/);
    do {
        iVar2 = *piVar3;
        if (iVar2 == 0) {
            return;
        }
    } while (*piVar3 != iVar2);
    *piVar3 = iVar2 - 1;
    if (iVar2 == 1) {
        *(volatile int *)(iVar1 + param_1 * 0x28) = 0;
        *(volatile int *)(iVar1 + param_1 * 0x28 + 4) = 0;
    }
}

