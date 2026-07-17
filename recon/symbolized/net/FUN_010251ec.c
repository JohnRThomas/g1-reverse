#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010251ec @ 0x010251ec
 * public-name: FUN_010251ec
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_4100c140                             @ 0x4100c140
 *   REG_41011140                             @ 0x41011140
 */
/* net-core FUN_010251ec @ 0x10251ec */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t subsystem,
                                                   uint32_t reason);

uintptr_t FUN_010251ec(uint32_t channel)
{
    if (channel < 4)
        return UINT32_C(0x4100c140) + channel * 4;

    channel = (uint8_t)(channel - 4);
    if (channel < 2)
        return UINT32_C(0x41011140) + channel * 4;

    FUN_010256dc(0x6c, 0x3cd);
}
