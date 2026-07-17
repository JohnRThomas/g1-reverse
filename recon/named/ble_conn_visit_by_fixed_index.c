/* readable reconstruction; identity: FUN_00056960 @ 0x00056960
 * public-name: ble_conn_visit_by_fixed_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_ref                             <= FUN_00056654 @ 0x00056654
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_visit_by_fixed_index            <= FUN_00056960 @ 0x00056960
 * address symbols (name @ address):
 *   g_ble_conn_pool                          @ 0x20006138
 */
/* Reconstructed FUN_00056960 @ 0x56960  (parity: 300/300 trials, PROVEN) */

extern unsigned int ble_conn_ref(unsigned int a);
extern void ble_conn_unref(unsigned int a);

void ble_conn_visit_by_fixed_index(unsigned char param_1, void (*param_2)(unsigned int, unsigned int), unsigned int param_3)
{
    unsigned int iVar1;
    iVar1 = ble_conn_ref(0x20006138UL);
    if (iVar1 != 0) {
        if ((param_1 & *(volatile unsigned char*)(iVar1 + 2)) != 0) {
            param_2(iVar1, param_3);
        }
        ble_conn_unref(iVar1);
    }
}
