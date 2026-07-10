/* Reconstructed FUN_00076b48 @ 0x76b48  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(unsigned int *, unsigned int, unsigned int);

void FUN_00076b48(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  volatile unsigned int *vp = (volatile unsigned int *)param_1;
  vp[2] = 0;
  *(volatile unsigned short *)(param_1 + 3) = (unsigned short)param_2;
  vp[0x19] = 0;
  *(volatile unsigned short *)((char *)param_1 + 0xe) = (unsigned short)param_3;
  vp[6] = 0;
  vp[0] = 0;
  vp[1] = 0;
  vp[4] = 0;
  vp[5] = 0;
  FUN_00086c78((unsigned int *)((char *)param_1 + 0x5c), 0, 8);
  vp[8] = (unsigned int)param_1;
  vp[9] = 0x86f35;
  vp[10] = 0x86f5b;
  vp[0xb] = 0x86f93;
  vp[0xc] = 0x86fb7;
}

