#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f192 @ 0x0007f192
 * public-name: settings_load
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_load_subtree                    <= FUN_0004e3e8 @ 0x0004e3e8
 *   settings_load                            <= FUN_0007f192 @ 0x0007f192
 */
/* Reconstructed FUN_0007f192 @ 0x7f192  (parity: 300/300 trials, PROVEN) */

extern int settings_load_subtree(const char *);

int settings_load(void)
{
  return settings_load_subtree(0);
}
