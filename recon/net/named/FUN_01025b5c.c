/* readable reconstruction; identity: FUN_01025b5c @ 0x01025b5c
 * public-name: FUN_01025b5c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01025b5c @ 0x1025b5c  (parity 300 trials PROVEN) */

void FUN_01025b5c(void)
{
  volatile int *base = (volatile int*)G1_NRF_RADIO_NS_BASE;
  int v = 0x80000004;

  *(volatile int*)((char*)base + 0x180) = v;
  v += 1; *(volatile int*)((char*)base + 0x184) = v;
  v += 1; *(volatile int*)((char*)base + 0x18c) = v;
  v += 1; *(volatile int*)((char*)base + 0x190) = v;
  v += 5; *(volatile int*)((char*)base + 0x1ec) = v;
  v -= 1; *(volatile int*)((char*)base + 0x90) = v;
}
