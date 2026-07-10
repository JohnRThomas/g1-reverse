/* Reconstructed FUN_00086668 @ 0x86668  (parity: 300/300 trials, PROVEN) */

extern void FUN_000742b4(int *p);
extern void FUN_000738d4(int *p);

unsigned int FUN_00086668(int *param_1)
{
  unsigned int uVar1;
  int *piVar2;

  uVar1 = 0;
  while ((piVar2 = (int *)*param_1, param_1 != piVar2 && (piVar2 != (int *)0)))
  {
    FUN_000742b4(piVar2);
    FUN_000738d4(piVar2);
    uVar1 = 1;
  }
  return uVar1;
}

