/* readable reconstruction; identity: FUN_0007e9ea @ 0x0007e9ea
 * public-name: ipc_log_forward
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   ipc_log_forward                          <= FUN_0007e9ea @ 0x0007e9ea
 */
/* Reconstructed FUN_0007e9ea @ 0x7e9ea  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void ipc_log_forward(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
