/* readable reconstruction; identity: FUN_0007d642 @ 0x0007d642
 * public-name: projector_send_cmd1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_send_cmd1                      <= FUN_0007d642 @ 0x0007d642
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 */
/* Reconstructed FUN_0007d642 @ 0x7d642  (parity: 300/300 trials, PROVEN) */

extern void projector_send_command(unsigned int, unsigned char*, unsigned int, unsigned int, unsigned int, unsigned int);

void projector_send_cmd1(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int stackword = ((param_2 & 0xFFu) << 24) | (param_2 & 0x00FFFFFFu);
    unsigned char *p = ((unsigned char*)&stackword) + 3;
    projector_send_command(param_1, p, 1, param_4, param_1, stackword);
}
