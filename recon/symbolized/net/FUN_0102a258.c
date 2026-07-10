#include "g1_net_symbols.h"
/* net-core FUN_0102a258 @ 0x102a258  (parity 296 trials PROVEN) */

void FUN_0102a258(char *param_1, char *param_2)
{
    char cVar1;
    do {
        cVar1 = *param_2;
        *param_1 = cVar1;
        param_2 = param_2 + 1;
        param_1 = param_1 + 1;
    } while (cVar1 != 0);
}

