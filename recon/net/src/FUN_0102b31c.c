/* net-core FUN_0102b31c @ 0x102b31c  (parity 300 trials PROVEN) */

extern int FUN_010333b4(void *);
extern void FUN_01033af8(int);
extern void FUN_01033acc(int);
extern int FUN_010339e4(int);
extern int FUN_01033a20(int);
extern int FUN_01033a60(int, int);
extern int FUN_01033aac(int);
extern int FUN_01033888(void);
extern void FUN_01039722(int);

int FUN_0102b31c(int param_1)
{
  volatile int * const p3d0 = (volatile int *)0x210005b4;
  volatile unsigned char * const p3d4 = (volatile unsigned char *)0x21004b9e;
  volatile unsigned char * const pE100 = (volatile unsigned char *)0xe000e100;
  volatile int * const p3e8 = (volatile int *)0x21000580;

  unsigned char local_buf[24];
  int iVar2;
  int iVar1;

  iVar2 = FUN_010333b4(local_buf);
  if (iVar2 != 0) {
    return iVar2;
  }

  FUN_01033af8(3);
  if (*p3d0 == 2) {
    unsigned char v = p3d4[0];
    FUN_01033acc((unsigned char)(v / 5) + 0x50);
  }
  iVar2 = FUN_010339e4(0x21000767);
  if (iVar2 == 0) {
    iVar2 = FUN_01033a20(0x21000763);
    if (iVar2 == 0) {
      iVar2 = FUN_01033a60(0x21000761, 2);
      if (iVar2 == 0) {
        iVar2 = FUN_01033aac(3);
        if (iVar2 == 0) {
          pE100[0x308] = (unsigned char)iVar2;
          if (param_1 == 1) {
            iVar1 = FUN_01033888();
            if (iVar1 != 0) {
              iVar2 = iVar1;
              if (*p3e8 > 0) {
                FUN_01039722(0x103d14a);
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}

