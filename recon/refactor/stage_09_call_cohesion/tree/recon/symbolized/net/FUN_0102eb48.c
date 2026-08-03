#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102eb48 @ 0x0102eb48
 * public-name: FUN_0102eb48
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102eb48 @ 0x102eb48  (parity 300 trials PROVEN) */

#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_nrf_regs.h"
void FUN_0102eb48(unsigned int param_1_raw)
{
  int v = (int)(int8_t)param_1_raw;
  if (v >= 0) {
    volatile unsigned int *base = (volatile unsigned int *)G1_NVIC_ISER0;
    base[(v >> 5) + 0x20] = 1u << (v & 0x1f);
    __DSB();
    __ISB();
  }
  return;
}
