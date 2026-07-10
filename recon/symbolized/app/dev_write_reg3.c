#include "g1_app_symbols.h"
/* named: dev_write_reg3 */
/* Reconstructed dev_write_reg3 @ 0x83dc8  (parity: 300/300 trials, PROVEN) */

extern void dev_ctrl_write1(unsigned int, void *, unsigned int, unsigned int, unsigned int);

void dev_write_reg3(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char local_c;
  unsigned char local_b;
  unsigned char local_a;

  local_c = (unsigned char)param_2;
  local_b = (unsigned char)param_3;
  local_a = (unsigned char)param_4;
  dev_ctrl_write1(*(unsigned int *)((unsigned char*)param_1 + 4), &local_c, 3, param_4, (unsigned int)param_1);
  return;
}

