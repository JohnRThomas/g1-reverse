#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102460c @ 0x0102460c
 * public-name: FUN_0102460c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_deferred_irq_num                   @ 0x21001bca
 */
/* net-core FUN_0102460c @ 0x102460c  (parity 300 trials PROVEN) */

void FUN_0102460c(void)
{
  volatile signed char *p = (volatile signed char *)((unsigned long)&g_net_deferred_irq_num) /*=0x21001bca*/;
  int v = (int)*p;
  if (v >= 0) {
    volatile unsigned int *base = (volatile unsigned int *)0xe000e100;
    base[(v >> 5) + 0x40] = 1u << (v & 0x1f);
  }
  return;
}
