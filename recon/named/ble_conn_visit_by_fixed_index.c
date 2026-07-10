/* named: ble_conn_visit_by_fixed_index */
/* globals referenced:
//   0x20006138  g_ble_conn_pool              
*/
/* Reconstructed ble_conn_visit_by_fixed_index @ 0x56960  (parity: 300/300 trials, PROVEN) */

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

