/* readable reconstruction; identity: FUN_0007d74e @ 0x0007d74e
 * public-name: projector_reset_sequence
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_reset_sequence                 <= FUN_0007d74e @ 0x0007d74e
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 */
/* Reconstructed FUN_0007d74e @ 0x7d74e  (parity: 300/300 trials, PROVEN) */

extern void delay_ms(int);
extern void projector_send_cmd_immediate(unsigned int a0);

void projector_reset_sequence(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  delay_ms(1);
  projector_send_cmd_immediate(0x66);
  delay_ms(1);
  projector_send_cmd_immediate(0x99);
  delay_ms(10);
}
