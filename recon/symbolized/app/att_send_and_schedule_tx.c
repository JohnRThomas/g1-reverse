#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081962 @ 0x00081962
 * public-name: att_send_and_schedule_tx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   att_send_and_schedule_tx                 <= FUN_00081962 @ 0x00081962
 */
/* Reconstructed FUN_00081962 @ 0x81962  (parity: 300/300 trials, PROVEN) */

extern unsigned long long bt_conn_create_pdu(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);
extern void net_buf_unref(int);
extern void k_work_reschedule(unsigned int, unsigned int, unsigned int, unsigned int);

void att_send_and_schedule_tx(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned long long uVar1;
    uVar1 = bt_conn_create_pdu(*param_1, 5, param_2, 0, 0, param_2, param_3);
    if ((int)uVar1 != 0) {
        net_buf_unref(param_2);
        return;
    }
    k_work_reschedule(param_1 + 0x30, (unsigned int)(uVar1 >> 32), param_3, param_4);
}
