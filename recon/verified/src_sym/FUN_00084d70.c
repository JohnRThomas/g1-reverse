/* Reconstructed FUN_00084d70 @ 0x84d70  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00084d70(int param_1,int param_2)
{
  unsigned int uVar1;
  if (param_1 == 4) { return 1; }
  if (param_1 == 5) {
    uVar1 = (unsigned int)(param_2 - 1);
    if (uVar1 != 0) { uVar1 = 1; }
    return uVar1;
  }
  return (unsigned int)(param_1 == param_2);
}

