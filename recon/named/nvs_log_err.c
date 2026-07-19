/* readable reconstruction; identity: FUN_0007e658 @ 0x0007e658
 * public-name: nvs_log_err
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   nvs_log_err                              <= FUN_0007e658 @ 0x0007e658
 */
/* Reconstructed FUN_0007e658 @ 0x7e658  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void nvs_log_err(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
