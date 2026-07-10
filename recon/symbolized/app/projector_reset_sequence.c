#include "g1_app_symbols.h"
/* named: projector_reset_sequence */
/* Reconstructed projector_reset_sequence @ 0x7d74e  (parity: 300/300 trials, PROVEN) */

extern void delay_ms(unsigned int a0);
extern void projector_send_cmd_immediate(unsigned int a0);

void projector_reset_sequence(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  delay_ms(1);
  projector_send_cmd_immediate(0x66);
  delay_ms(1);
  projector_send_cmd_immediate(0x99);
  delay_ms(10);
}

