#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081a4e @ 0x00081a4e
 * public-name: FUN_00081a4e
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00081a4e @ 0x81a4e  (parity: 300/300 trials, PROVEN) */

void FUN_00081a4e(int param_1, unsigned int param_2)
{
    int *piVar1;
    for (piVar1 = *(int **)(param_1 + 0x54);
         piVar1 != (int *)0 && *(unsigned short *)((char*)piVar1 + 0x1c) != (unsigned short)param_2;
         piVar1 = (int *)*piVar1) {
    }
}
