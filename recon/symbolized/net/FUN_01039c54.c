#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039c54 @ 0x01039c54
 * public-name: FUN_01039c54
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039c54 @ 0x1039c54  (parity 300 trials PROVEN) */

extern unsigned int FUN_01039c20(unsigned int *p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);

void FUN_01039c54(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1, uVar2;
    int bVar3;
    uVar1 = (param_2 << 2) | 2;
    *(unsigned int *)(param_1[8] + param_1[0]*4) = uVar1;
    uVar1 = FUN_01039c20(param_1, param_1[0], param_2, uVar1, param_4);
    uVar2 = param_1[3];
    bVar3 = (uVar1 == uVar2);
    if (bVar3) uVar2 = param_1[4];
    param_1[0] = uVar1;
    if (bVar3) uVar2 = uVar2 | 8;
    if (bVar3) param_1[4] = uVar2;
    uVar1 = FUN_01039c20(param_1, param_1[1], param_2, uVar2, param_4);
    param_1[1] = uVar1;
}
