/* readable reconstruction; identity: FUN_000543d8 @ 0x000543d8
 * public-name: bt_hci_cmd_send_or_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_driver_send                       <= FUN_000543c8 @ 0x000543c8
 *   bt_hci_cmd_send_or_create                <= FUN_000543d8 @ 0x000543d8
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f3103                             @ 0x000f3103
 *   hci_cmd_pool                             @ 0x2000214c
 */
/* Reconstructed FUN_000543d8 @ 0x543d8  (parity: 300/300 trials, PROVEN) */
extern int bt_hci_cmd_create(unsigned long, unsigned long);
extern int bt_hci_driver_send(int);
extern void net_buf_put(unsigned,int);
extern void net_buf_unref(int);
extern void bt_log_forward_3arg(unsigned,int,void*);
int bt_hci_cmd_send_or_create(int param_1, int param_2, unsigned param_3, unsigned param_4){
    int r4 = param_2;
    if (param_2 == 0){
        r4 = bt_hci_cmd_create(param_1, param_2);
        if (r4 == 0) return -0x69;
    }
    if (param_1 == 0xc35){
        int r5 = bt_hci_driver_send(r4);
        if (r5 != 0){
            volatile unsigned local[8];
            local[4]=3; local[5]=0xf3103; local[6]=(unsigned)r5;
            bt_log_forward_3arg(0x88138, 0x1840, (void*)&local[4]);
            net_buf_unref(r4);
        }
        return r5;
    } else {
        net_buf_put(0x2000214c, r4);
        return 0;
    }
}
