/* readable reconstruction; identity: FUN_00059c70 @ 0x00059c70
 * public-name: gatt_find_conn_in_known_table
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   bt_conn_is_peer_addr_le                  <= FUN_000814e6 @ 0x000814e6
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_known_device_table                     @ 0x2000af18
 */
/* Reconstructed FUN_00059c70 @ 0x59c70  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_is_peer_addr_le(int a, unsigned char b);
extern int bt_addr_le_eq_0(void *a, unsigned int b);

unsigned char * gatt_find_conn_in_known_table(int param_1)
{
    unsigned int uVar1;
    int iVar2;
    unsigned char *puVar3;
    int iVar4;

    uVar1 = 0x000f2b3aUL;
    iVar4 = 0;
    puVar3 = (unsigned char *)0x2000af18UL;
    while (1) {
        if (param_1 == 0) {
            iVar2 = bt_addr_le_eq_0(puVar3 + 1, uVar1);
        } else {
            iVar2 = bt_conn_is_peer_addr_le(param_1, *puVar3);
        }
        if (iVar2 != 0) break;
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0x10;
        if (iVar4 == 3) {
            return (unsigned char *)0;
        }
    }
    return puVar3;
}
