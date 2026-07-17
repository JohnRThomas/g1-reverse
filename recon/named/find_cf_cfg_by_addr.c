/* readable reconstruction; identity: FUN_00059b5c @ 0x00059b5c
 * public-name: find_cf_cfg_by_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 * address symbols (name @ address):
 *   g_bt_gatt_cf_cfg                         @ 0x2000aed4
 *   g_bt_gatt_cf_cfg                         @ 0x2000aed5
 */
/* Reconstructed FUN_00059b5c @ 0x59b5c  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int find_cf_cfg_by_addr(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = 0;
    unsigned int iVar3 = 0x2000aed5UL;
    while ((*(volatile unsigned char*)(iVar3 - 1) != param_1) ||
           (bt_addr_le_eq_0(param_2, iVar3, param_3, (unsigned int)*(volatile unsigned char*)(iVar3 - 1), param_4) == 0))
    {
        iVar2 = iVar2 + 0x10;
        iVar3 = iVar3 + 0x10;
        if (iVar2 == 0x30) {
            return 0;
        }
    }
    return 0x2000aed4UL + iVar2;
}
