/* Reconstructed FUN_000658e8 @ 0x658e8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00065434(unsigned int a);
extern int FUN_00065460(void);
extern void FUN_0007e2ec(int a,int b);
extern void FUN_0007e2fa(unsigned long, ...);

unsigned int FUN_000658e8(unsigned int param_1, int param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned long long uVar3;

  if (param_2 == 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f6b7d, 0x000f6b00, 0x265);
    FUN_0007e2ec(0x000f6b00, 0x265);
  }
  iVar1 = FUN_00065460();
  uVar2 = 0x0bad0004;
  if (iVar1 != 0) {
    uVar3 = FUN_00065434(param_1);
    uVar2 = 0x0bad0000;
    unsigned int lo = (unsigned int)uVar3;
    unsigned int hi = (unsigned int)(uVar3 >> 32);
    *(volatile unsigned char*)(unsigned long)hi = (unsigned char)((*(volatile unsigned short*)(0x20002bc0UL + (unsigned long)(lo+8)*2)) >> 0xd);
  }
  return uVar2;
}

