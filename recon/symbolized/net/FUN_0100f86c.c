#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f86c @ 0x0100f86c
 * public-name: FUN_0100f86c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private state-transition helper @ 0x0100f86c.
 * Raw back-map: FUN_0100f86c@0x0100f86c; extent 0x32. */
#include <stdint.h>

extern unsigned FUN_0100d3c0(void *state, unsigned arg, unsigned mode,
                             unsigned reserved);

uint64_t FUN_0100f86c(uint8_t *owner, const uint8_t *request,
                      unsigned unused2, unsigned unused3)
{
    volatile uint8_t *state = *(uint8_t **)(owner + 4) + 0xa8;
    (void)unused2;
    (void)unused3;
    if (FUN_0100d3c0((void *)state, 0, state[0x1e], 0) == 0)
        return 1;
    state[0xa0] = request[3];
    *(volatile uint16_t *)(state + 0x5a) = 0;
    state[0x1e] = 3;
    state[0x5c] = 1;
    return (uint64_t)request[3] << 32;
}
