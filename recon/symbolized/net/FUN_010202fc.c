#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010202fc @ 0x010202fc
 * public-name: FUN_010202fc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010202fc @ 0x10202fc */
#include <stdint.h>

extern void sdc_assertion_fail(unsigned module, unsigned line,
                         unsigned arg2, unsigned arg3, unsigned arg4);

void FUN_010202fc(uint32_t channel, uint32_t mode,
                  uint32_t detail, uint32_t context)
{
    volatile uint8_t *state = (volatile uint8_t *)0x210015f0u;
    volatile uint32_t *radio = (volatile uint32_t *)REG_41008000 /*=0x41008000*/;
    uint32_t config;

    state[0x34] = (uint8_t)channel;
    switch (mode) {
    case 1:
        config = 0x63900108u;
        break;
    case 2:
        config = 0x00100108u;
        break;
    case 4:
    case 8:
        config = 0x01100108u;
        break;
    default:
        sdc_assertion_fail(0x3e, 0x2dc, detail, (uint32_t)state, context);
        return;
    }

    radio[0x514 / 4] = config;
    radio[0x518 / 4] = 0x02030000u | channel;
    if ((radio[0x550 / 4] & 0xf7u) == 3u)
        sdc_assertion_fail(0x3e, 0x2f4, 0x02030000u | channel, 3, context);
}
