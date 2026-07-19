#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000831e2 @ 0x000831e2
 * public-name: convert_to_id_on_match
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy_83062                    <= FUN_00083062 @ 0x00083062
 *   convert_to_id_on_match                   <= FUN_000831e2 @ 0x000831e2
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 */
/* Reconstructed FUN_000831e2 @ 0x831e2  (parity: 300/300 trials, PROVEN) */

extern int memcmp(int a, int b, int c);
extern void bt_addr_le_copy_83062(int a, int b);
void convert_to_id_on_match(int param_1, int *param_2)
{
  int iVar1;
  iVar1 = memcmp(param_1 + 0x90, *param_2, 7);
  if (iVar1 == 0) {
    bt_addr_le_copy_83062(param_1 + 0x90, param_2[1]);
  }
}
