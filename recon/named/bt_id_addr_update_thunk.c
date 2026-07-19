/* readable reconstruction; identity: FUN_0008104a @ 0x0008104a
 * public-name: bt_id_addr_update_thunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_id_addr_update_thunk                  <= FUN_0008104a @ 0x0008104a
 */
/* Reconstructed FUN_0008104a @ 0x8104a  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void bt_id_addr_update_thunk(unsigned r0, unsigned r1, unsigned r2)
{
  z_log_msg_runtime_create(r0, r1, r2, 0);
}
