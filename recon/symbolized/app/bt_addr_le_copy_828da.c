#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000828da @ 0x000828da
 * public-name: bt_addr_le_copy_828da
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 */
/* Reconstructed FUN_000828da @ 0x828da  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void bt_addr_le_copy_828da(uint32_t *param_1, uint32_t *param_2)
{
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
