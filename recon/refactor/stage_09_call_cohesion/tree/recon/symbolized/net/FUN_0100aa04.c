#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100aa04 @ 0x0100aa04
 * public-name: FUN_0100aa04
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_addr_cache_pair                    @ 0x21000c34
 */
/* net-core FUN_0100aa04 @ 0x100aa04  (parity 300 trials PROVEN) */

char FUN_0100aa04(int param_1, unsigned int *param_2)
{
  volatile unsigned char *base = (volatile unsigned char*)((unsigned long)&g_net_addr_cache_pair) /*=0x21000c34*/;
  char cVar2 = 0;
  if (param_1 == 0) {
    cVar2 = *(volatile char *)(base);
    if (cVar2 != 0) {
      unsigned short uVar1 = *(volatile unsigned short *)(base+8);
      *param_2 = *(volatile unsigned int *)(base+4);
      *(unsigned short*)((char*)param_2+4) = uVar1;
    }
    return cVar2;
  } else {
    if (param_1 != 1) return 0;
    cVar2 = *(volatile char *)(base+10);
    if (cVar2 != 0) {
      unsigned short uVar1 = *(volatile unsigned short *)(base+0x10);
      *param_2 = *(volatile unsigned int *)(base+0xc);
      *(unsigned short*)((char*)param_2+4) = uVar1;
      return cVar2;
    }
    return cVar2;
  }
}
