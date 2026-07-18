#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e140 @ 0x0102e140
 * public-name: FUN_0102e140
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_net_current_thread_field_cache         @ 0x21004660
 *   g_net_tick_pending_cnt                   @ 0x21004668
 *   g_net_dev_init_done_flag                 @ 0x21004fad
 */
/* CPUNET Zephyr z_log_msg_post_finalize @ 0x0102e140.
 * Raw/address back-map: FUN_0102e140 / 0x0102e140.
 */
#include <stdint.h>

extern int32_t atomic_inc(volatile int32_t *); /* FUN_0103a294 */
extern int spin_lock_valid(void *); /* FUN_0103610c */
extern void spin_lock_acquire(void *); /* FUN_01036144 */
extern int log_process(void); /* FUN_0102df2c */
extern int spin_unlock_valid(void *); /* FUN_01036128 */
extern void assert_print(const void *, const void *, uint32_t); /* FUN_01039bbe */
extern void assert_panic(const void *, uint32_t); /* FUN_01039bb0 */
extern void k_timer_start(void *, uint64_t, uint64_t); /* FUN_01038448 */
extern void k_timer_stop(void *); /* FUN_0103b3a6 */
extern void k_sem_give(void *); /* FUN_01036824 */
#define z_log_msg_post_finalize FUN_0102e140

void z_log_msg_post_finalize(void)
{
    int32_t count = atomic_inc((volatile int32_t *)((unsigned long)&g_net_tick_pending_cnt) /*=0x21004668*/);

    if (*(volatile uint8_t *)((unsigned long)&g_net_dev_init_done_flag) /*=0x21004fad*/) {
        void *process_lock = (void *)0x21004658u;
        if (!spin_lock_valid(process_lock)) {
            assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                         (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
            assert_panic((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
        }
        spin_lock_acquire(process_lock);
        (void)log_process();
        if (!spin_unlock_valid(process_lock)) {
            assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                         (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
            assert_panic((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
        }
        return;
    }

    if (*(void * volatile *)((unsigned long)&g_net_current_thread_field_cache) /*=0x21004660*/ == 0)
        return;

    if (count == 0) {
        k_timer_start((void *)0x21002790u, 0x8000u, 0);
    } else if (count == 9) {
        k_timer_stop((void *)0x21002790u);
        k_sem_give((void *)0x21000944u);
    }
}
