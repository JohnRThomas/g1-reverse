/* Reconstructed FUN_0007ef3e @ 0x7ef3e */
#include <stdint.h>

void FUN_0007ef3e(void *object)
{
    uint8_t *base = object;
    uintptr_t member = *(uintptr_t *)(base + 0x14);
    if (member) {
        volatile uint32_t *flags = (volatile uint32_t *)(member + 4);
        (void)__atomic_fetch_or((uint32_t *)flags, 1u, __ATOMIC_ACQ_REL);
    }
}
