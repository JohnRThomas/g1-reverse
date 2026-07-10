/* Reconstructed FUN_00081660 @ 0x81660  (parity: 300/300 trials, PROVEN) */

extern void FUN_000815f6(int, int*, int*, unsigned int, int);

int * FUN_00081660(int param_1, unsigned int param_2, int param_3, int param_4)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;

  if (param_2 - 0x40 < 0x40) {
    piVar2 = *(int **)(long)(param_1 + 0x54);
    if (piVar2 != 0) {
      piVar1 = 0;
      piVar3 = piVar2;
      do {
        if (*(unsigned short *)((char*)piVar3 + 12) == param_2) {
          FUN_000815f6(param_1 + 0x54, piVar1, piVar3, param_2, param_4);
          return (int*)((char*)piVar3 - 8);
        }
        piVar2 = *(int **)piVar3;
        piVar1 = piVar3;
        piVar3 = piVar2;
      } while (piVar2 != 0);
    }
  } else {
    piVar2 = 0;
  }
  return piVar2;
}

