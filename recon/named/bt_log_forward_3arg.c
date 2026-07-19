/* readable reconstruction; identity: FUN_00080ea2 @ 0x00080ea2
 * public-name: bt_log_forward_3arg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 */
/* Reconstructed FUN_00080ea2 @ 0x80ea2  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void bt_log_forward_3arg(unsigned r0, unsigned r1, unsigned r2)
{
  z_log_msg_runtime_create(r0, r1, r2, 0);
}
