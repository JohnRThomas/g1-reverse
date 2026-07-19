#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081746 @ 0x00081746
 * public-name: log_msg_3arg_thunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   log_msg_3arg_thunk                       <= FUN_00081746 @ 0x00081746
 */
/* Reconstructed FUN_00081746 @ 0x81746  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void log_msg_3arg_thunk(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
