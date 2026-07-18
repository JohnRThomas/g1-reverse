/* Reconstructed Zephyr z_reschedule_unlocked @ 0x0008664c.
 * Raw/address back-map: FUN_0008664c / 0x0008664c.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

#define z_reschedule_irqlock FUN_00086634
extern void z_reschedule_irqlock(uint32_t key);

void z_reschedule_unlocked(void)
{
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();
    z_reschedule_irqlock(key);
}
