/* readable reconstruction; identity: FUN_00080f56 @ 0x00080f56
 * public-name: le_conn_param_neg_reply
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_or_create                <= FUN_000543d8 @ 0x000543d8
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   le_conn_param_neg_reply                  <= FUN_00080f56 @ 0x00080f56
 */
/* Reconstructed FUN_00080f56 @ 0x80f56  (parity: 300/300 trials, PROVEN) */

extern unsigned long long bt_hci_cmd_create(int a, int b);
extern short *net_buf_simple_add(int a, int b);
extern void bt_hci_cmd_send_or_create(int a, int b);
extern void FUN_000534a8(void);

void le_conn_param_neg_reply(short param_1, unsigned char param_2, int param_3, int param_4)
{
    unsigned long long uVar3 = bt_hci_cmd_create(0x2021, 3);
    int iVar1 = (int)uVar3;
    if (iVar1 == 0) {
        FUN_000534a8();
        return;
    }
    short *puVar2 = net_buf_simple_add(iVar1 + 0xc, 3);
    *(volatile short *)puVar2 = param_1;
    *(volatile unsigned char *)((char *)puVar2 + 2) = param_2;
    bt_hci_cmd_send_or_create(0x2021, iVar1);
}
