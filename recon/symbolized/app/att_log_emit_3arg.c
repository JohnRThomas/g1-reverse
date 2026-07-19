#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081ddc @ 0x00081ddc
 * public-name: att_log_emit_3arg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 */
/* Reconstructed FUN_00081ddc @ 0x81ddc  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void att_log_emit_3arg(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
