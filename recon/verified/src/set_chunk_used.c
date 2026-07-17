/* set_chunk_used @ 0x0007de24; raw FUN_0007de24 */
#include <stdint.h>

void set_chunk_used(uint8_t *heap, uint32_t chunk, int used)
{
    uint8_t *p = heap + chunk * 8u;

    if (*(uint32_t *)(heap + 8) < 0x8000u) {
        uint16_t *field = (uint16_t *)(p + 2);
        *field = used ? (uint16_t)(*field | 1u) : (uint16_t)(*field & ~1u);
    } else {
        uint32_t *field = (uint32_t *)(p + 4);
        *field = used ? (*field | 1u) : (*field & ~1u);
    }
}
