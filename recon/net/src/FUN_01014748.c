/* net-core FUN_01014748 @ 0x1014748  (parity 300 trials PROVEN) */

extern unsigned int FUN_0100f0fc(int);
extern int FUN_0100f1f8(int);
extern void FUN_0100f300(unsigned short, void *, void *);
extern void FUN_01013e98(int, int);
extern void FUN_0101f934(int, int);
extern unsigned int FUN_01023e88(void);
extern unsigned int FUN_01023ea8(unsigned int, unsigned int);

typedef void (*fptr_t)(int);

int FUN_01014748(void)
{
  volatile int * const iVar6base = (volatile int *)0x21000f68;
  volatile fptr_t * const pfp = (volatile fptr_t *)0x210001f4;

  int iVar6 = 0x21000f68;
  int iVar11 = iVar6base[1];

  volatile unsigned char *b11 = (volatile unsigned char *)iVar11;

  unsigned char cVar1 = b11[0x3be];
  unsigned char cVar2 = b11[0x3bf];
  unsigned char cVar7 = cVar1;
  if (cVar1 == 0) {
    cVar7 = b11[0x6e];
  }
  unsigned char cVar9 = cVar2;
  if (cVar2 == 0) {
    cVar9 = b11[0x6f];
  }
  b11[0x6f] = cVar9;
  b11[0x6e] = cVar7;

  fptr_t pcVar10 = *pfp;
  b11[0x70] = 0xff;
  if (pcVar10 != 0) {
    pcVar10(iVar6base[1]);
  }

  iVar11 = iVar6base[1];
  volatile unsigned char *b11b = (volatile unsigned char *)iVar11;
  if (b11b[0x16c] == 1 || cVar1 != 0 || cVar2 != 0) {
    FUN_0101f934(iVar6, 0);
    iVar11 = iVar6base[1];
  }

  unsigned int uVar3 = FUN_0100f0fc(iVar11 + 0x30);
  int iVar11b = FUN_0100f1f8(iVar6base[1]);
  if (iVar11b != 0) {
    volatile unsigned short *puVar8 = (volatile unsigned short *)(int)iVar6base[1];
    FUN_0100f300(puVar8[0], (void *)((char *)puVar8 + 0x30), (void *)((char *)puVar8 + 0x1ce));
  }

  FUN_01013e98(iVar6base[1], 5);
  unsigned int uVar4 = FUN_0100f0fc(iVar6base[1] + 0x30);

  if (uVar3 < uVar4) {
    unsigned int uVar5 = FUN_01023e88();
    uVar4 = uVar4 - uVar3;
    if (uVar4 < 0x76) {
      uVar4 = 0x76;
    }
    unsigned int r = FUN_01023ea8(uVar4, uVar5);
    return r == 0;
  }
  return 1;
}

