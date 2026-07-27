/* Reconstructed FUN_00032ef0 @ 0x32ef0  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

void FUN_00032ef0(unsigned int param_1)
{
  if (*(volatile unsigned int*)0x20007554UL == 0) {
    FUN_0007dda4(0x000a756aUL, param_1);
  }
  else {
    FUN_00019c70(0x000a756aUL, param_1);
  }
  *(volatile unsigned char*)0x20019ef3UL = (unsigned char)param_1;
  return;
}
