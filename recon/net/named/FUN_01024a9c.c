/* readable reconstruction; identity: FUN_01024a9c @ 0x01024a9c
 * public-name: FUN_01024a9c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41005000                             @ 0x41005000
 */
/* net-core FUN_01024a9c @ 0x1024a9c  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
static volatile uint32_t * const DAT_01024aa4 = (volatile uint32_t *)G1_NRF_CLOCK_NS_BASE;
void FUN_01024a9c(void) { *DAT_01024aa4 = 1; }
