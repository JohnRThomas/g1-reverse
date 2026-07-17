/* readable reconstruction; identity: FUN_0007d67e @ 0x0007d67e
 * public-name: projector_send_cmd_0x46
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_send_cmd_0x46                  <= FUN_0007d67e @ 0x0007d67e
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 */
/* Reconstructed FUN_0007d67e @ 0x7d67e  (parity: 300/300 trials, PROVEN) */

extern int projector_send_command(int a, void*b, int c, int d, int e, int f);
void projector_send_cmd_0x46(int param_1, int param_2, int param_3, int param_4) {
    unsigned char local = (unsigned char)param_1;
    projector_send_command(0x46, &local, 1, param_4, param_1, param_2);
}
