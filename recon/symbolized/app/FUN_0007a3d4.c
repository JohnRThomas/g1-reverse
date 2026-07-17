#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007a3d4 @ 0x0007a3d4
 * public-name: FUN_0007a3d4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007a3d4 @ 0x7a3d4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int, unsigned int, unsigned int);
void FUN_0007a3d4(unsigned int param_1, unsigned int param_2)
{
    memset_bytes(param_1, 0, param_2);
}
