#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010246e4 @ 0x010246e4
 * public-name: FUN_010246e4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_154_critical_section_nest_cnt          @ 0x21001bd0
 */
/* net-core FUN_010246e4 @ 0x10246e4  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01024a9c(void);
#include <cmsis_gcc.h>

void FUN_010246e4(void)
{
  unsigned int primask;
  primask = __get_PRIMASK();
  __disable_irq();
  volatile unsigned char *base = (volatile unsigned char *)((unsigned long)&g_154_critical_section_nest_cnt) /*=0x21001bd0*/;
  base[6] = base[6] + 1;
  if (base[6] == 1) {
    FUN_01024a9c();
  }
  if (primask == 0) {
    __enable_irq();
  }
  return;
}
