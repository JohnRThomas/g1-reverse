#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080970 @ 0x00080970
 * public-name: img_mgmt_vercmp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_vercmp                          <= FUN_00080970 @ 0x00080970
 */
/* Reconstructed FUN_00080970 @ 0x80970  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint32_t img_mgmt_vercmp(uint8_t *param_1, uint8_t *param_2)
{
  if (*param_2 <= *param_1) {
    if (*param_2 < *param_1) {
      return 1;
    }
    if (param_2[1] <= param_1[1]) {
      if (param_2[1] < param_1[1]) {
        return 1;
      }
      if (*(uint16_t*)(param_2 + 2) <= *(uint16_t*)(param_1 + 2)) {
        return (uint32_t)(*(uint16_t*)(param_2 + 2) < *(uint16_t*)(param_1 + 2));
      }
    }
  }
  return 0xffffffffUL;
}
