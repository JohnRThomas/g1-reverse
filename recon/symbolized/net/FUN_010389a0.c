#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010389a0 @ 0x010389a0
 * public-name: FUN_010389a0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 */
/* Zephyr k_aligned_alloc @ 0x010389a0, exact executable extent 0x3e.
 * Raw/address backmaps:
 *   FUN_010389a0@0x010389a0
 *   z_heap_aligned_alloc = FUN_01038958@0x01038958
 *   system_heap@0x210008b4
 * Its tail branch ends at 0x010389de; literals begin at 0x010389e0.
 */
#include <stddef.h>
#include <stdint.h>
#define k_aligned_alloc FUN_010389a0

extern void *z_heap_aligned_alloc(void *, size_t,
                                  size_t); /* FUN_01038958 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void *k_aligned_alloc(size_t alignment, size_t size)
{
    if (alignment < sizeof(void *) ||
        (alignment & (sizeof(void *) - 1u)) != 0u) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eba0) /*=0x103eba0*/, 0x42u);
        assert_post_action(((unsigned long)&rodata_103eba0) /*=0x103eba0*/, 0x42u);
    }
    if ((alignment & (alignment - 1u)) != 0u) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eba0) /*=0x103eba0*/, 0x46u);
        assert_post_action(((unsigned long)&rodata_103eba0) /*=0x103eba0*/, 0x46u);
    }
    return z_heap_aligned_alloc((void *)0x210008b4u, alignment, size);
}
