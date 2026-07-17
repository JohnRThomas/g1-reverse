#include "g1_net_symbols.h"
/* net-core controller_radio_request_state_clear @ 0x0101fdc0.
 * Reachable code is [0x0101fdc0,0x0101fdca), followed by the unexecuted
 * alignment NOP at 0x0101fdca and owned address literal [0x0101fdcc,
 * 0x0101fdd0). FUN_0101fc14 tail-branches here after radio shutdown.
 * Raw backmap: FUN_0101fdc0@0x0101fdc0. */
#include <stdint.h>

struct controller_radio_request_state {
    uint8_t active;
    uint8_t mode;
    uint8_t pending;
    uint8_t request_kind;
    uint8_t channel;
};

#define CONTROLLER_RADIO_REQUEST_STATE_ADDR ((unsigned long)&g_net_radio_pending_reset_flag) /*=0x210014dc*/

void controller_radio_request_state_clear(void)
{
    volatile struct controller_radio_request_state *state =
        (volatile struct controller_radio_request_state *)
            CONTROLLER_RADIO_REQUEST_STATE_ADDR;

    /* Preserve the shipped halfword transaction for active+mode. */
    *(volatile uint16_t *)&state->active = 0;
    state->pending = 0;
}
