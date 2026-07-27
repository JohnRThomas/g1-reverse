#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000758cc @ 0x000758cc
 * public-name: k_aligned_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_heap_aligned_alloc                     <= FUN_00075864 @ 0x00075864
 *   k_aligned_alloc                          <= FUN_000758cc @ 0x000758cc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f075e                             @ 0x000f075e   [INLINED -- G6 literal batch]
 *   rodata_f0779                             @ 0x000f0779   [INLINED -- G6 literal batch]
 *   rodata_f891e                             @ 0x000f891e
 *   rodata_f899c                             @ 0x000f899c
 *   rodata_f89d9                             @ 0x000f89d9
 */
/* Reconstructed k_aligned_alloc @ 0x000758cc.
 * Raw backmap: FUN_000758cc@0x000758cc. */

#include <stdint.h>
#include <stddef.h>
#include "../../headers/g1_log.h"

extern void *z_heap_aligned_alloc(void *heap, size_t alignment, size_t size);
extern int assert_post_action(int, int);

#define z_heap_aligned_alloc z_heap_aligned_alloc
void *k_aligned_alloc(size_t alignment, size_t size)
{
    if (alignment < sizeof(void *) ||
        (alignment & (sizeof(void *) - 1u)) != 0u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f899c) /*=0xf899c*/, ((unsigned long)&rodata_f891e) /*=0xf891e*/, 0x42u);
        printk(((unsigned long)&rodata_f89d9) /*=0xf89d9*/);
        assert_post_action(((unsigned long)&rodata_f891e) /*=0xf891e*/, 0x42u);
    }
    if ((alignment & (alignment - 1u)) != 0u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"(align & (align - 1)) == 0") /*=0xf075e*/, ((unsigned long)&rodata_f891e) /*=0xf891e*/, 0x46u);
        printk(((unsigned long)"\talign must be a power of 2\n") /*=0xf0779*/);
        assert_post_action(((unsigned long)&rodata_f891e) /*=0xf891e*/, 0x46u);
    }
    return z_heap_aligned_alloc((void *)0x200037d8u, alignment, size);
}
