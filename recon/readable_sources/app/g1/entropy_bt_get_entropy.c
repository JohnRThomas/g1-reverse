#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083896 @ 0x00083896
 * public-name: entropy_bt_get_entropy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_le_rand                           <= FUN_00053e74 @ 0x00053e74
 *   bt_is_ready                              <= FUN_00054c64 @ 0x00054c64
 *   entropy_bt_get_entropy                   <= FUN_00083896 @ 0x00083896
 */
/* Reconstructed FUN_00083896 @ 0x83896  (parity: 300/300 trials, PROVEN) */

extern int bt_is_ready(void);
extern unsigned int bt_hci_le_rand(unsigned int, unsigned int);

unsigned int entropy_bt_get_entropy(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = bt_is_ready();
  if (iVar1 != 0) {
    uVar2 = bt_hci_le_rand(param_2,param_3);
    return uVar2;
  }
  return 0xfffffff5;
}
