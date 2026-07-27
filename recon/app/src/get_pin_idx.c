/* Reconstructed get_pin_idx @ 0x65434  (CFG-directed candidate) */
#include <stdint.h>
unsigned long get_pin_idx(unsigned long pin) {
    const volatile uint8_t *port_offset = (const volatile uint8_t *)0x000f6ba7u;
    return (uint8_t)(port_offset[pin >> 5] + (pin & 0x1fu));
}
