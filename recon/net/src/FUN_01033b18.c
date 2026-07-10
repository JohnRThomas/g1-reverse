/* net-core FUN_01033b18 @ 0x1033b18  (parity 300 trials PROVEN) */

extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);

void FUN_01033b18(unsigned int param_1, int param_2)
{
  volatile unsigned char * const iVar3 = (volatile unsigned char *)0x41014000;

  *(volatile unsigned int *)(iVar3 + 0x118) = 0;
  *(volatile unsigned int *)(iVar3 + 0x11c) = 0;

  volatile unsigned char * const pbc8 = (volatile unsigned char *)0x2100645c;
  unsigned char bVar2 = pbc8[0];
  unsigned int uVar7 = bVar2 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x198) = uVar7;

  volatile unsigned char * const pbcc = (volatile unsigned char *)0x2100645b;
  unsigned int uVar9 = pbcc[0];
  unsigned int uVar8 = uVar9 | 0x80000000u;
  *(volatile unsigned int *)(iVar3 + 0x19c) = uVar8;

  volatile unsigned char * const pbd0 = (volatile unsigned char *)0x2100645a;
  unsigned char bVar1 = pbd0[0];

  volatile unsigned int *tbl800 = (volatile unsigned int *)(0x4100f800u + (unsigned int)bVar1 * 4);
  *tbl800 = (1u << uVar9) | *tbl800;

  *(volatile unsigned int *)(iVar3 + 0x9c) = uVar7;

  volatile unsigned char * const p8080 = (volatile unsigned char *)0x41008080;
  *(volatile unsigned int *)(p8080 + (param_1 & 0x3f) * 4) = uVar8;

  if (uVar9 > 0x1f) {
    FUN_01039bbe(0x0103d2a7, 0x0103e47c, 0x17d);
    FUN_01039bb0(0x0103e47c, 0x17d);
  }

  volatile unsigned char * const pf080 = (volatile unsigned char *)0x4100f080;
  unsigned int idx = ((unsigned int)bVar1 * 8 + 4) & 0xff;
  *(volatile unsigned int *)(pf080 + idx) = uVar8;

  volatile unsigned char * const pbe4 = (volatile unsigned char *)0x2100645d;
  *(volatile unsigned int *)(iVar3 + 0x98) = pbe4[0] | 0x80000000u;

  if (param_2 != 0) {
    volatile unsigned char * const p9000 = (volatile unsigned char *)0x41019000;
    *(volatile unsigned int *)(p9000 + 0x80) = uVar7;
  }

  volatile unsigned char * const pf000 = (volatile unsigned char *)0x4100f000;
  *(volatile unsigned int *)(pf000 + 0x504) = (1u << bVar2) | (1u << uVar9);
}

