/* split_chunks @ 0x0007df98; raw FUN_0007df98 */
#include <stdint.h>

extern uint32_t chunk_size(uint8_t *, uint32_t); /* FUN_0007de18 */
extern void set_chunk_size(uint8_t *, uint32_t, uint32_t); /* FUN_0007de54 */
extern void chunk_set(uint8_t *, uint32_t, uint32_t, uint32_t); /* FUN_0007de02 */

void split_chunks(uint8_t *heap, uint32_t left, uint32_t right)
{
    uint32_t original = chunk_size(heap, left);
    uint32_t left_size = right - left;
    uint32_t right_size = original - left_size;

    set_chunk_size(heap, left, left_size);
    set_chunk_size(heap, right, right_size);
    chunk_set(heap, right, 0, left_size);
    chunk_set(heap, right + chunk_size(heap, right), 0, right_size);
}
