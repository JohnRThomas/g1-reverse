/* Reconstructed FUN_00082fd2 @ 0x82fd2  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005c80c(unsigned char,int);
extern void FUN_0005a8bc(unsigned char,int,unsigned int,unsigned int);
void FUN_00082fd2(int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 != 0) {
    FUN_0005c80c(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90);
    FUN_0005a8bc(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90, param_3, param_4);
    return;
  }
  return;
}

