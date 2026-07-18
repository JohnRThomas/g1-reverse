/* Reconstructed k_aligned_alloc @ 0x000758cc from Zephyr mempool.c.
 * Raw backmap: FUN_000758cc@0x000758cc. */

#include <stdint.h>
#include <stddef.h>

extern void *FUN_00075864(void *heap, size_t alignment, size_t size);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);

#define z_heap_aligned_alloc FUN_00075864
void *k_aligned_alloc(size_t alignment, size_t size)
{
    if (alignment < sizeof(void *) ||
        (alignment & (sizeof(void *) - 1u)) != 0u) {
        FUN_0007e2fa(0x00099cbdu, 0x000f899cu, 0x000f891eu, 0x42u);
        FUN_0007e2fa(0x000f89d9u);
        FUN_0007e2ec(0x000f891eu, 0x42u);
    }
    if ((alignment & (alignment - 1u)) != 0u) {
        FUN_0007e2fa(0x00099cbdu, 0x000f075eu, 0x000f891eu, 0x46u);
        FUN_0007e2fa(0x000f0779u);
        FUN_0007e2ec(0x000f891eu, 0x46u);
    }
    return z_heap_aligned_alloc((void *)0x200037d8u, alignment, size);
}
