#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d39e @ 0x0007d39e
 * public-name: onboarding_clear_active_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   onboarding_clear_active_flag             <= FUN_0007d39e @ 0x0007d39e
 */
/* Reconstructed FUN_0007d39e @ 0x7d39e  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
void onboarding_clear_active_flag(void)
{
  int iVar1;
  iVar1 = get_device_info();
  if (**(volatile char **)(iVar1 + 0x1014) != (char)0) {
    iVar1 = get_device_info();
    **(volatile unsigned char **)(iVar1 + 0x1014) = 0;
  }
  return;
}
