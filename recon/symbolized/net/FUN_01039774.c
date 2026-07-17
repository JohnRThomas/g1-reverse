#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039774 @ 0x01039774
 * public-name: FUN_01039774
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039774 @ 0x1039774  (parity 300 trials PROVEN) */

void FUN_01039774(int param_1,int param_2,int param_3)
{
  int iVar1 = param_1 + param_2 * 8;
  if (*(unsigned int *)(param_1 + 8) > 0x7fff) {
    unsigned int uVar3;
    if (param_3 == 0) uVar3 = *(unsigned int *)(iVar1 + 4) & 0xfffffffe;
    else uVar3 = *(unsigned int *)(iVar1 + 4) | 1;
    *(unsigned int *)(iVar1 + 4) = uVar3;
    return;
  }
  {
    unsigned short uVar2;
    if (param_3 == 0) uVar2 = *(unsigned short *)(iVar1 + 2) & 0xfffe;
    else uVar2 = *(unsigned short *)(iVar1 + 2) | 1;
    *(unsigned short *)(iVar1 + 2) = uVar2;
  }
}
