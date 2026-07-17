#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086a06 @ 0x00086a06
 * public-name: check_is_release_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   check_is_release_mode                    <= FUN_00086a06 @ 0x00086a06
 */
/* Reconstructed FUN_00086a06 @ 0x86a06  (parity: 300/300 trials, PROVEN) */
extern int FUN_00077b24(int,...);
unsigned int check_is_release_mode(int param_1) {
  return FUN_00077b24(param_1, 0, 0xa);
}
