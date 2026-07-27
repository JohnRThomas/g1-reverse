/* readable reconstruction; identity: FUN_0007332c @ 0x0007332c
 * public-name: k_work_schedule_for_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   submit_to_queue_locked                   <= FUN_00072cd4 @ 0x00072cd4
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_72dad                             @ 0x00072dad
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f82df                             @ 0x000f82df
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_0007332c @ 0x7332c
 * Readable identity: k_work_schedule_for_queue.
 * Raw/address backmap: k_work_schedule_for_queue <= FUN_0007332c @ 0x0007332c.
 */

#include <stdint.h>
#include <cmsis_gcc.h>
#include "../headers/g1_log.h"

extern int assert_post_action(int, int);
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_spin_unlock_valid(uint32_t lock);
extern int submit_to_queue_locked(volatile uint32_t *work, uint32_t *queue,
                        uint32_t diagnostic0, uint32_t diagnostic1);
extern void z_add_timeout(uintptr_t timeout, uintptr_t handler,
                         uint32_t delay_low, uint32_t delay_high);

int k_work_schedule_for_queue(uint32_t queue, volatile uint32_t *delayable_work,
                 uint32_t delay_low, uint32_t delay_high)
{
    const uint32_t work_lock = 0x2000b480UL;
    uint32_t saved_basepri;
    int result = 0;

    if (delayable_work == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f82dfUL, 0x000f820fUL, 0x3baUL);
        assert_post_action(0x000f820fUL, 0x3baUL);
    }

    saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20U);
    __ISB();

    if (z_spin_lock_valid(work_lock) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_lock_valid(l)"), 0x000f08c7UL, 0x72UL);
        printk(((unsigned long)"\tInvalid spinlock %p\n"), work_lock);
        assert_post_action(0x000f08c7UL, 0x72UL);
    }
    z_spin_lock_set_owner(work_lock);

    uint32_t flags = delayable_work[3];
    if ((flags & 0x0eU) == 0U) {
        if ((delay_low | delay_high) == 0U) {
            result = submit_to_queue_locked(delayable_work, &queue, 0U, flags);
        } else {
            delayable_work[3] = flags | 8U;
            delayable_work[10] = queue;
            z_add_timeout((uintptr_t)delayable_work + 16U, 0x00072dadUL,
                         delay_low, delay_high);
            result = 1;
        }
    }

    if (z_spin_unlock_valid(work_lock) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_unlock_valid(l)"), 0x000f08c7UL, 0xf0UL);
        printk(((unsigned long)"\tNot my spinlock %p\n"), work_lock);
        assert_post_action(0x000f08c7UL, 0xf0UL);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    return result;
}
