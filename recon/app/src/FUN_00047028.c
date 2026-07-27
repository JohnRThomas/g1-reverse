/* Reconstructed FUN_00047028 @ 0x47028  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007d67e(int a0);
extern void FUN_0007d696(unsigned long);

void FUN_00047028(int param_1, int param_2)
{
  volatile int *piVar1;
  piVar1 = (volatile int *)0x2000a05cUL;
  if (param_1 != *piVar1) {
    FUN_0007d696(param_1);
    *piVar1 = param_1;
  }
  piVar1 = (volatile int *)0x2000a058UL;
  if (param_2 != *piVar1) {
    FUN_0007d67e(param_2);
    *piVar1 = param_2;
  }
}

