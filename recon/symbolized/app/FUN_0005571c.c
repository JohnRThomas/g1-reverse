#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005571c @ 0x0005571c
 * public-name: FUN_0005571c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_bt_le_legacy_adv                       @ 0x20002018
 */
/* Reconstructed FUN_0005571c @ 0x5571c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int a0, unsigned int a1, unsigned int a2);
void FUN_0005571c(void)
{
  memset_bytes(((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/, 0, 0x50);
}
