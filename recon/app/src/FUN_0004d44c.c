/* Reconstructed FUN_0004d44c @ 0x4d44c
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: z_log_notify_backend_enabled.
 * Raw/address backmap: z_log_notify_backend_enabled <= FUN_0004d44c @ 0x0004d44c.
 */

#include <stdint.h>

extern void FUN_00072880(void *sem); /* k_sem_give */

void FUN_0004d44c(void)
{
    volatile uint8_t *const backend_attached =
        (volatile uint8_t *)0x2001d44bUL;

    if (*backend_attached == 0U) {
        FUN_00072880((void *)0x200039f8UL);
    }
    *backend_attached = 1U;
}
