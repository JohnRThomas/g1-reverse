/* Reconstructed FUN_0002f688 @ 0x2f688  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00072240(int a, void *b, int c, int d);
unsigned int FUN_0002f688(void)
{
  int iVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned char auStack_dc[208];

  iVar1 = 0x20003890;
  uVar2 = 0;
  for (iVar3 = *(volatile int *)(0x20003890UL + 0x24); 0 < iVar3; iVar3 = iVar3 - 1) {
    uVar2 = FUN_00072240(iVar1, auStack_dc, 0, 0);
  }
  return uVar2;
}

