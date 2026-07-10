/* Reconstructed FUN_00078654 @ 0x78654  (parity: 300/300 trials, PROVEN) */

extern unsigned int *FUN_00076d6c(int size);
extern unsigned int *FUN_00076a94(int a,int b,int c,int d);

void FUN_00078654(int param_1, unsigned int *param_2)
{
  unsigned int *puVar1;
  int iVar2;

  if (*(volatile int *)(param_1 + 0x24) == 0) {
    puVar1 = FUN_00076d6c(0x10);
    *(volatile unsigned int *)(param_1 + 0x24) = (unsigned int)puVar1;
    if (puVar1 == 0) {
      puVar1 = FUN_00076a94(0x000f8cd5, 0x8a, 0, 0x000f8bb7);
    }
    puVar1[1] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
  }
  if (param_2 != 0) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 0xc);
    *param_2 = *(unsigned int *)(iVar2 + param_2[1] * 4);
    *(unsigned int **)(iVar2 + param_2[1] * 4) = param_2;
  }
}

