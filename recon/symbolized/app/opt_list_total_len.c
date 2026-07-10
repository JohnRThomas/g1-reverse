#include "g1_app_symbols.h"
/* named: opt_list_total_len */
/* Reconstructed opt_list_total_len @ 0x7c754  (parity: 300/300 trials, PROVEN) */

extern int opt_node_total_len(int);
int opt_list_total_len(int *param_1, int *param_2)
{
    if (param_1 == 0 || param_2 == 0) {
        return 7;
    }
    int iVar4 = 0, iVar5 = 0, iVar3;
    for (iVar3 = *param_1; iVar3 != 0; iVar3 = *(int*)(iVar3 + 0x18)) {
        int iVar1 = opt_node_total_len(iVar3);
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + iVar1;
    }
    param_2[0] = iVar5;
    param_2[1] = iVar4;
    return 0;
}

