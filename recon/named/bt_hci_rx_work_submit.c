/* readable reconstruction; identity: FUN_00053530 @ 0x00053530
 * public-name: bt_hci_rx_work_submit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_rx_work_submit                    <= FUN_00053530 @ 0x00053530
 *   net_buf_slist_put                        <= FUN_0005f074 @ 0x0005f074
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   k_work_submit_to_queue                   <= FUN_000865fc @ 0x000865fc
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2ddb                             @ 0x000f2ddb
 *   g_bt_hci_recv_fifo                       @ 0x20002144
 *   g_bt_hci_rx_work                         @ 0x20002980
 *   bt_workqueue                             @ 0x20005f08
 */
/* Reconstructed FUN_00053530 @ 0x53530  (parity: 300/300 trials, PROVEN) */

extern void net_buf_slist_put(unsigned int a, unsigned int b);
extern void bt_log_forward_3arg(unsigned int a, unsigned int b, void *c);
extern int k_work_submit_to_queue(unsigned int a, unsigned int b);

void bt_hci_rx_work_submit(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int local_20;
    unsigned int local_1c;
    int iStack_18;

    net_buf_slist_put(0x20002144UL, param_1);
    iStack_18 = k_work_submit_to_queue(0x20005f08UL, 0x20002980UL);
    if (iStack_18 < 0) {
        local_1c = 0x000f2ddbUL;
        local_20 = 3;
        bt_log_forward_3arg(0x00088138UL, 0x1840, &local_20);
    }
}
