/* Reconstructed projector_flush_canvas @ 0x7d4d6  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_0007d70a(uint32_t x, uint32_t y, uint32_t buf, uint32_t length);

uint32_t projector_flush_canvas(uint8_t *context)
{
    if (*(volatile uint32_t *)(context + 0x35c) == 0)
        return (uint32_t)context;
    return FUN_0007d70a(*(volatile uint32_t *)(context + 0x348),
                        *(volatile uint32_t *)(context + 0x34c),
                        *(volatile uint32_t *)(context + 0x24),
                        *(volatile uint32_t *)(context + 0x350));
}
