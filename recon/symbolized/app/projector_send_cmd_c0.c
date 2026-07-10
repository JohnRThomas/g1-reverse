#include "g1_app_symbols.h"
/* named: projector_send_cmd_c0 */
/* Reconstructed projector_send_cmd_c0 @ 0x7d658  (parity: 300/300 trials, PROVEN) */

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

