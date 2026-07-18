#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025bf8 @ 0x01025bf8
 * public-name: FUN_01025bf8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* CPUNET controller transition completion @ 0x01025bf8.
 * Raw-address backmap: FUN_01025bf8; true executable extent: 0x3c bytes.
 */
#include <stdint.h>

typedef void (*controller_callback_t)(void);

/* Readable identity; preprocessing retains the raw link/back-map symbol. */
#define controller_apply_pending_transition FUN_01025bf8

struct controller_transition_ops {
    controller_callback_t reserved[5];
    controller_callback_t stop;
};

struct controller_transition_state {
    uint8_t busy;
    uint8_t phase;
    uint8_t reserved[2];
    controller_callback_t completion;
    struct controller_transition_ops *ops;
};

void controller_apply_pending_transition(void)
{
    volatile struct controller_transition_state *state =
        (volatile struct controller_transition_state *)(uintptr_t)((unsigned long)&g_net_task_state_struct) /*=0x21001c88*/;

    if (state->busy != 0u) {
        return;
    }

    if (state->phase == 1u) {
        state->phase = 2u;
        if (state->completion != 0) {
            state->completion();
            state->completion = 0;
        }
    }

    /* The first callback may advance the phase, so this must be a fresh read. */
    if (state->phase == 3u) {
        state->phase = 0u;
        if (state->completion != 0) {
            state->ops->stop();
            /* stop() may replace the completion callback; match the reread. */
            state->completion();
            state->completion = 0;
        }
    }
}
