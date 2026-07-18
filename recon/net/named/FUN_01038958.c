/* readable reconstruction; identity: FUN_01038958 @ 0x01038958
 * public-name: FUN_01038958
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 */
/* Zephyr z_heap_aligned_alloc @ 0x01038958, exact extent 0x40.
 * CFG_VERIFY_CALL_ARITIES=3,3,2
 * Raw/address backmaps:
 *   FUN_01038958@0x01038958
 *   k_heap_aligned_alloc = FUN_01035d18@0x01035d18
 * Return ends at 0x01038998; assertion literals follow.
 */
#include <stddef.h>
#include <stdint.h>
#define z_heap_aligned_alloc FUN_01038958

extern void *k_heap_aligned_alloc(void *, size_t, size_t,
                                  uint64_t); /* FUN_01035d18 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void *z_heap_aligned_alloc(void *heap, size_t alignment, size_t size)
{
    void *memory;

    if (size > SIZE_MAX - sizeof(void *)) {
        return 0;
    }
    memory = k_heap_aligned_alloc(heap, alignment | sizeof(void *),
                                  size + sizeof(void *), 0);
    if (memory == 0) {
        return 0;
    }
    *(void **)memory = heap;
    memory = (uint8_t *)memory + sizeof(void *);
    if (alignment != 0u &&
        ((uintptr_t)memory & (alignment - 1u)) != 0u) {
        assert_print(0x0103d2a7u, 0x0103eba0u, 0x25u);
        assert_post_action(0x0103eba0u, 0x25u);
    }
    return memory;
}
