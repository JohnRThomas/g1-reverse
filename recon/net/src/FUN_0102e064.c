/* net-core FUN_0102e064 @ 0x102e064  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b) __attribute__((noreturn));
extern int FUN_0102dcf4(int a);
extern int FUN_0103b650(void);
extern void FUN_01036824(unsigned int a);
extern int FUN_0102dc90(int a);
extern unsigned long long FUN_0102df2c(void);
extern void FUN_0103689c(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

typedef unsigned long long (*fnptr2_t)(int *, int);

void FUN_0102e064(void)
{
  volatile int *piVar1 = (volatile int *)0x0103c0fc;
  unsigned int uVar2;
  int iVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned int uVar6 = 0;
  int iVar7;
  int *piVar8;
  unsigned int uVar9;
  unsigned long long uVar10;

  if (((unsigned int)((int)piVar1 - 0x0103c0ec)) >> 4 == 0) {
    FUN_01039bbe(0x0103d2a7, 0x0103d5d7, 0x35c);
    uVar5 = 0x35c;
    FUN_01039bb0(0x0103d5d7, uVar5);
  }
  iVar3 = FUN_0102dcf4(0);
  if (iVar3 == 0) {
    uVar5 = 0xffffffff;
    uVar9 = 0xffffffff;
  } else {
    uVar5 = 0x667;
    uVar9 = 0;
  }
  iVar4 = FUN_0103b650();
  iVar4 = *(volatile int *)(8 + iVar4);
  *(volatile int *)0x21004660 = iVar4;
  if ((iVar4 != 0) && (9 < *(volatile int *)0x21004668)) {
    FUN_01036824(0x21000944);
  }
  uVar2 = 0x21000944;
  iVar4 = 0;
  for (;;) {
    do {
      iVar7 = iVar4;
      if ((iVar3 != 0) && (iVar3 = FUN_0102dc90(iVar3), iVar3 == 0)) {
        uVar5 = 0xffffffff;
        uVar9 = 0xffffffff;
      }
      uVar10 = FUN_0102df2c();
      uVar6 = (unsigned int)(uVar10 >> 32);
      iVar4 = (int)uVar10;
    } while (iVar4 != 0);
    piVar8 = (int *)0x0103c0ec;
    if (iVar7 != 0) {
      for (;;) {
        if (piVar1 < (volatile int *)piVar8) {
          FUN_01039bbe(0x0103d2a7, 0x0103d5d7, 0x350);
          uVar5 = 0x350;
          FUN_01039bb0(0x0103d5d7, uVar5);
        }
        if (piVar1 <= (volatile int *)piVar8) break;
        {
          int base = *(volatile int *)piVar8;
          fnptr2_t fn = *(fnptr2_t *)(base + 0x18);
          if (fn != 0) {
            unsigned long long rc = fn(piVar8, 0);
            uVar6 = (unsigned int)(rc >> 32);
          }
        }
        piVar8 = piVar8 + 4;
      }
    }
    FUN_0103689c(uVar2, uVar6, uVar5, uVar9);
  }
}

