/* readable reconstruction; identity: FUN_00075864 @ 0x00075864
 * public-name: z_heap_aligned_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_heap_alloc                             <= FUN_000719f4 @ 0x000719f4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f891e                             @ 0x000f891e
 *   rodata_f8942                             @ 0x000f8942
 *   rodata_f8974                             @ 0x000f8974
 */
/* Reconstructed z_heap_aligned_alloc @ 0x00075864 from Zephyr mempool.c.
 * Raw backmap: FUN_00075864@0x00075864. */

#include <stdint.h>
#include <stddef.h>

extern void *k_heap_alloc(void *heap, size_t alignment, size_t size,
                          uint64_t timeout);
extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);

#define k_heap_aligned_alloc k_heap_alloc
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
        printk(0x00099cbdu, 0x000f8942u, 0x000f891eu, 0x25u);
        printk(0x000f8974u, result, alignment);
        assert_post_action(0x000f891eu, 0x25u);
        return 0;
    }
    return result;
}
