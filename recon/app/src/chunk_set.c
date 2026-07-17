/* chunk_set @ 0x0007de02; raw FUN_0007de02 */
#include <stdint.h>

void chunk_set(uint8_t *heap, uint32_t chunk, uint32_t field, uint32_t value)
{
    uint8_t *memory = heap + chunk * 8u;

    if (*(uint32_t *)(heap + 8) < 0x8000u) {
        ((uint16_t *)memory)[field] = (uint16_t)value;
    } else {
        ((uint32_t *)memory)[field] = value;
    }
}
