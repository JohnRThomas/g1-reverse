/* readable reconstruction; identity: FUN_00075174 @ 0x00075174
 * public-name: z_impl_k_timer_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   z_abort_timeout                          <= FUN_00074d74 @ 0x00074d74
 * address symbols (name @ address):
 *   rodata_75005                             @ 0x00075005
 */
/* Reconstructed z_impl_k_timer_start @ 0x00075174 (FUN_00075174). */
#include <stdint.h>

typedef struct { int64_t ticks; } k_timeout_t;
struct recovered_k_timer {
    uint8_t timeout[0x28];
    k_timeout_t period;
    uint32_t status;
};

extern int z_abort_timeout(void *timeout);
extern void z_add_timeout(void *timeout, void (*handler)(void *),
                         int64_t ticks);
#define z_abort_timeout z_abort_timeout
#define z_add_timeout z_add_timeout

void z_impl_k_timer_start(struct recovered_k_timer *timer,
                          k_timeout_t duration, k_timeout_t period)
{
    if (duration.ticks == -1) {
        return;
    }
    if (duration.ticks >= 0) {
        duration.ticks = duration.ticks > 0 ? duration.ticks - 1 : 0;
    }
    (void)z_abort_timeout(timer);
    volatile uint32_t *const timer_words = (volatile uint32_t *)timer;
    uint64_t period_bits = (uint64_t)period.ticks;
    timer_words[0x28u / 4u] = (uint32_t)period_bits;
    timer_words[0x2cu / 4u] = (uint32_t)(period_bits >> 32);
    timer_words[0x30u / 4u] = 0u;
    z_add_timeout(timer, (void (*)(void *))0x00075005u, duration.ticks);
}
