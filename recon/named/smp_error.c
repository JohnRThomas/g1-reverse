/* readable reconstruction; identity: FUN_0005dc2c @ 0x0005dc2c
 * public-name: smp_error
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   smp_error                                <= FUN_0005dc2c @ 0x0005dc2c
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4f98                             @ 0x000f4f98
 */
/* Reconstructed FUN_0005dc2c @ 0x5dc2c  (parity: 300/300 trials, PROVEN) */

extern void bt_conn_disconnect_by_state(unsigned a, int b);
extern void smp_pairing_complete(int a, unsigned b);
extern void net_buf_unref(int a);
extern unsigned net_buf_simple_add(int a, int b);
extern int bt_conn_create_pdu(unsigned a, int b, int c, int d, int e);
extern unsigned atomic_test_bit(int a, int b);
extern void smp_log_message(unsigned a, unsigned b, void*c);
extern int smp_create_pdu(int a, int b);
unsigned smp_error(int param_1, unsigned param_2){
    int iVar4 = param_1 + 4;
    unsigned uVar1 = atomic_test_bit(iVar4, 2);
    if (uVar1 != 0) uVar1 = (*(volatile short*)(param_1 + 0xe8) == 0) ? 1 : 0;
    int called = 0;
    if (atomic_test_bit(iVar4, 3) != 0) called = 1;
    else if (atomic_test_bit(iVar4, 1) != 0) called = 1;
    else if (atomic_test_bit(iVar4, 0xf) != 0) called = 1;
    if (called) smp_pairing_complete(param_1, param_2);
    unsigned loc[4];
    if (uVar1 == 0){
        int node = smp_create_pdu(param_1, 5);
        if (node == 0) return 0xffffff97u;
        unsigned char *puVar3 = (unsigned char*)net_buf_simple_add(node + 0xc, 1);
        *(volatile unsigned char*)puVar3 = (unsigned char)param_2;
        int i = bt_conn_create_pdu(*(volatile unsigned*)(param_1 + 0xf0), 6, node, 0, 0);
        if (i != 0) net_buf_unref(node);
    } else {
        loc[1] = 0x000f4f98; loc[0] = 2;
        smp_log_message(0x00088180, 0x1080, loc);
        bt_conn_disconnect_by_state(*(volatile unsigned*)(param_1 + 0xf0), 5);
    }
    return 0;
}
