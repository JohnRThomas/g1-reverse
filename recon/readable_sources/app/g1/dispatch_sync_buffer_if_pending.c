#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a4c0 @ 0x0002a4c0
 * public-name: dispatch_sync_buffer_if_pending
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dispatch_sync_buffer_if_pending          <= FUN_0002a4c0 @ 0x0002a4c0
 * address symbols (name @ address):
 *   g_misc_dispatch_ctx                      @ 0x20007b00
 *   g_misc_dispatch_pending_flag             @ 0x20018d88
 */
/* Reconstructed FUN_0002a4c0 @ 0x2a4c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void process_sync_buffer(void *arg);

void dispatch_sync_buffer_if_pending(void)
{
  if (*(volatile uint8_t*)((unsigned long)&g_misc_dispatch_pending_flag) /*=0x20018d88*/ != 0) {
    process_sync_buffer((void*)((unsigned long)&g_misc_dispatch_ctx) /*=0x20007b00*/);
    return;
  }
  return;
}
