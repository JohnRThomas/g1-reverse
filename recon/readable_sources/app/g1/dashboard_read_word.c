#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d1d0 @ 0x0007d1d0
 * public-name: dashboard_read_word
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dashboard_read_word                      <= FUN_0007d1d0 @ 0x0007d1d0
 */
/* Reconstructed FUN_0007d1d0 @ 0x7d1d0  (parity: 300/300 trials, PROVEN) */

unsigned int dashboard_read_word(volatile unsigned int *p)
{
    return *p;
}
