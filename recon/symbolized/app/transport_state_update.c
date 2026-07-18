#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002538c @ 0x0002538c
 * public-name: transport_state_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_state_update                   <= FUN_0002538c @ 0x0002538c
 *   thunk_FUN_00074f68                       <= FUN_0007c398 @ 0x0007c398
 * address symbols (name @ address):
 *   g_20007a00                               @ 0x20007a00
 *   g_20018c65                               @ 0x20018c65
 */
/* Reconstructed FUN_0002538c @ 0x0002538c, extent 0x00000098.
 * Readable identity: transport_state_update.
 * Raw/address backmap: transport_state_update <= FUN_0002538c @ 0x0002538c.
 */
#include <stdint.h>

extern void FUN_0007c842(void *context);
extern uint64_t thunk_FUN_00074f68(void);

void transport_state_update(uint8_t *context, uint8_t *state)
{
    volatile uint8_t *const active = (volatile uint8_t *)((unsigned long)&g_20018c65) /*=0x20018c65*/;
    volatile uint32_t *const timestamp = (volatile uint32_t *)((unsigned long)&g_20007a00) /*=0x20007a00*/;
    uint8_t phase;

    context[2] = 3U;
    FUN_0007c842(context);
    phase = context[2];

    if (phase == 1U) {
        state[12] = 9U;
        state[3] = 0U;
        if (*(uint32_t *)(context + 8) >= 500U) {
            *active = 0U;
        } else if (*active == 0U) {
            *active = 1U;
        }
    } else if (phase == 2U) {
        uint64_t now = thunk_FUN_00074f68();
        if (now - *timestamp >= 3001U) {
            if (state[5] == 10U) {
                if (state[0] == 0U)
                    state[12] = 6U;
                state[1] = 1U;
            }
            state[3] = 1U;
            *timestamp = thunk_FUN_00074f68();
        }
    } else if (phase == 4U) {
        if (state[5] == 10U) {
            if (state[0] == 0U)
                state[12] = 6U;
            state[1] = 1U;
        }
        if (state[2] == 0U)
            state[2] = 1U;
        *timestamp = thunk_FUN_00074f68();
    } else {
        *timestamp = thunk_FUN_00074f68();
    }
}
