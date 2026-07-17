#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059b94 @ 0x00059b94
 * public-name: find_sc_cfg_59b94
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59b94                        <= FUN_00059b94 @ 0x00059b94
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 * address symbols (name @ address):
 *   g_bt_gatt_sc_cfg                         @ 0x20006328
 *   g_bt_gatt_sc_cfg_addr                    @ 0x20006329
 */
/* Reconstructed FUN_00059b94 @ 0x59b94  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int find_sc_cfg_59b94(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = 0;
    unsigned int iVar3 = ((unsigned long)&g_bt_gatt_sc_cfg_addr) /*=0x20006329*/;
    while ((*(volatile unsigned char*)(iVar3 - 1) != param_1) ||
           (bt_addr_le_eq_0(param_2, iVar3, param_3, (unsigned int)*(volatile unsigned char*)(iVar3 - 1), param_4) == 0))
    {
        iVar2 = iVar2 + 0xc;
        iVar3 = iVar3 + 0xc;
        if (iVar2 == 0x24) {
            return 0;
        }
    }
    return ((unsigned long)&g_bt_gatt_sc_cfg) /*=0x20006328*/ + iVar2;
}
