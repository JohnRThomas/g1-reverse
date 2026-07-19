/* readable reconstruction; identity: FUN_00080780 @ 0x00080780
 * public-name: arm_fault_forward_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   arm_fault_forward_handler                <= FUN_00080780 @ 0x00080780
 */
/* Reconstructed FUN_00080780 @ 0x80780  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void arm_fault_forward_handler(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
