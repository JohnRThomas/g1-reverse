#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010343a0 @ 0x010343a0
 * public-name: FUN_010343a0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010343a0 @ 0x10343a0  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
static volatile uint8_t * const DAT_010343a8 = (volatile uint8_t *)G1_NRF_DPPIC_NS_BASE;
void FUN_010343a0(uint32_t param_1) {
    *(volatile uint32_t*)(DAT_010343a8 + 0x504) = param_1;
}
