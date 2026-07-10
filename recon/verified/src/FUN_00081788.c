/* Reconstructed FUN_00081788 @ 0x81788  (parity: 300/300 trials, PROVEN) */

extern void FUN_000815f6(int, int*);

void FUN_00081788(int param_1, int *param_2)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  if (*(int**)(param_1+0x54) != 0) {
    piVar1 = 0;
    piVar2 = *(int**)(param_1+0x54);
    do {
      if (param_2 == piVar2 - 2) {
        FUN_000815f6(param_1+0x54, piVar1);
        return;
      }
      piVar3 = (int*)*piVar2;
      piVar1 = piVar2;
      piVar2 = piVar3;
    } while (piVar3 != 0);
  }
}

