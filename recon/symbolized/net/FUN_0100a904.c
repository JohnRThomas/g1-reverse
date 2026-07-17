#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a904 @ 0x0100a904
 * public-name: FUN_0100a904
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a904 @ 0x100a904  (parity 300 trials PROVEN) */

unsigned int FUN_0100a904(int *param_1)
{
  unsigned int base = 0x21000bf8;
  volatile unsigned short *p34 = (volatile unsigned short*)(base + 0x34);
  volatile unsigned char  *p32 = (volatile unsigned char*)(base + 0x32);

  if (*p34 != 0xffff) {
    *param_1 = 0;
    return 0;
  }
  if (*p32 != 1) {
    *param_1 = (int)base;
    return 1;
  }
  return 0;
}
