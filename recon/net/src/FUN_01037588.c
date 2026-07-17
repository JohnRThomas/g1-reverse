/* Zephyr pend_locked @ 0x01037588, exact extent 0x2c.
 * Raw/address backmaps:
 *   FUN_01037588@0x01037588
 *   add_to_waitq_locked = FUN_01037514@0x01037514
 *   z_add_timeout = FUN_01037f8c@0x01037f8c
 *   z_thread_timeout@0x0103bac9 (Thumb callback)
 */
#include <stdint.h>
#define pend_locked FUN_01037588

extern void FUN_01037514(void *thread, void *wait_queue);
extern void FUN_01037f8c(void *timeout, void *handler,
                         uint32_t ticks_low, int32_t ticks_high);
#define add_to_waitq_locked FUN_01037514
#define z_add_timeout FUN_01037f8c

void pend_locked(void *thread, void *wait_queue,
                 uint32_t ticks_low, int32_t ticks_high)
{
    add_to_waitq_locked(thread, wait_queue);
    if (ticks_high != -1 || ticks_low != UINT32_MAX) {
        z_add_timeout((uint8_t *)thread + 0x18,
                      (void *)0x0103bac9u, ticks_low, ticks_high);
    }
}
