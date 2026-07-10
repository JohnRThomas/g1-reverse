/* Reconstructed FUN_0006b378 @ 0x6b378  (parity: 300/300 trials, PROVEN) */

extern void FUN_00068908(int a, unsigned int b, unsigned int c, unsigned int d);

void FUN_0006b378(int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char bVar1;
  int iVar2;
  int iVar3;
  unsigned int uVar4;
  unsigned int uVar5;

  uVar4 = *(unsigned int *)(param_1 + 0x20);
  uVar5 = uVar4 + 1;
  bVar1 = *param_2;
  if ((int)uVar5 < 0x21) {
    *(unsigned int *)(param_1 + 0x20) = uVar5;
    *(unsigned int *)(param_1 + 0x1c) = *(unsigned int *)(param_1 + 0x1c) | ((unsigned int)bVar1 << (uVar4 & 0xff));
    iVar2 = uVar4 + 10;
    iVar3 = *(int *)(param_2 + 4);
  } else {
    FUN_00068908(param_1,(unsigned int)bVar1,1,0);
    uVar5 = *(unsigned int *)(param_1 + 0x20);
    iVar3 = *(int *)(param_2 + 4);
    iVar2 = uVar5 + 9;
  }
  if (iVar2 < 0x21) {
    *(unsigned int *)(param_1 + 0x1c) = *(unsigned int *)(param_1 + 0x1c) | ((unsigned int)iVar3 << (uVar5 & 0xff));
    *(int *)(param_1 + 0x20) = iVar2;
    return;
  }
  FUN_00068908(param_1,iVar3,9,param_4);
}

