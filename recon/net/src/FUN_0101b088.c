/* net-core FUN_0101b088 @ 0x101b088  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int a, unsigned int b);
extern void *FUN_01019204(void);
extern unsigned int FUN_0101a130(void);
extern unsigned int FUN_01022e34(unsigned int a, unsigned int b);
extern unsigned int FUN_0101a38c(void *a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int FUN_010231c8(unsigned int a, void *b);

unsigned int FUN_0101b088(unsigned int param_1, int param_2)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char *)0x210010a0;
  void *puVar3;
  unsigned int uVar2 = 0x0101b321;
  int iVar4, iVar5, iVar7;
  unsigned int uVar6, uVar8;
  unsigned char auStack_30[24];

  if (param_2 != 0) {
    return 0x11;
  }
  if (*pcVar1 != 0) {
    return 0xc;
  }
  puVar3 = FUN_01019204();
  pcVar1[1] = 0;
  *pcVar1 = 4;
  pcVar1[0x2e] = 0;
  *(volatile unsigned short *)(pcVar1 + 0x74) = 0;
  iVar4 = FUN_0101a130();
  uVar6 = 0;
  iVar7 = 0;
  uVar8 = 0;
  do {
    iVar5 = uVar6 + 2;
    uVar8 = uVar8 + 1;
    uVar6 = uVar8 & 0xff;
    iVar7 = iVar7 + *(volatile int *)(pcVar1 + iVar5 * 4) + iVar4;
  } while (uVar6 <= (unsigned char)pcVar1[0x2f]);
  *(volatile int *)(pcVar1 + 0x58) = iVar7;
  iVar7 = FUN_01022e34(uVar2, 0);
  *(unsigned char *)puVar3 = (unsigned char)iVar7;
  if (iVar7 == 0x20) {
    FUN_01008d00(0x21, 0x366);
  }
  iVar7 = FUN_0101a38c(auStack_30, 1, 0, param_1);
  if (iVar7 == 0) {
    FUN_01008d00(0x21, 0x368);
  }
  iVar7 = FUN_010231c8(*(unsigned char *)puVar3, auStack_30);
  if (iVar7 != 0) {
    return 0;
  }
  FUN_01008d00(0x21, 0x369);
  return 0;
}

