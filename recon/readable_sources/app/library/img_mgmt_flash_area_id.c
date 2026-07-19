#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005169c @ 0x0005169c
 * public-name: img_mgmt_flash_area_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_flash_area_id                   <= FUN_0005169c @ 0x0005169c
 */
/* Reconstructed FUN_0005169c @ 0x5169c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t img_mgmt_flash_area_id(unsigned int param_1)
{
  uint8_t uVar1;
  if (param_1 < 4) {
    uVar1 = *(volatile uint8_t*)(0x000f270aUL + param_1);
  } else {
    uVar1 = 0xff;
  }
  return uVar1;
}
