/* readable reconstruction; identity: FUN_0102ddf4 @ 0x0102ddf4
 * public-name: z_log_notify_backend_enabled
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_log_notify_backend_enabled             <= FUN_0102ddf4 @ 0x0102ddf4
 * address symbols (name @ address):
 *   g_net_tick_handler_enable_flag           @ 0x21004fac
 */
/* Reconstructed z_log_msg_init @ 0x0102ddf4.
 * Raw/address back-map: FUN_0102ddf4 / 0x0102ddf4.
 */
#include <stdint.h>

extern void FUN_01036824(void *buffer); /* mpsc_pbuf_init */

void z_log_notify_backend_enabled(void)
{
    volatile uint8_t *const initialized = (volatile uint8_t *)0x21004facu;
    if (*initialized == 0u) {
        FUN_01036824((void *)0x21000944u);
    }
    *initialized = 1u;
}
