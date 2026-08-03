#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a924 @ 0x0103a924
 * public-name: FUN_0103a924
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a924 @ 0x103a924  (parity 300 trials PROVEN) */
extern int FUN_010345f4(int *);

void FUN_0103a924(int param_1, unsigned char *param_2, unsigned char *param_3,
                   unsigned char *param_4, unsigned char *param_5, unsigned char *param_6)
{
  int iVar1;
  unsigned int pbVar2;
  unsigned int uVar3, uVar4, uVar5, uVar6;
  unsigned int pbVar7;
  int local_1c;
  unsigned int v2, v3, v4, v6;

  local_1c = param_1;
  iVar1 = FUN_010345f4(&local_1c);
  pbVar2 = (unsigned int)(param_3 != 0 ? 1 : 0);
  iVar1 = iVar1 + local_1c * 4;
  pbVar7 = (unsigned int)(param_2 != 0 ? 1 : 0);
  uVar3 = (param_4 != 0) ? 0xc : 0;
  uVar4 = (param_5 != 0) ? 0xf00 : 0;
  uVar5 = (param_6 != 0) ? 0x30000 : 0;

  v2 = (param_2 != 0) ? (unsigned int)*param_2 : 0;
  v3 = (param_3 != 0) ? ((unsigned int)*param_3 << 1) : 0;
  v4 = (param_4 != 0) ? ((unsigned int)*param_4 << 2) : 0;
  uVar6 = (param_5 == 0) ? 0 : ((unsigned int)*param_5 << 8);
  v6 = (param_6 != 0) ? ((unsigned int)*param_6 << 0x10) : 0;

  *(unsigned int *)(iVar1 + 0x200) =
      uVar6 | v2 |
      (*(unsigned int *)(iVar1 + 0x200) & ~(pbVar7 | (pbVar2 << 1) | uVar3 | uVar4 | uVar5)) |
      v3 | v4 | v6;
  return;
}
