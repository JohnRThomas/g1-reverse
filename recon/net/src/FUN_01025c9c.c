/* net-core FUN_01025c9c @ 0x01025c9c -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

typedef void (*control_fn_t)(void);

void FUN_01025c9c(const void *argument)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21001c88u;
    if (argument == 0)
        controller_fault(0x68, 0x153);
    if (state[1] == 2 || state[1] == 3) {
        void **ops = *(void ***)(state + 8);
        ((control_fn_t)ops[1])();
    }
}
