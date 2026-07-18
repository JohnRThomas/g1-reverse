/* Reconstructed Zephyr free_chunk @ 0x0007e0a6.
 * Raw/address back-map: FUN_0007e0a6 / 0x0007e0a6.
 */
#include <stdint.h>

extern uint32_t FUN_0007de18(void *heap, uint32_t chunk);
extern uint32_t FUN_0007ddec(void *heap, uint32_t chunk, uint32_t side);
extern void FUN_0007def6(void *heap, uint32_t chunk);
extern void FUN_0007dfe6(void *heap, uint32_t left, uint32_t right);
extern void FUN_0007e022(void *heap, uint32_t chunk);

void free_chunk(void *heap, uint32_t chunk)
{
    uint32_t right = chunk + FUN_0007de18(heap, chunk);

    if ((FUN_0007ddec(heap, right, 1) & 1u) == 0u) {
        FUN_0007def6(heap, right);
        FUN_0007dfe6(heap, chunk, chunk + FUN_0007de18(heap, chunk));
    }

    uint32_t left = chunk - FUN_0007ddec(heap, chunk, 0);
    if ((FUN_0007ddec(heap, left, 1) & 1u) == 0u) {
        FUN_0007def6(heap, left);
        FUN_0007dfe6(heap, chunk - FUN_0007ddec(heap, chunk, 0), chunk);
        chunk -= FUN_0007ddec(heap, chunk, 0);
    }

    FUN_0007e022(heap, chunk);
}
