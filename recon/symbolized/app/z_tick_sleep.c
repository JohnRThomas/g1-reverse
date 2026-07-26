#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000746fc @ 0x000746fc
 * public-name: z_tick_sleep
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   unready_thread                           <= FUN_00073e88 @ 0x00073e88
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   z_tick_sleep                             <= FUN_000746fc @ 0x000746fc
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   get_uptime_ms                            <= FUN_00086690 @ 0x00086690
 * address symbols (name @ address):
 *   rodata_86661                             @ 0x00086661
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f8658                             @ 0x000f8658
 *   _kernel                                  @ 0x2000b448
 *   g_pend_locked_thread_tmp                 @ 0x2000b484
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_000746fc @ 0x746fc.
 * CFG_VERIFY_CALL_ARITIES=3,1,1,0,4,1,1,4,1,2
 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void mutex_unlock_syscall_handler(void);
extern int32_t get_uptime_ms(uint32_t, int32_t, ...);
extern int z_spin_lock_valid(uintptr_t);
extern void z_spin_lock_set_owner(uintptr_t);
extern int z_spin_unlock_valid(uintptr_t);
extern void unready_thread(void *thread);
extern void z_add_timeout(void *, uintptr_t, uint32_t, int32_t);
extern void arch_swap(uint32_t);
extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uintptr_t);

int32_t z_tick_sleep(uint32_t lo, int32_t hi)
{
    uint32_t exception = __get_IPSR() & 0x1fU;
    if (exception != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f801f) /*=0xf801f*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x596);
        printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
        assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x596);
    }
    if ((lo | (uint32_t)hi) == 0) {
        mutex_unlock_syscall_handler();
        return 0;
    }

    uint32_t target;
    int64_t requested = ((int64_t)hi << 32) | lo;
    if (requested >= -1)
        target = lo + (uint32_t)get_uptime_ms(lo, hi, lo + 2U);
    else
        target = 0U - lo - 2U;

    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (z_spin_lock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
    }
    z_spin_lock_set_owner(((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    volatile uint8_t *thread = *(volatile uint8_t **)(uintptr_t)(((unsigned long)&_kernel) /*=0x2000b448*/ + 8);
    *(uint32_t *)(uintptr_t)((unsigned long)&g_pend_locked_thread_tmp) /*=0x2000b484*/ = (uint32_t)(uintptr_t)thread;
    /* BRING-UP WIRING FIX (P4 iteration 5) — dropped call argument.
     * Zephyr's z_tick_sleep does `unready_thread(_current)`; the original bytes
     * at 0x74786 load r0 = _current (`ldr r0,[r7,#8]`) immediately before
     * `bl 0x73e88` (unready_thread).  The reconstruction declared the callee
     * `void unready_thread(void)` and called it with no argument, which only
     * worked because the ORIGINAL codegen happened to leave _current in r0.
     * Our codegen loads _current into r2 and leaves r0 = &sched_spinlock, so
     * unready_thread() ran on the spinlock object and then called
     * update_cache(0) -- the sleeping thread stayed in the ready cache, z_swap
     * returned to it immediately, and the following
     * __ASSERT(!_THREAD_SUSPENDED) (sched.c:1458) tripped a kernel OOPS.
     * Build/wiring TU only; recon/app/src is untouched. */
    unready_thread((void *)thread);
    thread = *(volatile uint8_t * volatile *)(uintptr_t)(((unsigned long)&_kernel) /*=0x2000b448*/ + 8);
    z_add_timeout((void *)(thread + 0x18), ((unsigned long)&rodata_86661) /*=0x86661*/, lo, hi);
    thread[0xd] |= 0x10;
    if (z_spin_unlock_valid(((unsigned long)&sched_spinlock) /*=0x2000b490*/) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x111);
        printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x111);
    }
    arch_swap(key);
    thread = *(volatile uint8_t * volatile *)(uintptr_t)(((unsigned long)&_kernel) /*=0x2000b448*/ + 8);
    if ((thread[0xd] & 0x10) != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f8658) /*=0xf8658*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x5b2);
        printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
        assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x5b2);
    }
    uint32_t now = (uint32_t)get_uptime_ms(0, 0);
    return target > now ? (int32_t)(target - now) : 0;
}
