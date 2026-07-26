/* readable reconstruction; identity: FUN_0102f4ec @ 0x0102f4ec
 * public-name: FUN_0102f4ec
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102f4ec @ 0x102f4ec CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_nrf_regs.h"

void FUN_0102f4ec(void)
{
  volatile unsigned int *p = (volatile unsigned int *)G1_SCB_CPUID;
  __DSB();
  p[3] = 0x05fa0004 | (p[3] & 0x700);
  __DSB();
  while (1) { }
}
