/* net-core FUN_01016e6c @ 0x1016e6c  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern int FUN_0100cb4c(int);
extern void FUN_0101fc70(void);
extern void FUN_010202fc(unsigned int, unsigned int);
extern void FUN_010204f4(unsigned int);
extern int FUN_01020764(int);
extern void FUN_01020898(unsigned int);
extern unsigned int FUN_01020a6c(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_010212ec(unsigned int, unsigned int);

unsigned int FUN_01016e6c(int param_1, int param_2)
{
  volatile unsigned char * const base = (volatile unsigned char *)0x21000f90;
  volatile unsigned char * const tbl = (volatile unsigned char *)0x0103c24c;
  unsigned char bVar1;
  unsigned char bVar5;
  unsigned char r0v;
  unsigned int iVar3;
  unsigned int uVar4;

  if (base[0xbc] < 0x60) {
    bVar5 = tbl[(base[0xbc] >> 5) + 4];
  } else {
    bVar5 = 0;
  }

  bVar1 = base[0xba];
  r0v = bVar1 & 0x3f;
  FUN_010204f4(r0v);
  base[0x8f] = r0v;

  if (param_1 == 0) {
    unsigned int arg1 = *(volatile unsigned int *)(base + 0x74);
    iVar3 = FUN_01020a6c(1, arg1, bVar5);
    if (iVar3 == 0) {
      FUN_01008d00(0x32, 0x93e);
    }
  } else {
    iVar3 = FUN_010212ec(1, bVar5);
    if (iVar3 == 0) {
      return 0;
    }
  }

  if (base[0x88] == 2) {
    uVar4 = 0x40;
  } else {
    uVar4 = 0xff;
  }
  FUN_010202fc(uVar4, bVar5);

  if (base[0xa8] != 0) {
    goto L_final;
  }

  iVar3 = FUN_0100cb4c(param_2 + 5);
  base[0x7c] = (unsigned char)iVar3;
  if (iVar3 != 0) {
    if ((bVar5 & 0xc) == 0) {
      uVar4 = 0x50;
    } else {
      uVar4 = 0x55;
    }
    FUN_0101fc70();
    FUN_01020898(uVar4);
  }

L_final:
  FUN_01020764(param_2);
  return 1;
}

