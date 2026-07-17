#include "g1_net_symbols.h"
/* Reconstructed internal net function FUN_010217cc @ 0x010217cc.
 * Semantic role: recompute the net-clock onoff manager's request batch size.
 * Exact code extent is [0x010217cc,0x010217fc); the raw 0x21001670 context
 * maps durably to g_net_clk_onoff_ctx.  Its literal occupies 0x010217fc.
 */
#include <stdint.h>

struct net_clock_onoff_batch_state {
    uint8_t reserved[10];
    volatile uint8_t active_requests;
    volatile uint8_t requests_per_batch;
    volatile uint8_t pending_requests;
};

#define NET_CLOCK_ONOFF_BATCH_STATE \
    ((volatile struct net_clock_onoff_batch_state *)0x21001670u) /* g_net_clk_onoff_ctx */
#define net_clock_onoff_recompute_batch_size FUN_010217cc /* raw entry back-map */

void net_clock_onoff_recompute_batch_size(void)
{
    volatile struct net_clock_onoff_batch_state *state =
        NET_CLOCK_ONOFF_BATCH_STATE;
    unsigned active_requests = state->active_requests;

    if (active_requests == 0) {
        state->requests_per_batch = 0;
        return;
    }

    unsigned pending_requests = state->pending_requests;
    unsigned requests_per_batch = pending_requests / active_requests;
    if (requests_per_batch < 1)
        requests_per_batch = 1;
    if (active_requests < pending_requests &&
        pending_requests % active_requests != 0)
        ++requests_per_batch;
    state->requests_per_batch = (uint8_t)requests_per_batch;
}
