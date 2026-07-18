/* readable reconstruction; identity: FUN_0102de10 @ 0x0102de10
 * public-name: z_log_dropped
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_log_dropped                            <= FUN_0102de10 @ 0x0102de10
 * address symbols (name @ address):
 *   g_net_tick_correction_pending            @ 0x21004664
 *   g_net_tick_pending_cnt                   @ 0x21004668
 */
/* Reconstructed z_log_dropped @ 0x0102de10.
 * Raw/address back-map: FUN_0102de10 / 0x0102de10.
 */
#include <stdint.h>
extern void FUN_0103a294(volatile uint32_t *value); /* atomic_inc */

void z_log_dropped(uint32_t buffered)
{
    volatile uint32_t *const buffered_count =
        (volatile uint32_t *)0x21004668u;
    FUN_0103a294((volatile uint32_t *)0x21004664u);
    if (buffered != 0u) {
        (void)__atomic_fetch_sub((uint32_t *)buffered_count, 1u,
                                 __ATOMIC_SEQ_CST);
    }
}
