#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083062 @ 0x00083062
 * public-name: bt_addr_le_copy_83062
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy_83062                    <= FUN_00083062 @ 0x00083062
 */
/* Reconstructed FUN_00083062 @ 0x83062  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void bt_addr_le_copy_83062(unsigned int*param_1, unsigned int*param_2) {
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
