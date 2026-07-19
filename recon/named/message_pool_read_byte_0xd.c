/* readable reconstruction; identity: FUN_00033c04 @ 0x00033c04
 * public-name: message_pool_read_byte_0xd
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   message_pool_read_byte_0xd               <= FUN_00033c04 @ 0x00033c04
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033c04 @ 0x33c04  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t message_pool_read_byte_0xd(int param_1)
{
  return *(volatile uint8_t*)(param_1 * 0x1b4 + 0x20007dacUL + 0xd);
}
