#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f5d8 @ 0x0100f5d8
 * public-name: sdc_controller_random_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_rand_poll                            <= FUN_01009204 @ 0x01009204
 *   sdc_controller_random_init               <= FUN_0100f5d8 @ 0x0100f5d8
 * address symbols (name @ address):
 *   g_net_prng_state                         @ 0x21000ef4
 */
/* net-core FUN_0100f5d8 @ 0x0100f5d8
 * Readable role: seed both controller xoroshiro64** streams.
 * Address back-map:
 *   sdc_rand_poll @ 0x01009204 (FUN_01009204 veneer)
 *   g_net_prng_state @ 0x21000ef4
 */
#include <stdint.h>

/* FUN_01009204 is the two-argument installed random-provider veneer. */
extern void sdc_rand_poll(void *buffer, uint32_t length);

#define RANDOM_STATE ((volatile uint32_t *)((unsigned long)&g_net_prng_state) /*=0x21000ef4*/)

static __attribute__((always_inline)) inline uint32_t
rotate_left(uint32_t value, unsigned int shift)
{
    return (value << shift) | (value >> (32U - shift));
}

void sdc_controller_random_init(void)
{
    const uint32_t output_multiplier = 0x9e3779bbU;
    uint32_t state_a;
    uint32_t state_b;
    uint32_t output_a;
    uint32_t output_b;

    /* The provider may legally return an all-zero seed; retry that one value. */
    do {
        sdc_rand_poll((void *)RANDOM_STATE, 8);
        state_a = RANDOM_STATE[0];
        state_b = RANDOM_STATE[1];
    } while ((state_a | state_b) == 0);

    /*
     * Generate two consecutive xoroshiro64** outputs.  Those outputs seed the
     * second stream, while the twice-advanced state seeds the first stream.
     * Retry the vanishingly rare pair which would make stream two all zero.
     */
    do {
        uint32_t first_xor = state_b ^ state_a;
        uint32_t next_a = rotate_left(state_a, 26) ^ first_xor ^
                          (first_xor << 9);
        uint32_t next_b = rotate_left(first_xor, 13);
        uint32_t second_xor = next_b ^ next_a;

        output_a = rotate_left(output_multiplier * state_a, 5) * 5U;
        output_b = rotate_left(output_multiplier * next_a, 5) * 5U;
        state_a = rotate_left(next_a, 26) ^ second_xor ^
                  (second_xor << 9);
        state_b = rotate_left(second_xor, 13);
    } while ((output_a | output_b) == 0);

    RANDOM_STATE[0] = state_a;
    RANDOM_STATE[1] = state_b;
    RANDOM_STATE[2] = output_a;
    RANDOM_STATE[3] = output_b;
}
