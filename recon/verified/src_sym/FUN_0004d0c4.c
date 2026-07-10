/* Reconstructed FUN_0004d0c4 @ 0x4d0c4  (parity: 300/300 trials, PROVEN) */

extern int rpmsg_create_ept(int, int, int, int, int, unsigned int, unsigned int, unsigned int);

int FUN_0004d0c4(int *param_1, int param_2, int param_3, unsigned int param_4)
{
  int uVar1;
  if (param_1 == 0 || param_3 == 0) {
    uVar1 = 0xffffffea;
  } else if (param_2 == 1) {
    uVar1 = rpmsg_create_ept(param_3, (int)param_1 + 0xe0, param_3 + 0x40, -1, -1,
                         *(unsigned int *)((char *)param_1 + 0x1ac), 0x0007ed27, param_4);
  } else {
    uVar1 = 0;
  }
  return uVar1;
}

