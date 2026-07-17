#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01022ebc @ 0x01022ebc
 * public-name: FUN_01022ebc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01022ebc @ 0x1022ebc  (parity 300 trials PROVEN) */
/* net-core FUN_01022ebc @ 0x1022ebc  (parity 300 trials PROVEN) */
/* net-core FUN_01022ebc @ 0x1022ebc  (parity 300 trials PROVEN) */
/* net-core FUN_01022ebc @ 0x1022ebc  (parity 300 trials PROVEN) */

static volatile unsigned char *const P_1022f04 = (volatile unsigned char *)((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/;
unsigned char FUN_01022ebc(unsigned int param_1)
{
  if (param_1 < 0x20) {
    unsigned int off = (param_1 + (unsigned int)P_1022f04[0x49] * 0x20) * 2 + 0x50;
    if (P_1022f04[off] == 0) return 0;
    if (P_1022f04[off] == 1) {
      P_1022f04[off] = 0;
      return 1;
    }
  }
  return 0;
}
