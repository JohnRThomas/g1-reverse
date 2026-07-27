/* Reconstructed FUN_0008392e @ 0x8392e  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(int a);
extern void FUN_0007ef56(unsigned char *);

void FUN_0008392e(int param_1)
{
  int base = *(int*)(param_1+0x10);
  if (*(char*)(base+0x60) == 0) {
    *(volatile unsigned int*)0x500055b8UL = 2;
  }
  FUN_00072880(base+0x18);
  FUN_0007ef56(param_1);
}

