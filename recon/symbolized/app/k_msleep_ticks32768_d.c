#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c0a8 @ 0x0007c0a8
 * public-name: k_msleep_ticks32768_d
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   k_msleep_ticks32768_d                    <= FUN_0007c0a8 @ 0x0007c0a8
 */
/* Reconstructed FUN_0007c0a8 @ 0x7c0a8  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void wait_for_event(void);
void k_msleep_ticks32768_d(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  wait_for_event();
  return;
}
