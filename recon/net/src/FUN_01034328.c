/* net-core FUN_01034328 @ 0x01034328
 * Readable role: atomically claim the highest-numbered free resource.
 *
 * Raw/address provenance:
 *   code [0x01034328, 0x0103435e)
 *   status literals [0x01034360, 0x01034368)
 *   callers: FUN_01034458, FUN_01034480, FUN_010346d8
 *   g_sdc_res_pool_free_bitmap @ 0x210006a4 is one concrete owner;
 *   g_net_dppi_chan_ctx        @ 0x210006a0 is the other.
 */
#include <stdint.h>

enum {
    RESOURCE_CLAIM_OK = 0x0bad0000U,
    RESOURCE_CLAIM_EMPTY = 0x0bad0002U
};

uint32_t FUN_01034328(volatile uint32_t *free_bitmap,
                      uint8_t *claimed_index)
{
    /* The shipped fast probe is an ordinary load before the acquire/release
     * exclusive compare-exchange loop. */
    uint32_t observed = *free_bitmap;

    while (observed != 0) {
        unsigned int bit = 31U - (unsigned int)__builtin_clz(observed);
        uint32_t desired = observed & ~(1U << bit);
        uint32_t expected = observed;

        if (__atomic_compare_exchange_n(
                free_bitmap, &expected, desired, 0,
                __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
            *claimed_index = (uint8_t)bit;
            return RESOURCE_CLAIM_OK;
        }

        /* A competing claimant changed the word. The shipped loop performs
         * a fresh ordinary load before selecting the next highest bit. */
        observed = *free_bitmap;
    }

    return RESOURCE_CLAIM_EMPTY;
}
