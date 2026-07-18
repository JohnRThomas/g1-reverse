/* Reconstructed z_heap_aligned_alloc @ 0x00075864 from Zephyr mempool.c.
 * Raw backmap: FUN_00075864@0x00075864. */

#include <stdint.h>
#include <stddef.h>

extern void *FUN_000719f4(void *heap, size_t alignment, size_t size,
                          uint64_t timeout);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);

#define k_heap_aligned_alloc FUN_000719f4
void *z_heap_aligned_alloc(void *heap, size_t alignment, size_t size)
{
    size_t adjusted_size = size + sizeof(void *);
    if (adjusted_size < size) {
        return 0;
    }

    void *allocation = k_heap_aligned_alloc(
        heap, alignment | sizeof(void *), adjusted_size, 0u);
    if (allocation == 0) {
        return 0;
    }

    *(void **)allocation = heap;
    void *result = (uint8_t *)allocation + sizeof(void *);
    if (alignment != 0u &&
        (((uintptr_t)result & (alignment - 1u)) != 0u)) {
        FUN_0007e2fa(0x00099cbdu, 0x000f8942u, 0x000f891eu, 0x25u);
        FUN_0007e2fa(0x000f8974u, result, alignment);
        FUN_0007e2ec(0x000f891eu, 0x25u);
        return 0;
    }
    return result;
}
