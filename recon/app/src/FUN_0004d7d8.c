/* Reconstructed FUN_0004d7d8 @ 0x0004d7d8 (z_log_msg_post_finalize).
 * Exact configured Zephyr log_core.c static owner; extent 0xb0.
 */
#include <stdint.h>
extern uint32_t FUN_0007ee2c(volatile uint32_t *); /* atomic_inc */
extern void FUN_00072040(void *);                 /* z_spin_lock_valid */
extern void FUN_00072078(void *);                 /* z_spin_lock_set_owner */
extern void FUN_0007205c(void *);                 /* z_spin_unlock_valid */
extern void FUN_0004d594(void);                   /* log_process */
extern void FUN_00075174(void *, uint32_t, uint32_t, uint32_t); /* k_timer_start */
extern void FUN_0008673e(void *);                 /* k_timer_stop */
extern void FUN_00072880(void *);                 /* k_sem_give */

void FUN_0004d7d8(void)
{
    uint32_t previous = FUN_0007ee2c((volatile uint32_t *)0x2000a0d8U);
    if (*(volatile uint8_t *)0x2001d44cU != 0U) {
        /* The shipped k_spin_lock/unlock expansion surrounds log_process. */
        FUN_00072040((void *)0x2000a0c8U);
        FUN_00072078((void *)0x2000a0c8U);
        FUN_0004d594();
        FUN_0007205c((void *)0x2000a0c8U);
        return;
    }
    if (*(volatile uintptr_t *)0x2000a0d0U == 0U)
        return;
    if (previous == 0U) {
        FUN_00075174((void *)0x200056a8U, 0x8000U, 0U, 0U);
    } else if (previous == 9U) {
        FUN_0008673e((void *)0x200056a8U);
        FUN_00072880((void *)0x200039f8U);
    }
}
