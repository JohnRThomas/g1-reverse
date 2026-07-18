#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007332c @ 0x0007332c
 * public-name: k_work_schedule_for_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_72dad                             @ 0x00072dad
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f82df                             @ 0x000f82df
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_0007332c @ 0x7332c
 * Readable identity: k_work_schedule_for_queue.
 * Raw/address backmap: k_work_schedule_for_queue <= FUN_0007332c @ 0x0007332c.
 */

#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);
extern int z_spin_lock_valid(uint32_t lock);
extern void z_spin_lock_set_owner(uint32_t lock);
extern int z_spin_unlock_valid(uint32_t lock);
extern int FUN_00072cd4(volatile uint32_t *work, uint32_t *queue,
                        uint32_t diagnostic0, uint32_t diagnostic1);
extern void FUN_00074bf4(uintptr_t timeout, uintptr_t handler,
                         uint32_t delay_low, uint32_t delay_high);

int k_work_schedule_for_queue(uint32_t queue, volatile uint32_t *delayable_work,
                 uint32_t delay_low, uint32_t delay_high)
{
    const uint32_t work_lock = ((unsigned long)&timer_spinlock) /*=0x2000b480*/;
    uint32_t saved_basepri;
    int result = 0;

    if (delayable_work == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f82df) /*=0xf82df*/, ((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x3baUL);
        assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x3baUL);
    }

    saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20U);
    __ISB();

    if (z_spin_lock_valid(work_lock) == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72UL);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, work_lock);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72UL);
    }
    z_spin_lock_set_owner(work_lock);

    uint32_t flags = delayable_work[3];
    if ((flags & 0x0eU) == 0U) {
        if ((delay_low | delay_high) == 0U) {
            result = FUN_00072cd4(delayable_work, &queue, 0U, flags);
        } else {
            delayable_work[3] = flags | 8U;
            delayable_work[10] = queue;
            FUN_00074bf4((uintptr_t)delayable_work + 16U, ((unsigned long)&rodata_72dad) /*=0x72dad*/,
                         delay_low, delay_high);
            result = 1;
        }
    }

    if (z_spin_unlock_valid(work_lock) == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0UL);
        printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, work_lock);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0UL);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    return result;
}
