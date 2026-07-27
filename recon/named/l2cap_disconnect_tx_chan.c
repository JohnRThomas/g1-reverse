/* readable reconstruction; identity: FUN_00081a60 @ 0x00081a60
 * public-name: l2cap_disconnect_tx_chan
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   conn_ctx_cleanup_if_pending              <= FUN_00081720 @ 0x00081720
 *   bt_l2cap_le_lookup_tx_cid                <= FUN_00081a4e @ 0x00081a4e
 *   l2cap_disconnect_tx_chan                 <= FUN_00081a60 @ 0x00081a60
 */
/* Reconstructed FUN_00081a60 @ 0x81a60  (parity: 300/300 trials, PROVEN) */

extern void conn_ctx_cleanup_if_pending(void);
extern int bt_l2cap_le_lookup_tx_cid(int, int);

void l2cap_disconnect_tx_chan(unsigned int param_1, void *param_2, int param_3)
{
    if (param_3 == 0) {
        int iVar1 = bt_l2cap_le_lookup_tx_cid(param_1, *(volatile unsigned short*)((char*)param_2 + 4));
        if (iVar1 != 0) {
            conn_ctx_cleanup_if_pending();
            return;
        }
    }
}
