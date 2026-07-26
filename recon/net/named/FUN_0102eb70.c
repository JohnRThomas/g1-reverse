/* readable reconstruction; identity: FUN_0102eb70 @ 0x0102eb70
 * public-name: FUN_0102eb70
 * durable-map: recon/catalogs/function_names_net.json
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_0102eb70 @ 0x102eb70  (parity 300 trials PROVEN) */

volatile unsigned int *DAT_0102eb88 = (volatile unsigned int *)G1_NVIC_ISER0;
unsigned int FUN_0102eb70(unsigned int param_1) {
  return (1u << (param_1 & 0x1f)) & DAT_0102eb88[param_1 >> 5];
}
