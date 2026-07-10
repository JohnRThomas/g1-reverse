#include "g1_app_symbols.h"
/* named: dev_update_bits5 */
/* Reconstructed dev_update_bits5 @ 0x83bca  (parity: 300/300 trials, PROVEN) */

extern int dev_read_bits5(unsigned int a, unsigned int *b, unsigned int c, unsigned int d, unsigned int e);
extern void dev_write_bits5_diff(unsigned int a, unsigned int b, unsigned int c);

void dev_update_bits5(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_14 = param_2;
  int iVar1 = dev_read_bits5(param_1, &local_14, param_3, param_4, param_1);
  if (iVar1 >= 0) {
    dev_write_bits5_diff(param_1, param_2, ~local_14);
  }
}

