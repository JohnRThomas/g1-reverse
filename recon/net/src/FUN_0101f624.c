/* net-core FUN_0101f624 @ 0x101f624  (CFG-directed candidate) */
#include <stdint.h>
int32_t FUN_0101f624(const uint8_t *p) {
    volatile uint8_t *dst = (volatile uint8_t *)0x21000eacu;
    if (p[0] == 0 || p[1] == 0 || *(const uint16_t *)(p + 2) <= 0x1a || *(const uint16_t *)(p + 4) <= 0x1a) return 0x12;
    *(volatile uint32_t *)dst = *(const uint32_t *)p;
    *(volatile uint16_t *)(dst + 4) = *(const uint16_t *)(p + 4);
    return 0;
}
