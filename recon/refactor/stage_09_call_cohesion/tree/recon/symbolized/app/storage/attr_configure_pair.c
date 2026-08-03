#include "g1_app_symbols.h"
#include "g1_storage.h"
/* readable reconstruction; identity: FUN_0007cfdc @ 0x0007cfdc
 * public-name: attr_configure_pair
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   wait_attr_0x4714_clear                   <= FUN_0007cfac @ 0x0007cfac
 *   attr_configure_pair                      <= FUN_0007cfdc @ 0x0007cfdc
 */
/* Reconstructed FUN_0007cfdc @ 0x7cfdc  (parity: 300/300 trials, PROVEN) */

extern int attr_store_set(unsigned int a, unsigned int b);

int attr_configure_pair(unsigned int param_1, unsigned int param_2)
{
  int iVar1;

  iVar1 = attr_store_set(0x4704,param_1);
  if ((((iVar1 == 0) && (iVar1 = attr_store_set(0x4708,param_2), iVar1 == 0)) &&
      (iVar1 = attr_store_set(0x4710,0xc), iVar1 == 0)) &&
     (iVar1 = attr_store_set(0x4714,1), iVar1 == 0)) {
    iVar1 = wait_attr_0x4714_clear();
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
