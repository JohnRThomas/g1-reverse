#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e526 @ 0x0007e526
 * public-name: thread_entry_no_return
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hw_reset_and_halt                        <= FUN_0004c4d0 @ 0x0004c4d0
 *   thread_entry_no_return                   <= FUN_0007e526 @ 0x0007e526
 */
/* Full reconstruction FUN_0007e526 @ 0x7e526 (exact extent 24 bytes).
 * CFG_VERIFY_PREFIX_FIRST: the post-call BX LR branches to itself because the
 * BL replaced LR; this is an intentional one-call terminal loop. */

extern void hw_reset_and_halt(void);

/* The shipped wrapper raises BASEPRI_MAX to 0x20 and executes an ISB before
 * entering the scheduler boundary.  BASEPRI is architectural state rather
 * than C-visible memory; FUN_0004c4d0 is the observable platform boundary. */
void thread_entry_no_return(void)
{
    hw_reset_and_halt();
    for (;;) {
    }
}
