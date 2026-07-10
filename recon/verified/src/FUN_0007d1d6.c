/* Reconstructed FUN_0007d1d6 @ 0x7d1d6  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004a46c(unsigned int, unsigned int);
extern void FUN_00016574(unsigned int);

void FUN_0007d1d6(int param_1, unsigned int param_2)
{
  int iVar1;
  char *base = (char*)param_1;
  int *p1 = *(int **)(base + 0xff4);

  iVar1 = *(int*)((char*)p1 + 0x164);
  if (iVar1 != 0) {
    **(int **)(base + 0xfec) = iVar1;
  }
  FUN_0004a46c(param_2, 0);
  p1 = *(int **)(base + 0xff4);
  if (*(int*)((char*)p1 + 0x164) != 0) {
    *(unsigned int*)((char*)p1 + 0x164) = **(unsigned int **)(base + 0xfec);
  }
  FUN_00016574(**(unsigned int **)(base + 0xfec));
  return;
}

