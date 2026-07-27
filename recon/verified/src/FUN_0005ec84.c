/* Reconstructed FUN_0005ec84 @ 0x5ec84, exact extent 70 bytes. */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line);

void FUN_0005ec84(uint8_t *destination, const uint8_t *source, uint32_t length)
{
    uintptr_t dst = (uintptr_t)destination;
    uintptr_t src = (uintptr_t)source;
    if (dst == src || (src < dst ? src + length > dst : dst + length > src)) {
        FUN_0007e2fa(0x00099cbdu, 0x000f38c6u, 0x000f3894u, 0x215u);
        FUN_0007e2fa(0x000f391du);
        FUN_0007e2ec(0x000f3894u, 0x215u);
        return;
    }

    const uint8_t *read = source + length;
    uint8_t *write = destination;
    while (write != destination + length)
        *write++ = *--read;
}
