#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103735c @ 0x0103735c
 * public-name: FUN_0103735c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_0103735c @ 0x103735c  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

void FUN_0103735c(unsigned int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int *piVar1;
  int iVar2;

  if ((unsigned int)param_2 == 0x210043a8u) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x484);
    FUN_01039bb0(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x484);
  }
  iVar2 = param_2[0];
  piVar1 = (int *)param_2[1];
  *piVar1 = iVar2;
  *(int **)(iVar2 + 4) = piVar1;
  param_2[0] = 0;
  param_2[1] = 0;
  return;
}
