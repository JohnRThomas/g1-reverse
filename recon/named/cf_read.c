/* readable reconstruction; identity: FUN_000829c0 @ 0x000829c0
 * public-name: cf_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 *   cf_read                                  <= FUN_000829c0 @ 0x000829c0
 */
/* Reconstructed FUN_000829c0 @ 0x829c0  (parity: 300/300 trials, PROVEN) */

extern int find_cf_cfg(void);
extern void bt_gatt_attr_read(unsigned int a, unsigned int b, unsigned short c, void *d, int e);

void cf_read(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned short param_5)
{
    unsigned char local_14[8];
    local_14[0] = 0;
    int iVar1 = find_cf_cfg();
    if (iVar1 != 0) {
        local_14[0] = *(volatile unsigned char*)((char*)iVar1 + 8);
    }
    bt_gatt_attr_read(param_3, param_4, param_5, local_14, 1);
}
