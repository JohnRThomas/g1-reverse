/* Reconstructed FUN_0004b3c8 @ 0x4b3c8
 * Readable identity: sys_heap_init (Zephyr 3.4.99).
 * Raw/address backmap: sys_heap_init <= FUN_0004b3c8 @ 0x0004b3c8.
 */
#include <stdint.h>

extern void FUN_0007e2fa(uint32_t, ...); /* printk */
extern void FUN_0007e2ec(uint32_t, uint32_t); /* assert_post_action */
extern uint32_t FUN_0007de82(uint32_t, uint32_t, uint32_t, uint32_t); /* bucket_idx */
extern uint32_t FUN_0007de70(uint32_t, uint32_t); /* chunksz */
extern void *FUN_00086c78(void *, uint32_t, uint32_t); /* memset */
extern void FUN_0007de54(void *, uint32_t, uint32_t); /* set_left_chunk_size */
extern void FUN_0007de02(void *, uint32_t, uint32_t, uint32_t); /* chunk_set */
extern void FUN_0007de24(void *, uint32_t, uint32_t); /* set_chunk_used */
extern void FUN_0007e022(void *, uint32_t); /* free_list_add */

void FUN_0004b3c8(uint32_t *heap, void *memory, uint32_t bytes)
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
        FUN_0007e2fa(0x00099cbdUL, 0x000f0796UL, 0x000f0692UL, 0x1f2U);
        FUN_0007e2fa(0x000f07b7UL);
        FUN_0007e2ec(0x000f0692UL, 0x1f2U);
    }

    bytes -= footer;
    start = ((uintptr_t)memory + 7U) & ~(uintptr_t)7U;
    end = ((uintptr_t)memory + bytes) & ~(uintptr_t)7U;
    heap_size = (uint32_t)((end - start) >> 3);

    if ((uint32_t)(end - start) <= 0x17U) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f07d0UL, 0x000f0692UL, 0x1fbU);
        FUN_0007e2fa(0x000f07b7UL);
        FUN_0007e2ec(0x000f0692UL, 0x1fbU);
    }

    state = (volatile uint32_t *)start;
    heap[0] = (uint32_t)start;
    state[2] = heap_size;
    state[3] = 0U;

    /* The leaf helper only consumes r0, but the shipped call preserves the
     * allocator geometry in r1-r3.  Keep that ABI-visible oracle state. */
    bucket_index = FUN_0007de82(heap_size, heap_size, bytes, footer);
    bucket_bytes = (bucket_index + 5U) * 4U;
    min_size = FUN_0007de70(heap_size, 1U);
    chunk0_size = (bucket_bytes + 7U) >> 3;

    if (chunk0_size + min_size > heap_size) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f07f9UL, 0x000f0692UL, 0x20cU);
        FUN_0007e2fa(0x000f07b7UL);
        FUN_0007e2ec(0x000f0692UL, 0x20cU);
    }

    FUN_00086c78((void *)(start + 16U), 0U,
                  bucket_index == UINT32_MAX ? 0U : bucket_bytes - 16U);

    FUN_0007de54((void *)state, 0U, chunk0_size);
    FUN_0007de02((void *)state, 0U, 0U, 0U);
    FUN_0007de24((void *)state, 0U, 1U);

    FUN_0007de54((void *)state, chunk0_size, heap_size - chunk0_size);
    FUN_0007de02((void *)state, chunk0_size, 0U, chunk0_size);

    FUN_0007de54((void *)state, heap_size, 0U);
    FUN_0007de02((void *)state, heap_size, 0U, heap_size - chunk0_size);
    FUN_0007de24((void *)state, heap_size, 1U);
    FUN_0007e022((void *)state, chunk0_size);
}
