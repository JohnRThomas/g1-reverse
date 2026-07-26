#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_timer__param_0414                    [param_0414; library]
 * Raw function identity: 0x00074bf4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00074bf4 @ 0x00074bf4
 * public-name: z_add_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_clock_set_timeout                    <= FUN_000638dc @ 0x000638dc
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   rtc_get_elapsed_cycles_since_baseline    <= FUN_00074b68 @ 0x00074b68
 *   next_timeout                             <= FUN_00074b7c @ 0x00074b7c
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f86d9                             @ 0x000f86d9
 *   rodata_f86fd                             @ 0x000f86fd
 *   g_20002cfc                               @ 0x20002cfc
 *   g_curr_tick_lo                           @ 0x200069e0
 *   g_timeout_list_spinlock                  @ 0x2000b498
 */
/* Reconstructed FUN_00074bf4 @ 0x74bf4. */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int z_spin_lock_valid(uintptr_t);
extern void z_spin_lock_set_owner(uintptr_t);
extern int z_spin_unlock_valid(uintptr_t);
extern uint32_t rtc_get_elapsed_cycles_since_baseline(void);
extern uint32_t next_timeout(void);
extern void sys_clock_set_timeout(uint32_t, uint32_t);
extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uintptr_t);

void z_add_timeout(uint32_t *timer, uintptr_t source, uint32_t lo, int32_t hi)
{
    int64_t delay = ((int64_t)hi << 32) | lo;
    if (delay == -1) return;
    if (timer[0] != 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f86fd) /*=0xf86fd*/, ((unsigned long)&rodata_f86d9) /*=0xf86d9*/, 0x6e);
        printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
        assert_post_action(((unsigned long)&rodata_f86d9) /*=0xf86d9*/, 0x6e);
    }
    timer[2] = (uint32_t)source;
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (z_spin_lock_valid(((unsigned long)&g_timeout_list_spinlock) /*=0x2000b498*/) == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, ((unsigned long)&g_timeout_list_spinlock) /*=0x2000b498*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
    }
    z_spin_lock_set_owner(((unsigned long)&g_timeout_list_spinlock) /*=0x2000b498*/);

    uint64_t ticks;
    if (delay >= -1) {
        ticks = (uint64_t)delay + 1U + (int32_t)rtc_get_elapsed_cycles_since_baseline();
    } else {
        int64_t limit = -(int64_t)*(uint64_t *)(uintptr_t)((unsigned long)&g_curr_tick_lo) /*=0x200069e0*/ - 2;
        int64_t remaining = limit - delay;
        ticks = remaining < 1 ? 1 : (uint64_t)remaining;
    }
    timer[4] = (uint32_t)ticks;
    timer[5] = (uint32_t)(ticks >> 32);

    uint32_t *head = (uint32_t *)(uintptr_t)((unsigned long)&g_20002cfc) /*=0x20002cfc*/;
    uint32_t *tail = (uint32_t *)(uintptr_t)head[1];
    uint32_t *it = head[0] == (uint32_t)(uintptr_t)head ? 0 : (uint32_t *)(uintptr_t)head[0];
    while (it != 0) {
        uint64_t span = ((uint64_t)it[5] << 32) | it[4];
        uint64_t wanted = ((uint64_t)timer[5] << 32) | timer[4];
        if (wanted < span) {
            tail = (uint32_t *)(uintptr_t)it[1];
            span -= wanted;
            it[4] = (uint32_t)span;
            it[5] = (uint32_t)(span >> 32);
            timer[0] = (uint32_t)(uintptr_t)it;
            timer[1] = (uint32_t)(uintptr_t)tail;
            tail[0] = (uint32_t)(uintptr_t)timer;
            it[1] = (uint32_t)(uintptr_t)timer;
            goto inserted;
        }
        wanted -= span;
        timer[4] = (uint32_t)wanted;
        timer[5] = (uint32_t)(wanted >> 32);
        if (it == tail) break;
        it = (uint32_t *)(uintptr_t)it[0];
    }
    timer[0] = (uint32_t)(uintptr_t)head;
    timer[1] = (uint32_t)(uintptr_t)tail;
    tail[0] = (uint32_t)(uintptr_t)timer;
    head[1] = (uint32_t)(uintptr_t)timer;
inserted:
    if (head[0] != (uint32_t)(uintptr_t)head && timer == (uint32_t *)(uintptr_t)head[0])
        sys_clock_set_timeout(next_timeout(), 0);
    if (z_spin_unlock_valid(((unsigned long)&g_timeout_list_spinlock) /*=0x2000b498*/) != 0) {
        __set_BASEPRI(key);
        __ISB();
        return;
    }
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, ((unsigned long)&g_timeout_list_spinlock) /*=0x2000b498*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
}
