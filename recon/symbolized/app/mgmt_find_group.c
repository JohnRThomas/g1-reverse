#include "g1_app_symbols.h"
/* named: mgmt_find_group */
/* Reconstructed mgmt_find_group @ 0x5139c  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;
uint mgmt_find_group(uint param_1)
{
    unsigned int *puVar2 = *(volatile unsigned int**)((uintptr_t)&g_mgmt_group_list_head) /*=0x2000a94c*/;
    unsigned int *puVar1 = puVar2;
    if (puVar2 != 0) puVar1 = (unsigned int*)*puVar2;
    while (1) {
        if (puVar2 == 0) return 0;
        if (*(volatile unsigned short*)((char*)puVar2 + 10) == param_1) break;
        puVar2 = puVar1;
        if (puVar1 != 0) puVar1 = (unsigned int*)*puVar1;
    }
    return puVar2[3];
}

