/* readable reconstruction; identity: FUN_0008144a @ 0x0008144a
 * public-name: bt_conn_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_notify_connected                 <= FUN_00055fb4 @ 0x00055fb4
 *   bt_l2cap_connected                       <= FUN_0005791c @ 0x0005791c
 *   bt_conn_connected                        <= FUN_0008144a @ 0x0008144a
 */
/* Reconstructed FUN_0008144a @ 0x8144a  (parity: 300/300 trials, PROVEN) */

extern void bt_l2cap_connected(void);
extern void bt_conn_notify_connected(unsigned int a);

void bt_conn_connected(unsigned int param_1)
{
    bt_l2cap_connected();
    bt_conn_notify_connected(param_1);
}
