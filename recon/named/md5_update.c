/* readable reconstruction; identity: FUN_0007d8f4 @ 0x0007d8f4
 * public-name: md5_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   md5_process_block                        <= FUN_00049acc @ 0x00049acc
 *   md5_update                               <= FUN_0007d8f4 @ 0x0007d8f4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* FUN_0007d8f4 @ 0x7d8f4 */
#include <stdint.h>

extern void memcpy(void *destination, const void *source, uint32_t length);
extern void md5_process_block(volatile unsigned int *, void *);

/* Feed bytes into a 64-byte block hash state while maintaining bit count. */
void md5_update(uint32_t *state, const uint8_t *input, uint32_t length)
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
        md5_process_block(state + 2, state + 6);
        consumed = space;
        while (consumed + 64 <= length) {
            md5_process_block(state + 2, input + consumed);
            consumed += 64;
        }
        used = 0;
    }
    memcpy((uint8_t *)state + 0x18 + used,
                 input + consumed, length - consumed);
}
