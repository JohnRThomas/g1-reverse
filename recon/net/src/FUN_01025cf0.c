/* net-core FUN_01025cf0 @ 0x1025cf0  (CFG-directed candidate) */
#include <stdint.h>
typedef uint32_t (*callback_t)(void);
uint32_t controller_transition_pending_check(void) {
    volatile uint8_t *state = (volatile uint8_t *)0x21001c88u;
    uint8_t mode = state[1];
    if (mode != 2 && mode != 3) return 0;
    uintptr_t ops = *(volatile uint32_t *)(state + 8);
    callback_t callback = *(callback_t *)(ops + 0x10);
    return callback();
}
