/* Reconstructed FUN_0007332c @ 0x7332c
 * Readable identity: k_work_schedule_for_queue.
 * Raw/address backmap: k_work_schedule_for_queue <= FUN_0007332c @ 0x0007332c.
 */

#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern int FUN_00072040(uint32_t lock);
extern void FUN_00072078(uint32_t lock);
extern int FUN_0007205c(uint32_t lock);
extern int FUN_00072cd4(volatile uint32_t *work, uint32_t *queue,
                        uint32_t diagnostic0, uint32_t diagnostic1);
extern void FUN_00074bf4(uintptr_t timeout, uintptr_t handler,
                         uint32_t delay_low, uint32_t delay_high);

int FUN_0007332c(uint32_t queue, volatile uint32_t *delayable_work,
                 uint32_t delay_low, uint32_t delay_high)
{
    const uint32_t work_lock = 0x2000b480UL;
    uint32_t saved_basepri;
    int result = 0;

    if (delayable_work == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f82dfUL, 0x000f820fUL, 0x3baUL);
        FUN_0007e2ec(0x000f820fUL, 0x3baUL);
    }

    saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20U);
    __ISB();

    if (FUN_00072040(work_lock) == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f0920UL, 0x000f08c7UL, 0x72UL);
        FUN_0007e2fa(0x000f0935UL, work_lock);
        FUN_0007e2ec(0x000f08c7UL, 0x72UL);
    }
    FUN_00072078(work_lock);

    uint32_t flags = delayable_work[3];
    if ((flags & 0x0eU) == 0U) {
        if ((delay_low | delay_high) == 0U) {
            result = FUN_00072cd4(delayable_work, &queue, 0U, flags);
        } else {
            delayable_work[3] = flags | 8U;
            delayable_work[10] = queue;
            FUN_00074bf4((uintptr_t)delayable_work + 16U, 0x00072dadUL,
                         delay_low, delay_high);
            result = 1;
        }
    }

    if (FUN_0007205c(work_lock) == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f08f4UL, 0x000f08c7UL, 0xf0UL);
        FUN_0007e2fa(0x000f090bUL, work_lock);
        FUN_0007e2ec(0x000f08c7UL, 0xf0UL);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    return result;
}
