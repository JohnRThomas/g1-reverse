/* readable reconstruction; identity: FUN_00081196 @ 0x00081196
 * public-name: bt_addr_le_copy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy                          <= FUN_00081196 @ 0x00081196
 */
/* Reconstructed FUN_00081196 @ 0x81196  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void bt_addr_le_copy(unsigned int*param_1, unsigned int*param_2) {
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
