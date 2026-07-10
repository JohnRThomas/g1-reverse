#include "g1_app_symbols.h"
/* named: opt_node_total_len */
/* Reconstructed opt_node_total_len @ 0x7c41c  (parity: 300/300 trials, PROVEN) */

extern int opt_node_header_len(void);
extern int opt_node_value_len(unsigned int param_1);

int opt_node_total_len(unsigned int param_1)
{
    int iVar1 = opt_node_header_len();
    int iVar2 = opt_node_value_len(param_1);
    return iVar2 + iVar1;
}

