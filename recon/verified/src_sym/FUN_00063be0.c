/* Reconstructed FUN_00063be0 @ 0x63be0  (parity: 300/300 trials, PROVEN) */

extern long long FUN_00063ba8(int a0);
extern void FUN_0007350c(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00063be0(void)
{
  if (*(volatile unsigned char*)0x2001d563UL == 0) {
    long long uVar1 = FUN_00063ba8(0);
    if ((int)uVar1 != 0) {
      *(volatile unsigned int*)0x2000b310UL = 0;
      FUN_0007350c(0x200066f0, (int)((unsigned long long)uVar1 >> 0x20), 0x8000, 0);
    }
  }
}

