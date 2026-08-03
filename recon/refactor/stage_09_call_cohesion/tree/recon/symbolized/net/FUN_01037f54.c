#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037f54 @ 0x01037f54
 * public-name: FUN_01037f54
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_kernel_timeout_dlist_head          @ 0x21000750
 */
/* net-core FUN_01037f54 @ 0x1037f54  (parity 300 trials PROVEN) */

void FUN_01037f54(int *param_1)
{
  if (param_1 != 0) {
    int **p = (int**)((unsigned long)&g_net_kernel_timeout_dlist_head) /*=0x21000750*/;
    if ((int*)param_1 != *(int**)((char*)p + 4)) {
      int iVar3 = *param_1;
      if (iVar3 != 0) {
        unsigned int uVar1 = *(unsigned int*)(iVar3 + 0x10);
        unsigned int uVar4 = (unsigned int)param_1[4];
        int iVar5 = param_1[5];
        unsigned int sum = uVar1 + uVar4;
        int carry = sum < uVar1;
        *(unsigned int*)(iVar3 + 0x10) = sum;
        *(int*)(iVar3 + 0x14) = *(int*)(iVar3 + 0x14) + iVar5 + carry;
      }
    }
  }
  int iVar3 = *param_1;
  int *piVar2 = (int*)param_1[1];
  *piVar2 = iVar3;
  *(int**)(iVar3 + 4) = piVar2;
  *param_1 = 0;
  param_1[1] = 0;
}
