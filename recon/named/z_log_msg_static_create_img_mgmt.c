/* readable reconstruction; identity: FUN_0008096a @ 0x0008096a
 * public-name: z_log_msg_static_create_img_mgmt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   z_log_msg_static_create_img_mgmt         <= FUN_0008096a @ 0x0008096a
 */
/* Reconstructed FUN_0008096a @ 0x8096a  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void z_log_msg_static_create_img_mgmt(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
