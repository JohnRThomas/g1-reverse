#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000748b8 @ 0x000748b8
 * public-name: z_thread_abort
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   mpu_region_index_lookup                  <= FUN_00050304 @ 0x00050304
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   sched_ready_queue_insert                 <= FUN_00073840 @ 0x00073840
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   z_abort_timeout                          <= FUN_00074d74 @ 0x00074d74
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f7a30                             @ 0x000f7a30
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f8698                             @ 0x000f8698
 *   rodata_f86b7                             @ 0x000f86b7
 *   _kernel                                  @ 0x2000b448
 *   g_current_thread_ptr                     @ 0x2000b450
 *   g_sched_ready_runq                       @ 0x2000b464
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed z_thread_abort @ 0x000748b8 from Zephyr sched.c.
 * Raw backmap: FUN_000748b8@0x000748b8, true code extent 0x166 bytes.
 *
 * This is the non-SMP Zephyr 3.4.99 path.  The scheduler spinlock is at
 * 0x2000b490 and the kernel's current-thread slot is 0x2000b448 + 8.
 */

#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../../headers/g1_log.h"

extern int z_spin_lock_valid(void *lock);
extern void z_spin_lock_set_owner(void *lock);
extern int z_spin_unlock_valid(void *lock);
extern void z_abort_thread_timeout(void *thread);
extern void z_abort_timeout(void *timeout);
extern void dlist_unlink_node(void *runq, void *thread);
extern void sched_ready_queue_insert(void *thread);
extern void sched_update_cache(int reschedule);
extern void mpu_region_index_lookup(void *thread);
extern void arch_swap(uint32_t key);
extern void assert_post_action(uint32_t, uint32_t);

#define z_spin_lock_valid z_spin_lock_valid
#define z_spin_lock_set_owner z_spin_lock_set_owner
#define z_spin_unlock_valid z_spin_unlock_valid
#define z_unpend_thread_no_timeout z_abort_thread_timeout
#define z_abort_thread_timeout z_abort_timeout
#define runq_remove dlist_unlink_node
#define ready_thread sched_ready_queue_insert
#define update_cache sched_update_cache
#define arch_float_disable mpu_region_index_lookup
#define z_swap arch_swap
#define assert_log printk
#define assert_panic assert_post_action

static inline __attribute__((always_inline)) int unlock_scheduler(void)
{
    return z_spin_unlock_valid((void *)((unsigned long)&sched_spinlock) /*=0x2000b490*/);
}

static inline __attribute__((always_inline)) void assert_unlock_succeeded(void)
{
    assert_log(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x00000111u);
    assert_log(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    assert_panic(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x00000111u);
}

void z_thread_abort(void *thread_arg)
{
    uint8_t *thread = (uint8_t *)thread_arg;
    void *const scheduler_lock = (void *)((unsigned long)&sched_spinlock) /*=0x2000b490*/;
    uint32_t key = 0u; /* irq-lock key; original saves BASEPRI in r6 */

    if (z_spin_lock_valid(scheduler_lock) == 0) {
        assert_log(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x00000072u);
        assert_log(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
        assert_panic(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x00000072u);
    }
    z_spin_lock_set_owner(scheduler_lock);

    if ((thread[0x0cu] & 0x01u) != 0u) { /* K_ESSENTIAL */
        if (unlock_scheduler() == 0) {
            assert_unlock_succeeded();
        }
        assert_log(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x000006d7u);
        assert_log(((unsigned long)&rodata_f8698) /*=0xf8698*/, (uint32_t)(uintptr_t)thread);
        assert_panic(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x000006d7u);
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
        runq_remove((void *)((unsigned long)&g_sched_ready_runq) /*=0x2000b464*/, thread);
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

    uint8_t *current = *(uint8_t * volatile *)((unsigned long)&g_current_thread_ptr) /*=0x2000b450*/;
    if (thread == current && __get_IPSR() == 0u) {
        if (unlock_scheduler() == 0) {
            assert_unlock_succeeded();
        }
        z_swap(key);
        assert_log(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x0000070du);
        assert_log(((unsigned long)&rodata_f86b7) /*=0xf86b7*/);
        assert_panic(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x0000070du);
        return;
    }

    if (unlock_scheduler() == 0) {
        assert_unlock_succeeded();
    }
}
