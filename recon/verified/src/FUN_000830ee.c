/* Reconstructed FUN_000830ee @ 0x830ee  (parity: 300/300 trials, PROVEN) */

extern int FUN_000830b0(int, int, unsigned int, unsigned int, unsigned int);
extern void *FUN_0005f5d0(int, int);
extern void FUN_0005cb38(int, int, int);

unsigned int FUN_000830ee(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int uVar3;
  iVar1 = FUN_000830b0(param_1, 2, param_3, param_4, param_4);
  if (iVar1 == 0) {
    uVar3 = 8;
  } else {
    puVar2 = (unsigned int *)FUN_0005f5d0(iVar1 + 0xc, 6);
    *puVar2 = *(unsigned int *)(param_1 + 0x11);
    *(unsigned short *)(puVar2 + 1) = *(unsigned short *)(param_1 + 0x15);
    FUN_0005cb38(param_1, iVar1, 0);
    uVar3 = 0;
  }
  return uVar3;
}

