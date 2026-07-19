#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083074 @ 0x00083074
 * public-name: smp_log_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 */
/* Reconstructed FUN_00083074 @ 0x83074  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void smp_log_message(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
