/* net-core FUN_010268ce @ 0x010268ce, exact Thumb extent 0x44 bytes. */
#include <stdint.h>

/* True when two wrapped 15-bit positions agree but occupy opposite epochs. */
uint8_t FUN_010268ce(uint16_t first, uint16_t second)
{
    uint16_t difference = (uint16_t)(first ^ second);
    return (uint8_t)(((difference & 0x7fffu) == 0u) &&
                     ((int16_t)difference < 0));
}
