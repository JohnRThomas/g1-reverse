/* net-core FUN_010295d6 @ 0x10295d6  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t sdc_controller_random_get(void); /* FUN_0100f63c @ 0x0100f63c. */
/* Readable role: controller_random_window_step. Raw back-map: FUN_010295d6 @ 0x010295d6. */
void FUN_010295d6(void *state_pointer, uint32_t shrink)
{
    uint8_t *state = (uint8_t *)state_pointer;
    uint16_t window = *(uint16_t *)state;
    if (state[3] == 0u) {
        if (shrink == 0u) {
            if (window < 0xffu) {
                window = (uint16_t)(window * 2u);
                if (window > 0xffu)
                    window = 0xffu;
                *(uint16_t *)state = window;
            }
        } else if (window > 1u) {
            window = (uint16_t)(window >> 1);
            *(uint16_t *)state = window;
        }
        window = *(uint16_t *)state;
        state[2] = (uint8_t)(sdc_controller_random_get() % window);
    }
    state[3] ^= 1u;
}
