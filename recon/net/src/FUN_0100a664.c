/* net-core FUN_0100a664 @ 0x100a664 */
#include <stdint.h>

extern void FUN_01008d00(uint32_t, uint32_t);
extern int32_t FUN_010279e6(uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_01027258(uint32_t *, uint32_t);

uint32_t FUN_0100a664(uint32_t raw_id, uint32_t raw_count,
                      uint32_t value, uint32_t raw_mode)
{
    uint32_t id = (uint32_t)raw_id & 0xffu;
    uint32_t count = (uint32_t)raw_count & 0xffu;
    uint32_t mode = (uint32_t)raw_mode & 0xffu;

    if ((value & 7u) == 0 || (value & 3u) != 0) {
        FUN_01008d00(0x4cu, 0x1fu);
    }

    int32_t scale = FUN_010279e6(0, id, 0x10eu);
    uint32_t *value_pointer = mode == 0 ? &value : (uint32_t *)0;
    uint32_t result = FUN_01027258(value_pointer, (uint32_t)scale * count);

    if (mode != 1u) {
        *(volatile uint32_t *)0x21000becu = value;
        *(volatile int32_t *)0x21000bf0u = scale;
    }
    return result;
}
