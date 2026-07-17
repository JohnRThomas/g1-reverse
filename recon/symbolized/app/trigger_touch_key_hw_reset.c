#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a0c0 @ 0x0002a0c0
 * public-name: trigger_touch_key_hw_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   trigger_touch_key_hw_reset               <= FUN_0002a0c0 @ 0x0002a0c0
 * address symbols (name @ address):
 *   g_some_module_sem                        @ 0x20007b1c
 *   g_some_module_init_done_flag             @ 0x20018d8a
 */
/* Reconstructed FUN_0002a0c0 @ 0x2a0c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void process_sync_buffer(unsigned int);
void trigger_touch_key_hw_reset(void)
{
  if (*(volatile uint8_t*)((unsigned long)&g_some_module_init_done_flag) /*=0x20018d8a*/ != 0) {
    process_sync_buffer(((unsigned long)&g_some_module_sem) /*=0x20007b1c*/);
    return;
  }
  return;
}
