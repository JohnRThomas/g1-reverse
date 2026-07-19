#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000850f6 @ 0x000850f6
 * public-name: value_in_bitmap_0_47
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   value_in_bitmap_0_47                     <= FUN_000850f6 @ 0x000850f6
 */
/* Reconstructed FUN_000850f6 @ 0x850f6  (parity: 300/300 trials, PROVEN) */

unsigned int value_in_bitmap_0_47(unsigned int param_1)
{
  unsigned int uVar1;
  if ((param_1 >> 5) == 0) {
    uVar1 = 0xffffffff;
  } else {
    if ((param_1 >> 5) != 1) {
      return 0;
    }
    uVar1 = 0xffff;
  }
  return (uVar1 >> (param_1 & 0x1f)) & 1;
}
