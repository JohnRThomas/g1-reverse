/* Reconstructed FUN_00010840 @ 0x10840  (parity: 300/300 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long u64;

extern u64 FUN_0000d824(int a);
extern u64 FUN_0000d848(void);
extern u64 FUN_0000db4c(int a, int b, int c, int d);
extern void FUN_0000d8f8(int a, int b, int c, int d);
extern int FUN_0000dddc(int a, int b, int c, int d);
extern int FUN_0000de18(int a, int b, int c, int d);
extern int FUN_0000dee8(void);
extern int FUN_000167a8(void);
extern int FUN_0002e648(int a);

static float BF(unsigned int h) { union { unsigned int i; float f; } u; u.i = h; return u.f; }

byte FUN_00010840(void)
{
  volatile byte *DAT_a40 = (volatile byte*)0x20018da1UL;
  volatile byte *DAT_a44 = (volatile byte*)0x20018da0UL;
  byte bVar5;
  int iVar2, iVar3;
  u64 uVar6, uVar7;
  float fVar4;
  int r0val;

  if (*DAT_a40 == 0) {
    return 0xff;
  }
  iVar2 = FUN_0002e648(0);
  if ((uint)(iVar2 + 1) < 2) {
    return 0xff;
  }

  iVar3 = FUN_000167a8();
  if ( (*(volatile int*)(long)(iVar3+0xfb0) == 0)
    || (iVar3 = FUN_000167a8(), *(volatile int*)(long)(iVar3+0xfb0) == -1)
    || (iVar3 = FUN_000167a8(), *(volatile int*)(long)(iVar3+0xfb0) < 0xea61) ) {
    if (iVar2 < 0x32) {
      bVar5 = (byte)(iVar2 / 5);
    } else if (iVar2 < 200) {
      bVar5 = (byte)((((uint)iVar2 - 0x32u) / 10u) + 10u);
    } else if (iVar2 < 1000) {
      bVar5 = (byte)((((uint)iVar2 - 200u) / 0x32u) + 0x19u);
    } else if (iVar2 < 10000) {
      bVar5 = (byte)((((uint)iVar2 - 1000u) / 1000u) + 0x29u);
    } else {
      if (0x1387f < iVar2) {
        return 0x2a;
      }
      bVar5 = (byte)((((uint)iVar2 - 10000u) / 5000u) + 0x32u);
    }
    if (0x29 < bVar5) bVar5 = 0x2a;
  } else {
    uVar6 = FUN_0000d824(iVar2);
    iVar2 = FUN_000167a8();
    uVar7 = FUN_0000d824(*(volatile int*)(long)(iVar2+0xfb0));
    uVar7 = FUN_0000db4c((int)uVar7, (int)(uVar7>>32), 0, 0);
    FUN_0000d8f8((int)uVar7, (int)(uVar7>>32), (int)uVar6, (int)(uVar6>>32));
    r0val = FUN_0000dee8();
    { union { int i; float f; } u; u.i = r0val; fVar4 = u.f; }
    bVar5 = *DAT_a44;
    if (bVar5 == 0xc) {
      if (fVar4 > BF(0x42f00000)) {
        bVar5 = 0x13;
      } else if (fVar4 < 8.0f) {
        bVar5 = 6;
      }
    } else if (bVar5 > 0xc) {
      if (bVar5 == 0x1a) {
        if (fVar4 > BF(0x44b40000)) {
          bVar5 = 0x2a;
        } else if (fVar4 < BF(0x43ba0000)) {
          bVar5 = 0x13;
        }
      } else if (bVar5 == 0x2a) {
        if (fVar4 < BF(0x44700000)) {
          bVar5 = 0x1a;
        }
      } else if (bVar5 == 0x13) {
        if (fVar4 > BF(0x43f80000)) {
          bVar5 = 0x1a;
        } else if (fVar4 < BF(0x42960000)) {
          bVar5 = 0xc;
        }
      }
    } else {
      if (bVar5 == 3) {
        if (fVar4 > 6.0f) {
          bVar5 = 6;
        } else {
          uVar6 = FUN_0000d848();
          iVar2 = FUN_0000dddc((int)uVar6,(int)(uVar6>>32),0,0);
          if (iVar2 != 0) bVar5 = 0;
        }
      } else if (bVar5 == 6) {
        if (fVar4 > 12.0f) {
          bVar5 = 0xc;
        } else if (fVar4 < 4.0f) {
          bVar5 = 3;
        }
      } else if (bVar5 == 0) {
        uVar6 = FUN_0000d848();
        iVar2 = FUN_0000de18((int)uVar6,(int)(uVar6>>32),0,0);
        if (iVar2 != 0) bVar5 = 3;
      }
    }
    *DAT_a44 = bVar5;
  }
  return bVar5;
}

