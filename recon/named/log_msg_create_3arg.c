/* readable reconstruction; identity: FUN_00082a42 @ 0x00082a42
 * public-name: log_msg_create_3arg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 */
/* Reconstructed FUN_00082a42 @ 0x82a42  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void log_msg_create_3arg(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
