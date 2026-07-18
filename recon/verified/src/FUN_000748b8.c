/* Reconstructed z_thread_abort @ 0x000748b8 from Zephyr sched.c.
 * Raw backmap: FUN_000748b8@0x000748b8, true code extent 0x166 bytes.
 *
 * This is the non-SMP Zephyr 3.4.99 path.  The scheduler spinlock is at
 * 0x2000b490 and the kernel's current-thread slot is 0x2000b448 + 8.
 */

#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_00072040(void *lock);
extern void FUN_00072078(void *lock);
extern int FUN_0007205c(void *lock);
extern void FUN_00074274(void *thread);
extern void FUN_00074d74(void *timeout);
extern void FUN_00073cdc(void *runq, void *thread);
extern void FUN_00073840(void *thread);
extern void FUN_000737d8(int reschedule);
extern void FUN_00050304(void *thread);
extern void FUN_000501d4(uint32_t key);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);

#define z_spin_lock_valid FUN_00072040
#define z_spin_lock_set_owner FUN_00072078
#define z_spin_unlock_valid FUN_0007205c
#define z_unpend_thread_no_timeout FUN_00074274
#define z_abort_thread_timeout FUN_00074d74
#define runq_remove FUN_00073cdc
#define ready_thread FUN_00073840
#define update_cache FUN_000737d8
#define arch_float_disable FUN_00050304
#define z_swap FUN_000501d4
#define assert_log FUN_0007e2fa
#define assert_panic FUN_0007e2ec

static inline __attribute__((always_inline)) int unlock_scheduler(void)
{
    return z_spin_unlock_valid((void *)0x2000b490u);
}

static inline __attribute__((always_inline)) void assert_unlock_succeeded(void)
{
    assert_log(0x00099cbdu, 0x000f08f4u, 0x000f08c7u, 0x00000111u);
    assert_log(0x000f090bu, 0x2000b490u);
    assert_panic(0x000f08c7u, 0x00000111u);
}

void z_thread_abort(void *thread_arg)
{
    uint8_t *thread = (uint8_t *)thread_arg;
    void *const scheduler_lock = (void *)0x2000b490u;
    uint32_t key = 0u; /* irq-lock key; original saves BASEPRI in r6 */

    if (z_spin_lock_valid(scheduler_lock) == 0) {
        assert_log(0x00099cbdu, 0x000f0920u, 0x000f08c7u, 0x00000072u);
        assert_log(0x000f0935u, 0x2000b490u);
        assert_panic(0x000f08c7u, 0x00000072u);
    }
    z_spin_lock_set_owner(scheduler_lock);

    if ((thread[0x0cu] & 0x01u) != 0u) { /* K_ESSENTIAL */
        if (unlock_scheduler() == 0) {
            assert_unlock_succeeded();
        }
        assert_log(0x00099cbdu, 0x000f7a30u, 0x000f82f4u, 0x000006d7u);
        assert_log(0x000f8698u, (uint32_t)(uintptr_t)thread);
        assert_panic(0x000f82f4u, 0x000006d7u);
        return;
    }

    uint8_t state = thread[0x0du];
    if ((state & 0x08u) != 0u) { /* _THREAD_DEAD */
        if (unlock_scheduler() == 0) {
            assert_unlock_succeeded();
        }
        return;
    }

    /* end_thread(): mark dead, clear aborting, and dequeue if ready. */
    thread[0x0du] = (uint8_t)((state & (uint8_t)~0x20u) | 0x08u);
    if ((state & 0x80u) != 0u) { /* _THREAD_QUEUED */
        thread[0x0du] = (uint8_t)((state & 0x5fu) | 0x08u);
        runq_remove((void *)0x2000b464u, thread);
    }

    if (*(void **)(thread + 0x08u) != (void *)0) {
        z_unpend_thread_no_timeout(thread);
    }
    z_abort_thread_timeout(thread + 0x18u);

    /* Wake every waiter on thread->join_queue (a sys_dlist at +0x58). */
    uint8_t *const join_queue = thread + 0x58u;
    for (;;) {
        uint8_t *waiter = *(uint8_t **)join_queue;
        if (waiter == join_queue || waiter == (uint8_t *)0) {
            break;
        }
        z_unpend_thread_no_timeout(waiter);
        z_abort_thread_timeout(waiter + 0x18u);
        *(uint32_t *)(waiter + 0x90u) = 0u;
        ready_thread(waiter);
    }

    update_cache(1);
    arch_float_disable(thread);

    uint8_t *current = *(uint8_t * volatile *)0x2000b450u;
    if (thread == current && __get_IPSR() == 0u) {
        if (unlock_scheduler() == 0) {
            assert_unlock_succeeded();
        }
        z_swap(key);
        assert_log(0x00099cbdu, 0x000f7a30u, 0x000f82f4u, 0x0000070du);
        assert_log(0x000f86b7u);
        assert_panic(0x000f82f4u, 0x0000070du);
        return;
    }

    if (unlock_scheduler() == 0) {
        assert_unlock_succeeded();
    }
}
