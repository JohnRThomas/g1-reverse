/* named: bignum_compare_estimate */
/* Reconstructed bignum_compare_estimate @ 0x875e4  (parity: 300/300 trials, PROVEN) */
extern unsigned long long d2b(int, int*);
extern unsigned long long __divdf3(int, int, int, int);

unsigned long long bignum_compare_estimate(int param_1, int param_2)
{
  unsigned long long uVar4, uVar5;
  int iVar2, iVar3, iVar1;

  uVar4 = d2b(param_1, (int*)0x2007EFF4UL);
  iVar2 = (int)(uVar4 >> 32);
  uVar5 = d2b(param_2, (int*)0x2007EFF8UL);
  iVar3 = (int)(uVar5 >> 32);
  iVar1 = (*(volatile int*)0x2007EFF4UL - *(volatile int*)0x2007EFF8UL) +
          (*(volatile int*)(param_1 + 0x10) - *(volatile int*)(param_2 + 0x10)) * 0x20;
  if (iVar1 < 1) {
    iVar3 = iVar3 + iVar1 * -0x100000;
  } else {
    iVar2 = iVar2 + iVar1 * 0x100000;
  }
  uVar4 = __divdf3((int)uVar4, iVar2, (int)uVar5, iVar3);
  __asm__ volatile("vmov d0, %0, %1" :: "r"((unsigned)uVar4), "r"((unsigned)(uVar4 >> 32)));
  return uVar4;
}

