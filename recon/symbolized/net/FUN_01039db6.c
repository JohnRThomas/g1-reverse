#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039db6 @ 0x01039db6
 * public-name: FUN_01039db6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039db6 @ 0x1039db6  (parity 300 trials PROVEN) */

extern unsigned int FUN_01039bfe(void);

void FUN_01039db6(int param_1)
{
  int v = *(int *)(param_1 + 0x10);
  if ((v << 0x1d) < 0) {
    unsigned int uVar2 = *(unsigned int *)(param_1 + 0x28);
    unsigned int uVar1 = FUN_01039bfe();
    if (uVar1 <= uVar2) {
      *(unsigned int *)(param_1 + 0x28) = uVar2;
    } else {
      *(unsigned int *)(param_1 + 0x28) = uVar1;
    }
  }
}
