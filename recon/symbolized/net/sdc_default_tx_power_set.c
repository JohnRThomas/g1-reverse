#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010091cc @ 0x010091cc
 * public-name: sdc_default_tx_power_set
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Reconstructed sdc_default_tx_power_set @ 0x010091cc
 * (raw identity: FUN_010091cc). */
#include <stdint.h>

/* Internal controller setter.  It forwards the signed power level through
 * its own leaf chain; retaining this argument is part of the public ABI. */
extern void FUN_0101e94c(int8_t requested_power_level);

#define controller_state (*(volatile uint8_t *)0x21000a5cUL)

int32_t sdc_default_tx_power_set(int8_t requested_power_level)
{
    if (controller_state != 0)
        return -1;

    FUN_0101e94c(requested_power_level);
    return 0;
}
