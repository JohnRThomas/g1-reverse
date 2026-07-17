/* net-core FUN_0103b2b4 @ 0x0103b2b4
 * upstream identity: z_reschedule_unlocked
 * back-map: raw identity FUN_0103b2b4
 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void scheduler_reschedule_restore(uint32_t key); /* =FUN_0103b29c */

void FUN_0103b2b4(void)
{
    uint32_t key = __get_BASEPRI();

    __set_BASEPRI_MAX(0x40u);
    __ISB();
    scheduler_reschedule_restore(key);
}
