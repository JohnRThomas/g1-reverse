/* Reconstructed FUN_00034dbc @ 0x34dbc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int undefined4;
typedef unsigned char byte;
typedef unsigned int uint;

extern void DEBUG_PRINT(undefined4 fmt, ...);
extern void FUN_00019c70(void);
extern void FUN_00064b1c(int a);
extern int FUN_0008500c(void);
extern unsigned int FUN_00085020(int a);
extern int FUN_00085030(int a);
extern int FUN_0008503c(int a, ...);
extern int FUN_000850c8(void);
extern void FUN_00086c78(void *dst, int val, int n);
extern void FUN_0008705a(void *dst, void *src, int n);

undefined4 FUN_00034dbc(undefined4 param_1,undefined4 param_2,undefined4 param_3)
{
  volatile byte *pbVar2;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar9;
  uint uVar10;
  volatile byte *pbVar11;
  uint uVar12;
  byte bVar13;
  int bVar14;

  iVar5 = FUN_0008500c();
  pbVar2 = (volatile byte *)0x2001a22cUL;
  if (iVar5 == 0) {
    if (*(volatile int*)0x20007554UL == 0) {
      DEBUG_PRINT(0,param_1);
    } else {
      FUN_00019c70();
    }
    return 0;
  }
  FUN_00086c78((void*)pbVar2,0,0x15e2);
  iVar6 = FUN_0008503c(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  bVar14 = *(int *)(iVar6 + 0xc) == 2;
  bVar4 = (byte)((*pbVar2 & 0xfe) | (byte)bVar14);
  *pbVar2 = bVar4;
  iVar6 = FUN_0008503c(iVar5,0,bVar4,bVar14,param_1,param_2,param_3);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  uVar12 = (uint)(*(int *)(iVar6 + 0xc) == 2);
  uVar10 = (uint)((*pbVar2 & 0xfffffffd) | (uVar12 << 1));
  *pbVar2 = (byte)uVar10;
  iVar6 = FUN_0008503c(iVar5,0,uVar10,uVar12,param_1,param_2,param_3);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xf7) | (byte)((*(int *)(iVar6 + 0xc) == 2) << 3));
  iVar6 = FUN_0008503c(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xfb) | (byte)((*(int *)(iVar6 + 0xc) == 2) << 2));
  iVar6 = FUN_0008503c(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  iVar7 = FUN_0008503c(iVar6,0);
  if (iVar7 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xef) | (byte)((*(int *)(iVar7 + 0xc) == 2) << 4));
  iVar6 = FUN_0008503c(iVar6,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)0x20007554UL;
    goto tail;
  }
  iVar7 = FUN_000850c8();
  if (iVar7 != 0) {
    bVar4 = (byte)(FUN_00085020(iVar6) & 0xffu);
    bVar13 = 0;
    if (99 < bVar4) {
      bVar4 = 100;
    }
    uVar12 = 0;
    pbVar2[1] = bVar4;
    for (; bVar13 < pbVar2[1]; bVar13 = bVar13 + 1) {
      iVar7 = FUN_00085030(iVar6);
      if (iVar7 == 0) {
        iVar7 = *(volatile int*)0x20007554UL;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          FUN_00019c70();
        }
        continue;
      }
      iVar9 = FUN_0008503c(iVar7,0);
      if (iVar9 == 0) {
        iVar7 = *(volatile int*)0x20007554UL;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          FUN_00019c70();
        }
        continue;
      }
      iVar7 = FUN_0008503c(iVar7,0);
      if (iVar7 == 0) {
        iVar7 = *(volatile int*)0x20007554UL;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          FUN_00019c70();
        }
        continue;
      }
      pbVar11 = pbVar2 + uVar12 * 0x38 + 2;
      FUN_00086c78((void*)pbVar11,0,0x28);
      FUN_00086c78((void*)(pbVar2 + uVar12 * 0x38 + 0x2a),0,0x10);
      FUN_0008705a((void*)pbVar11,*(void **)(iVar9 + 0x10),0x27);
      FUN_0008705a((void*)(pbVar2 + uVar12 * 0x38 + 0x2a),*(void **)(iVar7 + 0x10),0xf);
      uVar12 = (uVar12 + 1) & 0xff;
    }
  }
  FUN_00064b1c(iVar5);
  return 1;

tail:
  if (iVar6 == 0) {
    DEBUG_PRINT(0);
  } else {
    FUN_00019c70();
  }
  FUN_00064b1c(iVar5);
  return 0;
}

