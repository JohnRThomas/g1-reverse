#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081320 @ 0x00081320
 * public-name: FUN_00081320
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 */
/* Reconstructed FUN_00081320 @ 0x81320  (parity: 300/300 trials, PROVEN) */

extern void k_work_cancel_delayable(int);
void FUN_00081320(int param_1)
{
    k_work_cancel_delayable(param_1 + 0x18);
}
