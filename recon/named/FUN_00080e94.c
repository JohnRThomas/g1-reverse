/* readable reconstruction; identity: FUN_00080e94 @ 0x00080e94
 * public-name: FUN_00080e94
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00080e94 @ 0x80e94  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00080e94(uint32_t *param_1, uint32_t *param_2)
{
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
