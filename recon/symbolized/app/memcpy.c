#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086c04 @ 0x00086c04
 * public-name: memcpy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00086c04 @ 0x86c04  (parity: 300/300 trials, PROVEN) */

void memcpy(unsigned char *param_1, unsigned char *param_2, int param_3)
{
  unsigned char *end = param_2 + param_3;
  unsigned char *dst = param_1 - 1;
  if (param_2 != end) {
    do {
      unsigned char v = *(volatile unsigned char *)param_2;
      param_2 = param_2 + 1;
      dst = dst + 1;
      *(volatile unsigned char *)dst = v;
    } while (param_2 != end);
  }
}
