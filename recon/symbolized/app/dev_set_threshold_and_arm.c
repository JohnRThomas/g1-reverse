#include "g1_app_symbols.h"
/* named: dev_set_threshold_and_arm */
/* Reconstructed dev_set_threshold_and_arm @ 0x83e70  (parity: 300/300 trials, PROVEN) */

extern int dev_ctrl_write1(unsigned int, void*, int);
extern int dev_write_reg3(int, int, int, int);

int dev_set_threshold_and_arm(int param_1, unsigned int param_2)
{
  unsigned char buf[5];
  int iVar1;
  unsigned int r3;

  if (param_2 < 0x10000000) {
    buf[0] = 0x07;
    buf[1] = 0x08;
    buf[2] = (unsigned char)(param_2 >> 0x14);
    r3 = param_2 >> 4;
    buf[3] = (unsigned char)(r3 >> 8);
    buf[4] = (unsigned char)r3;
    iVar1 = dev_ctrl_write1(*(unsigned int*)(param_1+4), buf, 5);
    if (iVar1 == 0) {
      iVar1 = dev_write_reg3(param_1, 7, 3, 1);
    }
  } else {
    iVar1 = -0x16;
  }
  return iVar1;
}

