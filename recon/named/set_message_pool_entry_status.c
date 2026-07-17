/* readable reconstruction; identity: FUN_00033bf0 @ 0x00033bf0
 * public-name: set_message_pool_entry_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_message_pool_entry_status            <= FUN_00033bf0 @ 0x00033bf0
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033bf0 @ 0x33bf0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void set_message_pool_entry_status(int param_1, uint8_t param_2)
{
  *(volatile uint8_t*)(param_1 * 0x1b4 + 0x20007dacUL + 0xd) = param_2;
  return;
}
