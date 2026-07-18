/* readable reconstruction; identity: FUN_000758cc @ 0x000758cc
 * public-name: k_aligned_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_heap_aligned_alloc                     <= FUN_00075864 @ 0x00075864
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f075e                             @ 0x000f075e
 *   rodata_f0779                             @ 0x000f0779
 *   rodata_f891e                             @ 0x000f891e
 *   rodata_f899c                             @ 0x000f899c
 *   rodata_f89d9                             @ 0x000f89d9
 */
/* Reconstructed k_aligned_alloc @ 0x000758cc from Zephyr mempool.c.
 * Raw backmap: FUN_000758cc@0x000758cc. */

#include <stdint.h>
#include <stddef.h>

extern void *z_heap_aligned_alloc(void *heap, size_t alignment, size_t size);
extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);

#define z_heap_aligned_alloc z_heap_aligned_alloc
void *k_aligned_alloc(size_t alignment, size_t size)
{
    if (alignment < sizeof(void *) ||
        (alignment & (sizeof(void *) - 1u)) != 0u) {
        printk(0x00099cbdu, 0x000f899cu, 0x000f891eu, 0x42u);
        printk(0x000f89d9u);
        assert_post_action(0x000f891eu, 0x42u);
    }
    if ((alignment & (alignment - 1u)) != 0u) {
        printk(0x00099cbdu, 0x000f075eu, 0x000f891eu, 0x46u);
        printk(0x000f0779u);
        assert_post_action(0x000f891eu, 0x46u);
    }
    return z_heap_aligned_alloc((void *)0x200037d8u, alignment, size);
}
