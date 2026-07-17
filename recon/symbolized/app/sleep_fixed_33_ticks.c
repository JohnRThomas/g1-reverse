#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c87a @ 0x0007c87a
 * public-name: sleep_fixed_33_ticks
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 */
/* Reconstructed FUN_0007c87a @ 0x7c87a  (parity: 300/300 trials, PROVEN) */

extern void FUN_00074844(unsigned int, unsigned int);
void sleep_fixed_33_ticks(void)
{
    FUN_00074844(0x21, 0);
}
