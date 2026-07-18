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
    int32_t count = atomic_inc((volatile int32_t *)0x21004668u);

    if (*(volatile uint8_t *)0x21004fadu) {
        void *process_lock = (void *)0x21004658u;
        if (!spin_lock_valid(process_lock)) {
            assert_print((const void *)0x0103d2a7u,
                         (const void *)0x0103d3b6u, 0x72u);
            assert_panic((const void *)0x0103d3b6u, 0x72u);
        }
        spin_lock_acquire(process_lock);
        (void)log_process();
        if (!spin_unlock_valid(process_lock)) {
            assert_print((const void *)0x0103d2a7u,
                         (const void *)0x0103d3b6u, 0xf0u);
            assert_panic((const void *)0x0103d3b6u, 0xf0u);
        }
        return;
    }

    if (*(void * volatile *)0x21004660u == 0)
        return;

    if (count == 0) {
        k_timer_start((void *)0x21002790u, 0x8000u, 0);
    } else if (count == 9) {
        k_timer_stop((void *)0x21002790u);
        k_sem_give((void *)0x21000944u);
    }
}
