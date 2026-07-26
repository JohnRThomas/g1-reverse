/* readable reconstruction; identity: FUN_01020048 @ 0x01020048
 * public-name: FUN_01020048
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_01020048 @ 0x1020048  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
static volatile uint8_t * const DAT_01020050 = (volatile uint8_t *)G1_NRF_AAR_NS_BASE;
void FUN_01020048(void) {
    *(volatile uint32_t *)(DAT_01020050 + 8) = 1;
}
