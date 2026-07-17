/* net-core FUN_0100a5c8 @ 0x100a5c8 */

#include <stdint.h>

extern void FUN_01008d00(uint32_t group, uint32_t line);
extern int FUN_01027742(uint32_t type, uint32_t field, uint32_t value);
extern void FUN_010276e6(uintptr_t destination, uint32_t stride, uint32_t type,
                         uint32_t field, uint32_t value);

int FUN_0100a5c8(uintptr_t destination, uint32_t count_arg, uint32_t value_arg)
{
    uint8_t count = (uint8_t)count_arg;
    uint8_t value = (uint8_t)value_arg;
    uint16_t stride = (uint16_t)((uint16_t)(FUN_01027742(0xf7u, 5u, value) + 3) & 0xfffcu);

    if (destination != 0u) {
        if ((destination & 3u) != 0u) {
            FUN_01008d00(0x19u, 0x95u);
        }
        *(volatile uintptr_t *)0x21000be4u = destination;
        *(volatile uint16_t *)0x21000be8u = stride;
        for (uint16_t index = 0; index < count; ++index) {
            FUN_010276e6(*(volatile uintptr_t *)0x21000be4u +
                             (uint32_t)*(volatile uint16_t *)0x21000be8u * index,
                         stride, 0xf7u, 5u, value);
        }
    }
    return (uint32_t)stride * count;
}
