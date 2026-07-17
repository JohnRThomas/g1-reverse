/* readable reconstruction; identity: FUN_0100f5d8 @ 0x0100f5d8
 * public-name: FUN_0100f5d8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_prng_state                         @ 0x21000ef4
 */
/* net-core FUN_0100f5d8 @ 0x0100f5d8
 * Readable role: finalize the network core's four-word random state.
 * Address back-map:
 *   sys_rand_get @ 0x01009204 (FUN_01009204 veneer)
 *   random_state @ 0x21000ef4
 */
#include <stdint.h>

/* This veneer forwards exactly buffer and length to its installed provider. */
extern void sys_rand_get(void *buffer, uint32_t length);

#define RANDOM_STATE ((volatile uint32_t *)0x21000ef4UL)

static inline uint32_t rotate_right(uint32_t value, unsigned int shift)
{
    return (value >> shift) | (value << (32U - shift));
}

void FUN_0100f5d8(void)
{
    const uint32_t output_multiplier = 0x9e3779bbU;
    uint32_t state_a;
    uint32_t state_b;
    uint32_t output_a;
    uint32_t output_b;

    /* The provider may legally return an all-zero seed; retry that one value. */
    do {
        sys_rand_get((void *)RANDOM_STATE, 8);
        state_a = RANDOM_STATE[0];
        state_b = RANDOM_STATE[1];
    } while ((state_a | state_b) == 0);

    /* Advance the two-word state and derive two non-simultaneously-zero words. */
    do {
        uint32_t xor_pair = state_b ^ state_a;
        uint32_t pre_shift_mix = xor_pair ^ rotate_right(state_a, 6);
        uint32_t mixed_a = pre_shift_mix ^ (xor_pair << 9);
        uint32_t mixed_b;

        output_a = rotate_right(output_multiplier * state_a, 27) * 5U;
        mixed_b = mixed_a ^ rotate_right(xor_pair, 19);
        output_b = rotate_right(output_multiplier * mixed_a, 27) * 5U;

        state_b = rotate_right(mixed_b, 19);
        state_a = mixed_b ^ (mixed_a >> 6) ^ (pre_shift_mix << 26) ^
                  (mixed_b << 9);
    } while ((output_a | output_b) == 0);

    RANDOM_STATE[0] = state_a;
    RANDOM_STATE[1] = state_b;
    RANDOM_STATE[2] = output_a;
    RANDOM_STATE[3] = output_b;
}
