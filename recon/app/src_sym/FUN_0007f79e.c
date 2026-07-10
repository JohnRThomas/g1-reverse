/* Reconstructed bt_ancs_register_app_attr @ 0x7f79e  (parity: 300/300 trials, PROVEN) */

int bt_ancs_register_app_attr(int param_1, int param_2, int param_3, int param_4)
{
  int uVar1;
  if ((param_1 == 0) || (param_3 == 0) || ((unsigned int)(param_4 - 1) > 0xff) || (param_2 != 0)) {
    uVar1 = (int)0xffffffea;
  } else {
    *(volatile short *)(param_1 + 0x8f0) = (short)param_4;
    *(volatile unsigned char *)(param_1 + 0x8e8) = 1;
    *(volatile int *)(param_1 + 0x8f4) = param_3;
    uVar1 = param_2;
  }
  return uVar1;
}

