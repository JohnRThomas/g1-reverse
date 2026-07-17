#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c038 @ 0x0007c038
 * public-name: app_msleep_thunk_a
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 */
/* Reconstructed FUN_0007c038 @ 0x7c038  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void FUN_00074844(void);
void app_msleep_thunk_a(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  FUN_00074844();
  return;
}
