#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081788 @ 0x00081788
 * public-name: ctx_list_unlink_node
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ctx_list_unlink_node                     <= FUN_00081788 @ 0x00081788
 */
/* Reconstructed FUN_00081788 @ 0x81788  (parity: 300/300 trials, PROVEN) */

extern void FUN_000815f6(int, int*);

void ctx_list_unlink_node(int param_1, int *param_2)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  if (*(int**)(param_1+0x54) != 0) {
    piVar1 = 0;
    piVar2 = *(int**)(param_1+0x54);
    do {
      if (param_2 == piVar2 - 2) {
        FUN_000815f6(param_1+0x54, piVar1);
        return;
      }
      piVar3 = (int*)*piVar2;
      piVar1 = piVar2;
      piVar2 = piVar3;
    } while (piVar3 != 0);
  }
}
