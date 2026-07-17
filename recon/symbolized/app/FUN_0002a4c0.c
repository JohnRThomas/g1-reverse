#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a4c0 @ 0x0002a4c0
 * public-name: FUN_0002a4c0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_misc_dispatch_ctx                      @ 0x20007b00
 *   g_misc_dispatch_pending_flag             @ 0x20018d88
 */
/* Reconstructed FUN_0002a4c0 @ 0x2a4c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072880(void *arg);

void FUN_0002a4c0(void)
{
  if (*(volatile uint8_t*)((unsigned long)&g_misc_dispatch_pending_flag) /*=0x20018d88*/ != 0) {
    thunk_FUN_00072880((void*)((unsigned long)&g_misc_dispatch_ctx) /*=0x20007b00*/);
    return;
  }
  return;
}
