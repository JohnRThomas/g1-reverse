/* Reconstructed projector_clear_canvas @ 0x7d4ca  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_00086c78(uint32_t dst, uint32_t value, uint32_t length);

uint32_t projector_clear_canvas(uint8_t *context)
{
    return FUN_00086c78(*(volatile uint32_t *)(context + 0x24), 0,
                        *(volatile uint32_t *)(context + 0x350));
}
