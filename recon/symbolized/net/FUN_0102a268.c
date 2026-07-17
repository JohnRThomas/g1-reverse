#include "g1_net_symbols.h"
/* net-core FUN_0102a268 @ 0x102a268  (parity 300 trials PROVEN) */

int FUN_0102a268(char *param_1)
{
    char cVar1;
    char *pcVar2, *pcVar3;
    pcVar3 = param_1;
    do {
        pcVar2 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar2;
    } while (cVar1 != 0);
    return (int)(pcVar2 - 1 - param_1);
}
