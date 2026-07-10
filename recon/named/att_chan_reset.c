/* named: att_chan_reset */
/* Reconstructed att_chan_reset @ 0x83204  (parity: 300/300 trials, PROVEN) */

extern void FUN_00073518(unsigned int *, unsigned int, unsigned int);
extern void atomic_set_bit(unsigned int *, unsigned int, unsigned int, unsigned int);

void att_chan_reset(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile unsigned int *vp = (volatile unsigned int *)param_1;
  unsigned int uVar1 = vp[1];
  vp[1] = 0;
  FUN_00073518(param_1 + 0x82, 0, uVar1);
  *(volatile unsigned char *)(param_1 + 2) = 0;
  vp[0] = 0;
  atomic_set_bit(param_1, 1, 0, param_4);
}

