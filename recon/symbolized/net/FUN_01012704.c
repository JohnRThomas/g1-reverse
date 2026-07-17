#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01012704 @ 0x01012704
 * public-name: FUN_01012704
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core FUN_01012704 @ 0x1012704  (parity 300 trials PROVEN) */

typedef void (*fnptr)(unsigned int);
void FUN_01012704(unsigned int param_1)
{
  volatile unsigned char *base = (volatile unsigned char *)((unsigned long)&g_net_own_addr_info) /*=0x21000f20*/;
  *(volatile unsigned int *)(base + 0x2c) = param_1;
  unsigned int ptr1 = *(volatile unsigned int *)(base + 0x28);
  fnptr f = *(fnptr *)ptr1;
  f(param_1);
}
