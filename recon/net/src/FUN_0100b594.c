/* net-core controller_radio_idle_state_finish @ 0x0100b594
 * Catalog-missing executable ownership is [0x0100b594,0x0100b5f4).
 * The 0x21000c48 base literal is [0x0100b5f4,0x0100b5f8), followed by the
 * independent entry at 0x0100b5f8.  The caller supplies context/event in
 * r0/r1, but this fallback deliberately reads the controller's fixed state.
 * Raw backmap: FUN_0100b594@0x0100b594. */
#include <stdint.h>

extern void FUN_01008d00(uint32_t group, uint32_t line);
extern void FUN_0100ac34(void);
extern void FUN_010207cc(uint32_t timestamp);
extern void FUN_01022a50(uint32_t channel, void *output, uint32_t mode);

#define CONTROLLER_RADIO_STATE_ADDR 0x21000c48u

void controller_radio_idle_state_finish(void *unused_context,
                                        uint32_t unused_event)
{
    volatile uint8_t *state =
        (volatile uint8_t *)CONTROLLER_RADIO_STATE_ADDR;

    if (state[0x44u] == 0u) {
        FUN_0100ac34();
    } else if (state[0x24u] != 0u) {
        if (state[0x44u] != 2u) {
            FUN_01008d00(0x27u, 0x224u);
            return;
        }
        volatile uint8_t *context =
            *(volatile uint8_t * volatile *)(state + 0x28u);
        FUN_010207cc(*(volatile uint32_t *)(context + 0x2f0u));
    } else if (state[0x44u] != 1u) {
        FUN_01008d00(0x27u, 0x220u);
        FUN_0100ac34();
    }

    volatile uint8_t *context =
        *(volatile uint8_t * volatile *)(state + 0x28u);
    uint32_t busy = context[0x7bu];
    if (busy == 0u && *(volatile uint32_t *)(context + 0x74u) != 0u) {
        FUN_01022a50(context[0x7au], 0, busy);
    }
}
