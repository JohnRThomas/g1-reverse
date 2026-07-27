/* Reconstructed FUN_0008253a @ 0x8253a  (parity: 300/300 trials, PROVEN) */

extern int * FUN_0005858c(unsigned long);

int *FUN_0008253a(unsigned int param_1, int param_2)
{
  int *piVar1;
  int *piVar2;
  piVar1 = FUN_0005858c(param_1);
  if (piVar1 != 0) {
    for (piVar2 = *(int **)((char *)piVar1 + 0x30); piVar2 != 0; piVar2 = (int *)*piVar2) {
      if (*(int *)(piVar2[-0x1b] + 0x18) == param_2) {
        return (int *)piVar2[-0x1b];
      }
    }
    for (piVar1 = *(int **)((char *)piVar1 + 4); piVar1 != 0 && piVar1[6] != param_2; piVar1 = (int *)*piVar1) {}
  }
  return piVar1;
}

