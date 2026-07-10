/* net-core FUN_0101ba58 @ 0x101ba58  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int a, unsigned int b);
extern int FUN_0100f0fc(void *p);
extern int FUN_0101a130(void);
extern unsigned int FUN_01023dec(unsigned int a);
extern int FUN_01023ea8(unsigned int a, unsigned int b);
extern unsigned int FUN_0100f368(void *p, int a, unsigned int b);
extern void FUN_01023d38(int a);

void FUN_0101ba58(int param_1, unsigned int param_2)
{
  unsigned int uVar10, uVar11, uVar5;
  int iVar9, iVar4;
  unsigned int uVar6;
  unsigned int iVar12;

  FUN_01008d00(0x35, 0x138);

  {
    unsigned int a = *(volatile unsigned int *)(param_1 + 0x30);
    unsigned int b = *(volatile unsigned int *)(param_1 + 0x14);
    uVar10 = (a >= b) ? b : a;
  }

  iVar12 = 0;
  uVar11 = 0;

  iVar9 = FUN_0100f0fc((void*)(param_1 + 0x30));
  iVar4 = FUN_0101a130();
  iVar9 = iVar9 + iVar4;
  uVar5 = FUN_01023dec(2);
  uVar10 = (uVar10 - iVar9) & ~(unsigned int)((int)(uVar10 - iVar9) >> 31);
  if (uVar5 <= uVar10) uVar10 = uVar5;
  iVar4 = FUN_01023ea8(uVar10, 2);
  if (iVar4 == 0) iVar9 = iVar9 + uVar10;
  iVar4 = FUN_0101a130();
  uVar6 = FUN_0100f368((void*)param_1, iVar9, uVar11);
  *(volatile unsigned int *)(iVar12 + 4) = uVar6;
  FUN_01023d38((iVar9 - 0xb7) - iVar4);
  return;
}

