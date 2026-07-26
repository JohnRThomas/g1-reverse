/* readable reconstruction; identity: FUN_00073424 @ 0x00073424
 * public-name: k_work_reschedule_for_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   submit_to_queue_locked                   <= FUN_00072cd4 @ 0x00072cd4
 *   k_work_reschedule_for_queue              <= FUN_00073424 @ 0x00073424
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   unschedule_locked                        <= FUN_0008656a @ 0x0008656a
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
/* Reconstructed FUN_00073424 @ 0x73424
 * Readable identity: k_work_reschedule_for_queue.
 * Raw/address backmap: k_work_reschedule_for_queue <= FUN_00073424 @ 0x00073424.
 */

#include <stdint.h>
#include <cmsis_gcc.h>

extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);
extern int z_spin_lock_valid(uint32_t lock);
extern void z_spin_lock_set_owner(uint32_t lock);
extern int z_spin_unlock_valid(uint32_t lock);
extern void unschedule_locked(volatile uint32_t *delayable_work);
extern int submit_to_queue_locked(volatile uint32_t *work, uint32_t *queue,
                        uint32_t diagnostic0, uint32_t diagnostic1);
extern void z_add_timeout(uintptr_t timeout, uintptr_t handler,
                         uint32_t delay_low, uint32_t delay_high);

int k_work_reschedule_for_queue(uint32_t queue, volatile uint32_t *delayable_work,
                 uint32_t delay_low, uint32_t delay_high)
{
    const uint32_t work_lock = 0x2000b480UL;
    uint32_t saved_basepri;
    int result;

    if (delayable_work == 0) {
        printk(0x00099cbdUL, 0x000f82dfUL, 0x000f820fUL, 0x3deUL);
        assert_post_action(0x000f820fUL, 0x3deUL);
    }

    saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20U);
    __ISB();

    if (z_spin_lock_valid(work_lock) == 0) {
        printk(0x00099cbdUL, 0x000f0920UL, 0x000f08c7UL, 0x72UL);
        printk(0x000f0935UL, work_lock);
        assert_post_action(0x000f08c7UL, 0x72UL);
    }
    z_spin_lock_set_owner(work_lock);

    unschedule_locked(delayable_work);
    if ((delay_low | delay_high) == 0U) {
        result = submit_to_queue_locked(delayable_work, &queue, 0U,
                              delayable_work[3]);
    } else {
        uint32_t flags = delayable_work[3] | 8U;
        delayable_work[3] = flags;
        delayable_work[10] = queue;
        z_add_timeout((uintptr_t)delayable_work + 16U, 0x00072dadUL,
                     delay_low, delay_high);
        result = 1;
    }

    if (z_spin_unlock_valid(work_lock) == 0) {
        printk(0x00099cbdUL, 0x000f08f4UL, 0x000f08c7UL, 0xf0UL);
        printk(0x000f090bUL, work_lock);
        assert_post_action(0x000f08c7UL, 0xf0UL);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    return result;
}
