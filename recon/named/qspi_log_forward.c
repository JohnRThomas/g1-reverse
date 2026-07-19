/* readable reconstruction; identity: FUN_000838d6 @ 0x000838d6
 * public-name: qspi_log_forward
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   qspi_log_forward                         <= FUN_000838d6 @ 0x000838d6
 */
/* Reconstructed FUN_000838d6 @ 0x838d6  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
void qspi_log_forward(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    z_log_msg_runtime_create(a, b, c, 0);
}
