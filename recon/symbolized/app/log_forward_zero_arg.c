#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000837a2 @ 0x000837a2
 * public-name: log_forward_zero_arg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   log_forward_zero_arg                     <= FUN_000837a2 @ 0x000837a2
 */
/* Reconstructed FUN_000837a2 @ 0x837a2  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void log_forward_zero_arg(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
