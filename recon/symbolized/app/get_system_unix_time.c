#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d216 @ 0x0007d216
 * public-name: get_system_unix_time
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_system_unix_time                     <= FUN_0007d216 @ 0x0007d216
 */
/* Reconstructed FUN_0007d216 @ 0x7d216  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
uint32_t get_system_unix_time(void)
{
  int iVar1 = get_device_info();
  return **(volatile uint32_t **)(iVar1 + 0xfec);
}
