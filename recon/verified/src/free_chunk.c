/* Reconstructed Zephyr free_chunk @ 0x0007e0a6.
 * Raw/address back-map: FUN_0007e0a6 / 0x0007e0a6.
 */
#include <stdint.h>

extern uint32_t FUN_0007de18(void *heap, uint32_t chunk);
extern uint32_t FUN_0007ddec(void *heap, uint32_t chunk, uint32_t side);
#ifdef G1_APP_SDK_INLINE_COHESION
extern int FUN_0007de82(uint32_t end_chunk, uint32_t size);
extern void FUN_0007de02(unsigned char *, unsigned int, unsigned int, unsigned int);
extern void FUN_0007de54(void *heap, uint32_t chunk, uint32_t size);

/* Exact Zephyr 3.4.99 heap.c locals.  They are always-inline and TU-local so
 * the cohesive build exports no duplicate helper owner; parity mode keeps the
 * original call boundaries through the extern branch below.
 */
static __attribute__((always_inline)) inline void free_list_remove_bidx(
    void *heap_arg, uint32_t chunk, int bucket_index)
{
    uint8_t *heap = (uint8_t *)heap_arg;
    uint32_t next = FUN_0007ddec(heap, chunk, 3u);

    if (next == chunk) {
        *(uint32_t *)(heap + 0x0cu) &= ~(1u << (bucket_index & 0xff));
        *(uint32_t *)(heap + 0x10u + (uint32_t)bucket_index * 4u) = 0u;
    } else {
        uint32_t previous = FUN_0007ddec(heap, chunk, 2u);
        *(uint32_t *)(heap + 0x10u + (uint32_t)bucket_index * 4u) = next;
        FUN_0007de02(heap, previous, 3u, next);
        FUN_0007de02(heap, next, 2u, previous);
    }
}

static __attribute__((always_inline)) inline void free_list_remove(
    void *heap_arg, uint32_t chunk)
{
    uint8_t *heap = (uint8_t *)heap_arg;
    uint32_t size = FUN_0007de18(heap, chunk);

    if (*(uint32_t *)(heap + 8u) >= 0x8000u && size == 1u)
        return;
    free_list_remove_bidx(heap, chunk,
                          FUN_0007de82(*(uint32_t *)(heap + 8u), size));
}

static __attribute__((always_inline)) inline void merge_chunks(
    void *heap, uint32_t left, uint32_t right)
{
    uint32_t merged = FUN_0007de18(heap, left) +
                      FUN_0007de18(heap, right);
    FUN_0007de54(heap, left, merged);
    FUN_0007de02(heap, right + FUN_0007de18(heap, right), 0u, merged);
}
#else
extern void FUN_0007def6(void *heap, uint32_t chunk);
extern void FUN_0007dfe6(void *heap, uint32_t left, uint32_t right);
#define free_list_remove FUN_0007def6
#define merge_chunks FUN_0007dfe6
#endif
extern void FUN_0007e022(void *heap, uint32_t chunk);

void free_chunk(void *heap, uint32_t chunk)
{
    uint32_t right = chunk + FUN_0007de18(heap, chunk);

    if ((FUN_0007ddec(heap, right, 1) & 1u) == 0u) {
        free_list_remove(heap, right);
        merge_chunks(heap, chunk, chunk + FUN_0007de18(heap, chunk));
    }

    uint32_t left = chunk - FUN_0007ddec(heap, chunk, 0);
    if ((FUN_0007ddec(heap, left, 1) & 1u) == 0u) {
        free_list_remove(heap, left);
        merge_chunks(heap, chunk - FUN_0007ddec(heap, chunk, 0), chunk);
        chunk -= FUN_0007ddec(heap, chunk, 0);
    }

    FUN_0007e022(heap, chunk);
}
