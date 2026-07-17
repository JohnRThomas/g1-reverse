#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e9dc @ 0x0007e9dc
 * public-name: settings_nvs_read_latest
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_read_hist                            <= FUN_0004cab4 @ 0x0004cab4
 *   settings_nvs_read_latest                 <= FUN_0007e9dc @ 0x0007e9dc
 */
/* Reconstructed FUN_0007e9dc @ 0x7e9dc  (parity: 300/300 trials, PROVEN) */

extern void nvs_read_hist(void);
void settings_nvs_read_latest(void)
{
  nvs_read_hist();
  return;
}
