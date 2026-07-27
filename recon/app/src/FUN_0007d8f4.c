/* FUN_0007d8f4 @ 0x7d8f4 */
#include <stdint.h>

extern void FUN_00086c04(void *destination, const void *source, uint32_t length);
extern void FUN_00049acc(volatile unsigned int *, void *);

/* Feed bytes into a 64-byte block hash state while maintaining bit count. */
void FUN_0007d8f4(uint32_t *state, const uint8_t *input, uint32_t length)
{
    uint32_t used = (state[0] >> 3) & 0x3f;
    uint32_t old_low = state[0];
    state[0] = old_low + (length << 3);
    if (state[0] < old_low)
        state[1]++;
    state[1] += length >> 29;

    uint32_t consumed = 0;
    uint32_t space = 64 - used;
    if (length >= space) {
        FUN_00086c04((uint8_t *)state + 0x18 + used, input, space);
        FUN_00049acc(state + 2, state + 6);
        consumed = space;
        while (consumed + 64 <= length) {
            FUN_00049acc(state + 2, input + consumed);
            consumed += 64;
        }
        used = 0;
    }
    FUN_00086c04((uint8_t *)state + 0x18 + used,
                 input + consumed, length - consumed);
}
