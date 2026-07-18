/* readable reconstruction; identity: FUN_00063654 @ 0x00063654
 * public-name: compare_set
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   g_20006690                               @ 0x20006690
 *   g_gpio_pin_latch_mask                    @ 0x2000b2d0
 *   g_gpio_pin_enabled_mask                  @ 0x2000b2d8
 */
/* compare_set @ 0x00063654; raw FUN_00063654 */
#include <stdint.h>

typedef void (*compare_handler_t)(int32_t, uint64_t, void *);

struct compare_channel {
    compare_handler_t callback;
    void *context;
    uint64_t target;
};

#ifdef G1_APP_SDK_INLINE_COHESION
/* Exact Zephyr 3.4.99 nrf_rtc_timer.c local owners (receipt baa02453..., lines
 * 155 and 83). The event readback is required by the Nordic HAL contract. */
static __attribute__((always_inline)) inline int
g1_compare_int_lock_inline(int32_t channel)
{
    uint32_t bit = 1U << channel;
    uint32_t previous = __atomic_fetch_and((uint32_t *)0x2000b2d8U, ~bit,
                                           __ATOMIC_SEQ_CST);
    *(volatile uint32_t *)(0x50015000U + 0x308U) = 0x10000U << channel;
    __asm__ volatile("dmb sy" ::: "memory");
    __asm__ volatile("isb sy" ::: "memory");
    return (previous & bit) != 0U;
}

static __attribute__((always_inline)) inline void
g1_event_clear_inline(int32_t channel)
{
    volatile uint32_t *event =
        (volatile uint32_t *)(0x50015000U + 0x140U + (uint32_t)channel * 4U);
    *event = 0U;
    (void)*event;
}
#define compare_int_lock g1_compare_int_lock_inline
#define event_clear g1_event_clear_inline
#else
extern int compare_int_lock(int32_t); /* FUN_0006349c */
extern void event_clear(int32_t); /* FUN_00084c5e */
#endif
extern uint64_t rtc_read_extended_cycle_count(void); /* FUN_00063610 */
extern void compare_int_unlock(int32_t, int); /* FUN_00063524 */

int compare_set(int32_t channel, uint64_t target, compare_handler_t callback,
                void *context, int exact)
{
    int key = compare_int_lock(channel);
    uint64_t current = rtc_read_extended_cycle_count();
    int result = 0;
    struct compare_channel *channels =
        (struct compare_channel *)0x20006690u;
    volatile uint32_t *rtc = (volatile uint32_t *)0x50015000u;

    if (current < target) {
        if (target - current > 0x800000u) {
            result = -22;
            goto out;
        }
        if (target != channels[channel].target) {
            uint32_t interrupt = 0x10000u << channel;
            uint32_t requested = (uint32_t)target & 0xffffffu;
            uint32_t increment = 3;

            rtc[0x348 / 4] = interrupt;
            event_clear(channel);
            for (;;) {
                rtc[(0x540 / 4) + channel] = requested;
                rtc[0x344 / 4] = interrupt;
                uint32_t now = rtc[0x504 / 4];

                if (((requested - now - 3u) & 0xffffffu) <= 0x7ffffdu) {
                    break;
                }
                if (rtc[(0x140 / 4) + channel] != 0) {
                    now = rtc[0x504 / 4];
                    if (((now - ((uint32_t)target & 0xffffffu)) & 0xffffffu) <
                        0x800001u) {
                        break;
                    }
                    event_clear(channel);
                }
                if (exact) {
                    result = -22;
                    goto out;
                }
                requested = (now + increment) & 0xffffffu;
                increment++;
            }
        }
    } else if (!exact) {
        __atomic_fetch_or((uint32_t *)0x2000b2d0u, 1u << channel,
                          __ATOMIC_RELAXED);
    } else {
        result = -22;
        goto out;
    }

    channels[channel].callback = callback;
    channels[channel].target = target;
    channels[channel].context = context;
out:
    compare_int_unlock(channel, key);
    return result;
}
