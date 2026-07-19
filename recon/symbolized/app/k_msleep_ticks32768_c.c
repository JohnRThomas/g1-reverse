#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d194 @ 0x0007d194
 * public-name: k_msleep_ticks32768_c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   k_msleep_ticks32768_c                    <= FUN_0007d194 @ 0x0007d194
 */
/* Reconstructed FUN_0007d194 @ 0x7d194  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void k_sleep(void);
void k_msleep_ticks32768_c(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  k_sleep();
  return;
}
