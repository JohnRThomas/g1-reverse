/* readable reconstruction; identity: FUN_0007d658 @ 0x0007d658
 * public-name: projector_send_cmd_c0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_send_cmd_c0                    <= FUN_0007d658 @ 0x0007d658
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 */
/* Reconstructed FUN_0007d658 @ 0x7d658  (parity: 300/300 trials, PROVEN) */

extern void projector_send_command(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void projector_send_cmd_immediate(unsigned int a);
extern void delay_ms(unsigned int a);

void projector_send_cmd_c0(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  (void)param_3;
  unsigned char local[2];
  local[0] = (unsigned char)param_1;
  local[1] = (unsigned char)param_2;
  projector_send_command(0xc0, local, 2, param_4, param_1);
  projector_send_cmd_immediate(0x97);
  delay_ms(1);
}
