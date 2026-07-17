#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033c04 @ 0x00033c04
 * public-name: FUN_00033c04
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033c04 @ 0x33c04  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_00033c04(int param_1)
{
  return *(volatile uint8_t*)(param_1 * 0x1b4 + ((unsigned long)g_message_pool) /*=0x20007dac*/ + 0xd);
}
