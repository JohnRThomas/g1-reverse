#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d6b0 @ 0x0100d6b0
 * public-name: FUN_0100d6b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100d6b0 @ 0x100d6b0  (parity 300 trials PROVEN) */

unsigned long long FUN_0100d6b0(unsigned int param_1, unsigned int param_2)
{
  unsigned long long prod;
  unsigned int hi, lo, q;
  if (0x1d4bu < param_2) {
    prod = (unsigned long long)0xd1b71759u * (unsigned long long)param_1;
    lo = (unsigned int)prod;
    hi = (unsigned int)(prod >> 32);
    q = (hi >> 0xa) * 0x4e2u;
    return ((unsigned long long)lo << 32) | q;
  } else {
    prod = (unsigned long long)0x51eb851fu * (unsigned long long)param_1;
    lo = (unsigned int)prod;
    hi = (unsigned int)(prod >> 32);
    q = (hi >> 5) * 100u;
    return ((unsigned long long)lo << 32) | q;
  }
}
