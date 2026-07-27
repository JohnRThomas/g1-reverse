#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d44c @ 0x0004d44c
 * public-name: z_log_notify_backend_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_notify_backend_enabled             <= FUN_0004d44c @ 0x0004d44c
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   g_200039f8                               @ 0x200039f8
 *   log_process_active                       @ 0x2001d44b
 */
/* Reconstructed FUN_0004d44c @ 0x4d44c
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: z_log_notify_backend_enabled.
 * Raw/address backmap: z_log_notify_backend_enabled <= FUN_0004d44c @ 0x0004d44c.
 */

#include <stdint.h>

extern void k_sem_give(int); /* k_sem_give */

void z_log_notify_backend_enabled(void)
{
    volatile uint8_t *const backend_attached =
        (volatile uint8_t *)((unsigned long)&log_process_active) /*=0x2001d44b*/;

    if (*backend_attached == 0U) {
        k_sem_give((void *)((unsigned long)&g_200039f8) /*=0x200039f8*/);
    }
    *backend_attached = 1U;
}
