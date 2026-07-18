#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d3a0 @ 0x0100d3a0
 * public-name: FUN_0100d3a0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET reverse byte copy @ 0x0100d3a0.
 * Raw back-map: FUN_0100d3a0=reverse_copy_u8; true executable extent 0x1e. */
#include <stdint.h>

void FUN_0100d3a0(uint8_t *destination, const uint8_t *source,
                  uint32_t raw_length)
{
    /* The firmware deliberately narrows length-1 to a byte. */
    uint32_t count = (uint8_t)(raw_length - 1u) + 1u;

    if (raw_length == 0u)
        return;

    source += raw_length;
    do {
        *destination++ = *--source;
    } while (--count != 0u);
}
