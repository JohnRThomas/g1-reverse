#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d860 @ 0x0007d860
 * public-name: index_in_range32_mask
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   index_in_range32_mask                    <= FUN_0007d860 @ 0x0007d860
 */
/* Reconstructed FUN_0007d860 @ 0x7d860  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int index_in_range32_mask(unsigned int param_1)
{
  unsigned int uVar1;
  uVar1 = 0xffffffff;
  if (0x1f < param_1) {
    uVar1 = 0;
  }
  return uVar1;
}
