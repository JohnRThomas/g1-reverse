#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081aca @ 0x00081aca
 * public-name: bt_l2cap_le_lookup_tx_cid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_le_lookup_tx_cid                <= FUN_00081aca @ 0x00081aca
 */
/* Reconstructed FUN_00081aca @ 0x81aca  (parity: 300/300 trials, PROVEN) */

void bt_l2cap_le_lookup_tx_cid(int param_1, unsigned int param_2)
{
    int *piVar1;
    for (piVar1 = *(int **)(param_1 + 0x54);
         piVar1 != (int *)0 && *(unsigned short *)((char*)piVar1 + 0xc) != (unsigned short)param_2;
         piVar1 = (int *)*piVar1) {
    }
}
