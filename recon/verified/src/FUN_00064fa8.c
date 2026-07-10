/* Reconstructed FUN_00064fa8 @ 0x64fa8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(unsigned int,unsigned int);
extern void FUN_0007e2fa(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00064fa8(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    FUN_0007e2fa(0x00099cbdUL,0x000f6a46UL,0x000f6a09UL,0x5c,param_4);
    FUN_0007e2ec(0x000f6a09UL,0x5c);
  }
  *(unsigned int *)(param_2 + 0x80) = 0;
  return;
}

