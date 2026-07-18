#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080864 @ 0x00080864
 * public-name: smp_write_hdr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_write_hdr                            <= FUN_00080864 @ 0x00080864
 */
/* Reconstructed FUN_00080864 @ 0x80864  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void smp_write_hdr(uint32_t *param_1, uint32_t *param_2)
{
  volatile uint32_t *puVar1 = *(volatile uint32_t **)((char*)0 + *param_1 + 0xc);
  *puVar1 = *param_2;
  puVar1[1] = param_2[1];
  return;
}
