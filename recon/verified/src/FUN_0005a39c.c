/* Reconstructed FUN_0005a39c @ 0x5a39c, exact extent 34 bytes. */
#include <stdint.h>

extern void FUN_000828da(uintptr_t destination, uintptr_t source,
                         uintptr_t object, uint32_t mode);

void FUN_0005a39c(uintptr_t object, uint32_t a1, uint32_t a2, uint32_t mode)
{
    (void)a1; (void)a2;
    FUN_000828da(object + 1u, 0x000f2b3au, object, mode);
    *(volatile uint8_t *)(object + 8u) = 0;
    __atomic_store_n((volatile uint32_t *)(object + 0xcu), 0u,
                     __ATOMIC_RELAXED);
}
