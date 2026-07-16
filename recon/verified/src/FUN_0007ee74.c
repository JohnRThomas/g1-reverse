/* Full reconstruction FUN_0007ee74 @ 0x7ee74 (exact code extent 50 bytes). */
#include <stdint.h>
extern uint32_t FUN_0004d468(void *, uint32_t, uint32_t);
extern void FUN_00086c04(uint8_t *, uint32_t, uint32_t);
extern uint32_t FUN_0004d8b8(void *);
uint32_t FUN_0007ee74(uint32_t *object, uint32_t upper, uint32_t lower, uint32_t tag)
{
    if (object == 0) return FUN_0004d468(0, tag, lower >> 20);
    if (tag != 0) {
        unsigned offset = (lower >> 9) & 0x7ff;
        FUN_00086c04((uint8_t *)object + 16 + offset, tag, lower >> 20);
    }
    object[0] = lower;
    object[1] = upper;
    return FUN_0004d8b8(object);
}
