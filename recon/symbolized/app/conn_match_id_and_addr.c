#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080c20 @ 0x00080c20
 * public-name: conn_match_id_and_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   active_transfer_conn_match               <= FUN_000527dc @ 0x000527dc
 *   conn_match_id_and_addr                   <= FUN_00080c20 @ 0x00080c20
 */
/* Reconstructed FUN_00080c20 @ 0x80c20  (parity: 300/300 trials, PROVEN) */

extern unsigned long long active_transfer_conn_match(unsigned int a);

unsigned int conn_match_id_and_addr(int param_1, unsigned int param_2)
{
  unsigned long long uVar1;
  if (param_2 != 0) {
    uVar1 = active_transfer_conn_match(param_2);
    param_2 = (unsigned int)uVar1;
    if (param_2 != 0) {
      if (*(int*)(param_1+0x18) == (int)(uVar1>>32)) {
        param_2 = (unsigned int)(*(char*)(param_2+0x69) == *(char*)(param_1+0x1c));
      } else {
        param_2 = 1;
      }
    }
  }
  return param_2;
}
