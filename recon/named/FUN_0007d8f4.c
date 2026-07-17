/* readable reconstruction; identity: FUN_0007d8f4 @ 0x0007d8f4
 * public-name: FUN_0007d8f4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* FUN_0007d8f4 @ 0x7d8f4 */
#include <stdint.h>

extern void memcpy(void *destination, const void *source, uint32_t length);
extern void FUN_00049acc(void *state, const void *block);

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
        memcpy((uint8_t *)state + 0x18 + used, input, space);
        FUN_00049acc(state + 2, state + 6);
        consumed = space;
        while (consumed + 64 <= length) {
            FUN_00049acc(state + 2, input + consumed);
            consumed += 64;
        }
        used = 0;
    }
    memcpy((uint8_t *)state + 0x18 + used,
                 input + consumed, length - consumed);
}
