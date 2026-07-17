#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033c74 @ 0x01033c74
 * public-name: FUN_01033c74
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_154_dppi_channel_ack                   @ 0x2100645c
 */
/* net-core FUN_01033c74 @ 0x1033c74  (parity 300 trials PROVEN) */

void FUN_01033c74(void)
{
  volatile unsigned char *p1 = (volatile unsigned char *)((unsigned long)&g_154_dppi_channel_ack) /*=0x2100645c*/;
  volatile unsigned char *base = (volatile unsigned char *)0x41014000;
  unsigned char b = *p1;
  unsigned int v = (unsigned int)b | 0x80000000u;
  *(volatile unsigned int *)(base + 0x198) = v;
  *(volatile unsigned int *)(base + 0x5000 + 0x80) = v;
  volatile unsigned char *p3 = (volatile unsigned char *)0x4100f000;
  *(volatile unsigned int *)(p3 + 0x504) = 1u << b;
  return;
}
