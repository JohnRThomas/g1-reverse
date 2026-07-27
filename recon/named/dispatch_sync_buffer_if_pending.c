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
extern unsigned long process_sync_buffer(unsigned int, ...);

void dispatch_sync_buffer_if_pending(void)
{
  if (*(volatile uint8_t*)0x20018d88UL != 0) {
    process_sync_buffer((void*)0x20007b00UL);
    return;
  }
  return;
}
