#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084d70 @ 0x00084d70
 * public-name: nvs_ate_id_matches
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_ate_id_matches                       <= FUN_00084d70 @ 0x00084d70
 */
/* Reconstructed FUN_00084d70 @ 0x84d70  (parity: 300/300 trials, PROVEN) */

unsigned int nvs_ate_id_matches(int param_1,int param_2)
{
  unsigned int uVar1;
  if (param_1 == 4) { return 1; }
  if (param_1 == 5) {
    uVar1 = (unsigned int)(param_2 - 1);
    if (uVar1 != 0) { uVar1 = 1; }
    return uVar1;
  }
  return (unsigned int)(param_1 == param_2);
}
