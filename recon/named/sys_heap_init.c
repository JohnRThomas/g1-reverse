/* readable reconstruction; identity: FUN_0004b3c8 @ 0x0004b3c8
 * public-name: sys_heap_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_heap_init                            <= FUN_0004b3c8 @ 0x0004b3c8
 *   chunk_set                                <= FUN_0007de02 @ 0x0007de02
 *   set_chunk_used                           <= FUN_0007de24 @ 0x0007de24
 *   chunk_set_used_flag                      <= FUN_0007de54 @ 0x0007de54
 *   log_msg_compute_wlen                     <= FUN_0007de70 @ 0x0007de70
 *   heap_bucket_index                        <= FUN_0007de82 @ 0x0007de82
 *   free_list_add                            <= FUN_0007e022 @ 0x0007e022
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_40000                             @ 0x00040000
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0692                             @ 0x000f0692
 *   rodata_f0796                             @ 0x000f0796   [INLINED -- G6 literal batch]
 *   rodata_f07b7                             @ 0x000f07b7   [INLINED -- G6 literal batch]
 *   rodata_f07d0                             @ 0x000f07d0   [INLINED -- G6 literal batch]
 *   rodata_f07f9                             @ 0x000f07f9   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004b3c8 @ 0x4b3c8
 * Readable identity: sys_heap_init (Zephyr 3.4.99).
 * Raw/address backmap: sys_heap_init <= FUN_0004b3c8 @ 0x0004b3c8.
 */
#include <stdint.h>
#include "../headers/g1_log.h"

/* printk */
extern void assert_post_action(uint32_t, uint32_t); /* assert_post_action */
extern uint32_t heap_bucket_index(uint32_t, uint32_t, uint32_t, uint32_t); /* bucket_idx */
extern uint32_t log_msg_compute_wlen(uint32_t, uint32_t); /* chunksz */
extern void *memset_bytes(void *, uint32_t, uint32_t); /* memset */
extern void chunk_set_used_flag(void *, uint32_t, uint32_t); /* set_left_chunk_size */
extern void chunk_set(unsigned char *, unsigned int, unsigned int, unsigned int); /* chunk_set */
extern void set_chunk_used(void *, uint32_t, uint32_t); /* set_chunk_used */
extern void free_list_add(void *, uint32_t); /* free_list_add */

void sys_heap_init(uint32_t *heap, void *memory, uint32_t bytes)
{
    uint32_t footer = bytes < 0x40000U ? 4U : 8U;
    uintptr_t start;
    uintptr_t end;
    uint32_t heap_size;
    uint32_t bucket_index;
    uint32_t chunk0_size;
    uint32_t min_size;
    uint32_t bucket_bytes;
    volatile uint32_t *state;

    if (bytes <= footer) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f0796UL, 0x000f0692UL, 0x1f2U);
        printk(0x000f07b7UL);
        assert_post_action(0x000f0692UL, 0x1f2U);
    }

    bytes -= footer;
    start = ((uintptr_t)memory + 7U) & ~(uintptr_t)7U;
    end = ((uintptr_t)memory + bytes) & ~(uintptr_t)7U;
    heap_size = (uint32_t)((end - start) >> 3);

    if ((uint32_t)(end - start) <= 0x17U) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f07d0UL, 0x000f0692UL, 0x1fbU);
        printk(0x000f07b7UL);
        assert_post_action(0x000f0692UL, 0x1fbU);
    }

    state = (volatile uint32_t *)start;
    heap[0] = (uint32_t)start;
    state[2] = heap_size;
    state[3] = 0U;

    /* The leaf helper only consumes r0, but the shipped call preserves the
     * allocator geometry in r1-r3.  Keep that ABI-visible oracle state. */
    bucket_index = heap_bucket_index(heap_size, heap_size, bytes, footer);
    bucket_bytes = (bucket_index + 5U) * 4U;
    min_size = log_msg_compute_wlen(heap_size, 1U);
    chunk0_size = (bucket_bytes + 7U) >> 3;

    if (chunk0_size + min_size > heap_size) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f07f9UL, 0x000f0692UL, 0x20cU);
        printk(0x000f07b7UL);
        assert_post_action(0x000f0692UL, 0x20cU);
    }

    memset_bytes((void *)(start + 16U), 0U,
                  bucket_index == UINT32_MAX ? 0U : bucket_bytes - 16U);

    chunk_set_used_flag((void *)state, 0U, chunk0_size);
    chunk_set((void *)state, 0U, 0U, 0U);
    set_chunk_used((void *)state, 0U, 1U);

    chunk_set_used_flag((void *)state, chunk0_size, heap_size - chunk0_size);
    chunk_set((void *)state, chunk0_size, 0U, chunk0_size);

    chunk_set_used_flag((void *)state, heap_size, 0U);
    chunk_set((void *)state, heap_size, 0U, heap_size - chunk0_size);
    set_chunk_used((void *)state, heap_size, 1U);
    free_list_add((void *)state, chunk0_size);
}
