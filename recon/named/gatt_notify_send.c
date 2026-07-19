/* readable reconstruction; identity: FUN_0008199a @ 0x0008199a
 * public-name: gatt_notify_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_pairing_event_cnt_inc                <= FUN_00057394 @ 0x00057394
 *   att_alloc_pdu_with_hdr                   <= FUN_000573f4 @ 0x000573f4
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   att_send_and_schedule_tx                 <= FUN_00081962 @ 0x00081962
 *   gatt_notify_send                         <= FUN_0008199a @ 0x0008199a
 */
/* Reconstructed FUN_0008199a @ 0x8199a  (parity: 300/300 trials, PROVEN) */

extern int smp_pairing_event_cnt_inc(void);
extern int att_alloc_pdu_with_hdr(int a, int b, int c);
extern short *net_buf_simple_add(int a, int b);
extern void att_send_and_schedule_tx(int a, int b, int c, int d, int e);

unsigned int gatt_notify_send(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    short *puVar3;

    uVar1 = smp_pairing_event_cnt_inc();
    *(char *)(param_1 + 0xb8) = (char)uVar1;
    iVar2 = att_alloc_pdu_with_hdr(0x14, uVar1, 10);
    if (iVar2 == 0) {
        uVar1 = 0xfffffff4;
    } else {
        puVar3 = net_buf_simple_add(iVar2 + 0xc, 10);
        *puVar3 = *(short *)(param_1 + 0xb6);
        puVar3[1] = *(short *)(param_1 + 0x14);
        puVar3[2] = *(short *)(param_1 + 0x16);
        puVar3[3] = *(short *)(param_1 + 0x18);
        puVar3[4] = (short)*(int *)(param_1 + 0x1c);
        att_send_and_schedule_tx(param_1, iVar2, 0x140000, 0, param_4);
        uVar1 = 0;
    }
    return uVar1;
}
