#include "g1_app_symbols.h"
/* named: opt_list_append_node */
/* Reconstructed opt_list_append_node @ 0x7c7de  (parity: 300/300 trials, PROVEN) */

extern int opt_node_total_len(unsigned char *a);

unsigned int opt_list_append_node(unsigned int *param_1, unsigned char *param_2)
{
    unsigned char bVar1;
    unsigned char *pbVar2;
    unsigned char *pbVar5;
    int iVar3;
    unsigned int uVar4;

    if (param_1 == 0 || param_2 == 0) {
        uVar4 = 7;
    } else {
        bVar1 = *param_2;
        *param_2 = (unsigned char)((bVar1 & 0x7f) | 0x40);
        *(volatile unsigned int *)(param_2 + 0x18) = 0;
        pbVar2 = *(unsigned char **)param_1;
        if (pbVar2 == 0) {
            *param_2 = (unsigned char)((bVar1 & 0x7f) | 0xc0);
            *(unsigned char **)param_1 = param_2;
        } else {
            do {
                pbVar5 = pbVar2;
                pbVar2 = *(unsigned char **)(pbVar5 + 0x18);
            } while (*(unsigned char **)(pbVar5 + 0x18) != 0);
            *(unsigned char **)(pbVar5 + 0x18) = param_2;
            *pbVar5 = (unsigned char)(*pbVar5 & 0xbf);
        }
        iVar3 = opt_node_total_len(param_2);
        uVar4 = 0;
        param_1[1] = param_1[1] + iVar3;
        param_1[2] = param_1[2] + 1;
    }
    return uVar4;
}

