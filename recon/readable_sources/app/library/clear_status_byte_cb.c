#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c004 @ 0x0007c004
 * public-name: clear_status_byte_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_status_byte_cb                     <= FUN_0007c004 @ 0x0007c004
 */
/* Reconstructed FUN_0007c004 @ 0x7c004  (parity: 300/300 trials, PROVEN) */

void clear_status_byte_cb(int a0, int a1, int a2, volatile unsigned char *a3)
{
    *a3 = 0;
}
