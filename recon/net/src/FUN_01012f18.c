/* net-core FUN_01012f18 @ 0x1012f18  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long ulonglong;

extern int FUN_01008d00(int,int);
extern int FUN_0100d4d0(int,int);
extern int FUN_0100d58c(int,int);
extern int FUN_0100d6e8(uint,int,uint,void*);
extern int FUN_0100f0fc(int);
extern int FUN_0100f48c(int,int);
extern int FUN_0100f63c(void);
extern void FUN_01012c08(void);
extern int FUN_01016160(void);
extern void FUN_0101618c(int);
extern void FUN_010209c8(void*,void*);
extern int FUN_010209e0(int);
extern int FUN_010209f0(int);
extern int FUN_010231c8(int,int);
extern int FUN_010243c0(uint,uint,uint,uint,uint);
extern int FUN_01024678(int,int);
extern int FUN_010247cc(void);
extern short thunk_FUN_010246cc(void);

#define B(o)  (*(byte *)(param_1 + (o)))
#define SC(o) (*(signed char *)(param_1 + (o)))
#define S(o)  (*(short *)(param_1 + (o)))
#define H(o)  (*(ushort *)(param_1 + (o)))
#define I(o)  (*(int *)(param_1 + (o)))
#define U(o)  (*(uint *)(param_1 + (o)))

#define G54B (*(volatile byte *)0x21000f54)
#define G58U (*(volatile uint *)0x21000f58)
#define TBL(idx) (*(short *)(0x0103c1f8 + (uint)(idx) * 2))
#define MAGIC 0x10624dd3u
#define PANIC(x) do { for(;;){ FUN_01008d00(0x30,(x)); } } while(0)

undefined4 FUN_01012f18(int param_1,uint param_2,int param_3,int param_4,short *param_5)
{
  signed char cVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  undefined1 uVar7;
  short sVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;

  (void)uVar2; (void)uVar10; (void)local_34;
  bVar6 = B(0x6f);
  (void)bVar6;
  local_38 = 0;
  sVar8 = thunk_FUN_010246cc();
after_thunk:
  if (0xb < B(0x2d8)) {
    FUN_01008d00(0x30,0x571);
    goto after_thunk;
  }
  cVar1 = SC(0xc6);
  sVar8 = sVar8 + TBL(B(0x2d8));
  if ((((param_3 == 0) && (SC(0x31c) == '\x03')) && (cVar1 == '\x0e')) &&
     (H(0x3bc) == param_2)) {
    U(0x318) = (uint)H(0x362) + (uint)H(0x2f6);
    U(0x310) = U(0x324);
    U(0x314) = U(0x14);
    FUN_0101618c(param_1);
    U(0x24) = U(0x3c0);
    H(0x28) = H(0x3be);
    U(0x14) = U(0x3c4);
    U(0x1c) = U(0x3c8);
    B(0x31c) = 2;
  }
  sVar4 = (short)param_2;
  iVar22 = (int)(short)(sVar4 - S(0x360));
  iVar21 = (int)(short)(sVar4 - S(0xbc));
  if (iVar22 < 0) {
    B(0x333) = 0;
    bVar5 = G54B;
    U(0x358) = U(0x350);
    U(0x35c) = U(0x354);
    iVar22 = iVar21;
    iVar14 = 1;
  }
  else {
    bVar5 = G54B;
    iVar14 = param_4;
  }
  uVar11 = (uint)bVar5;
  if ((uVar11 != 0) && (uVar11 = FUN_010247cc(), uVar11 != 0)) {
    if ((H(0x308) < 2) || ((SC(0x31c) == '\x02' || (B(0x332) != '\0')))) {
      uVar11 = 0;
    }
    else if (U(0x14) < 0x1d4c) {
      uVar11 = 0;
    }
    else {
      if (0xb < B(0x2d8)) { FUN_01008d00(0x30,0x571); goto after_thunk; }
      sVar8 = TBL(B(0x2d8)) + 0x640;
      if (SC(0x31c) == '\x01') {
        if (SC(0xc9) == '\x03') {
          iVar12 = I(0x314);
          iVar19 = I(0x24) + iVar12;
        }
        else {
          iVar19 = I(0x24);
          iVar12 = FUN_0100d58c(B(0x2ef),B(0x6f));
          iVar19 = iVar19 + iVar12;
          iVar12 = I(0x314);
        }
        iVar12 = FUN_01024678(iVar12,sVar8);
        iVar16 = I(0x310);
        iVar20 = I(0x318);
        I(0x310) = iVar12;
        iVar19 = FUN_01024678(iVar19,sVar8);
        iVar17 = I(0x320);
        I(0x320) = iVar19;
        iVar13 = FUN_01024678(U(0x14),sVar8);
        if (U(0x14) < 0x1d4c) {
          iVar13 = iVar13 + 2;
        }
        iVar15 = I(0x324);
        I(0x324) = iVar13;
        uVar11 = (iVar13 - iVar15) *
                 ((((uint)H(0x2f6) + iVar21) - iVar22) + ~U(0x318)) +
                 (iVar12 - iVar16) * iVar20 + (iVar19 - iVar17);
      }
      else {
        iVar12 = FUN_01024678(U(0x14),sVar8);
        iVar19 = I(0x324);
        if (U(0x14) < 0x1d4c) {
          iVar12 = iVar12 + 2;
        }
        I(0x324) = iVar12;
        uVar11 = (iVar12 - iVar19) * (((uint)H(0x2f6) + iVar21) - iVar22);
      }
      B(0x332) = 1;
    }
  }
  switch(B(0x31c)) {
  case 0:
    iVar22 = FUN_0100d58c(B(0x2ef),B(0x6f));
    uVar18 = MAGIC;
    uVar10 = FUN_01024678(I(0x24) + iVar22,sVar8);
    U(0x320) = uVar10;
    iVar21 = FUN_01024678(U(0x14),sVar8);
    if (U(0x14) < 0x1d4c) {
      iVar21 = iVar21 + 2;
    }
    I(0x324) = iVar21;
    FUN_010209c8(&local_30,&local_34);
    iVar21 = FUN_010243c0(U(0x358),U(0x35c),local_30,uStack_2c,local_34);
    bVar6 = B(0x6f);
    iVar14 = FUN_010209f0(bVar6);
    if ((bVar6 & 0xc) == 0) {
      iVar12 = 0;
    }
    else {
      iVar12 = 0x28;
    }
    FUN_0100f48c(param_1,iVar12 + (uint)((ulonglong)uVar18 * (ulonglong)(iVar14 + 0xdf41) >> 0x26) +
                         0xc5);
    local_38 = U(0x368);
    iVar19 = I(0x24);
    iVar14 = FUN_010209f0(B(0x6f));
    iVar12 = I(0x320);
    uVar3 = H(0x28);
    local_38 = (((((local_38 - 0x20) + iVar19) - iVar12) + iVar22) - iVar21) -
               (uint)((ulonglong)uVar18 * (ulonglong)(iVar14 + 0xa3a1) >> 0x26);
    bVar6 = B(0x6f);
    if ((bVar6 & 0xc) == 0) {
      iVar22 = FUN_010209f0(bVar6);
      uVar18 = (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar22 = FUN_010209e0(bVar6);
    uVar9 = iVar22 + (iVar12 + 0x30) * 2 + uVar3 + 0x22 + uVar18;
    G58U = uVar9;
    if (local_38 - U(0x368) < 0x244) {
      FUN_01008d00(0x30,0x51f); goto after_thunk;
    }
    goto LAB_010131f4;
  case 1:
    iVar14 = I(0x324);
    uVar18 = U(0x318);
    uVar2 = H(0x2f6);
    local_38 = iVar22 * (I(0x14) - iVar14);
    iVar12 = I(0x320);
    bVar6 = B(0x6f);
    iVar22 = I(0x310);
    uVar3 = H(0x28);
    if ((bVar6 & 0xc) == 0) {
      iVar19 = FUN_010209f0(bVar6);
      uVar9 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar19 + 0xa3a1) >> 0x26);
    }
    else {
      uVar9 = 0x65;
    }
    iVar19 = FUN_010209e0(bVar6);
    uVar9 = iVar19 + (uint)uVar3 +
                     (iVar14 * (iVar21 + (uint)uVar2 + ~uVar18) + iVar22 * uVar18 + iVar12 + 0x30) *
                     2 + uVar9;
    G58U = uVar9;
LAB_010131f4:
    uVar18 = U(0x14);
    break;
  case 2:
    uVar10 = FUN_01024678(I(0x314) + I(0x24),sVar8);
    U(0x320) = uVar10;
    iVar22 = FUN_01024678(U(0x14),sVar8);
    uVar18 = MAGIC;
    bVar6 = B(0x6f);
    if (U(0x14) < 0x1d4c) {
      iVar22 = iVar22 + 2;
    }
    I(0x324) = iVar22;
    iVar22 = FUN_010209f0(bVar6);
    if ((bVar6 & 0xc) == 0) {
      iVar21 = 0;
    }
    else {
      iVar21 = 0x28;
    }
    FUN_0100f48c(param_1,iVar21 + (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xdf41) >> 0x26) +
                         0xc5);
    if ((S(0x2f6) == 0) && (param_4 != 0)) {
      iVar19 = I(0x314);
      iVar14 = I(0x24);
      uVar7 = B(0x6f);
      iVar22 = FUN_010209f0(uVar7);
      iVar12 = I(0x36c);
      iVar13 = I(0x320);
      iVar21 = FUN_010209e0(uVar7);
      local_38 = (((iVar19 + iVar14 + -0x20 + iVar12) - iVar13) - iVar21) -
                 (uint)((ulonglong)uVar18 * (ulonglong)(iVar22 + 0xa3a1) >> 0x26);
      iVar22 = I(0x320);
    }
    else {
      iVar22 = I(0x320);
      local_38 = (I(0x314) + I(0x24)) - iVar22;
    }
    iVar14 = I(0x310);
    iVar21 = I(0x318);
    bVar6 = B(0x6f);
    uVar3 = H(0x28);
    if ((bVar6 & 0xc) == 0) {
      iVar12 = FUN_010209f0(bVar6);
      uVar18 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar12 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar12 = FUN_010209e0(bVar6);
    uVar9 = iVar12 + (uint)uVar3 + (iVar21 * iVar14 + iVar22 + 0x30) * 2 + uVar18;
    uVar18 = U(0x14);
    G58U = uVar9;
    B(0x31c) = 1;
    break;
  case 3:
    uVar18 = U(0x14);
    local_38 = uVar18 * iVar22;
    if ((param_4 == 0) || (S(0x2f6) != 0)) {
      if (SC(0x333) != '\0') {
        uVar9 = G58U;
        break;
      }
      uVar18 = (uint)H(0x2f6);
    }
    else {
      B(0x333) = 0;
      uVar18 = 0;
    }
    iVar12 = I(0x324);
    uVar9 = local_38 - iVar12 * iVar22;
    if ((((SC(0xc5) == '&') || (SC(0xc6) == '&')) &&
        (-1 < (int)((param_2 - H(0x3bc)) * 0x10000))) &&
       (B(0x3bf) != 0)) {
      bVar6 = B(0x3bf);
    }
    local_38 = uVar9;
    if ((iVar14 != 0) && (uVar18 == 0)) {
      iVar22 = I(0x36c);
      if (iVar22 == 0) {
        FUN_01008d00(0x30,0x571); goto after_thunk;
      }
      bVar5 = B(0x6f);
      if ((bVar5 & 0xc) == 0) {
        iVar14 = FUN_010209f0(bVar5);
        iVar22 = I(0x36c);
        bVar5 = B(0x6f);
        iVar14 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar14 + 0xa3a1) >> 0x26) + 0x10;
      }
      else {
        iVar14 = 0x75;
      }
      iVar19 = FUN_010209e0(bVar5);
      uVar18 = (uint)H(0x2f6);
      iVar12 = I(0x324);
      local_38 = (((uVar9 - 0x10) + iVar22) - iVar14) - iVar19;
    }
    iVar22 = (iVar12 * (uVar18 + iVar21) + 0x30) * 2;
    if ((bVar6 & 0xc) == 0) {
      iVar21 = FUN_010209f0(bVar6);
      uVar18 = (uint)((ulonglong)MAGIC * (ulonglong)(iVar21 + 0xa3a1) >> 0x26);
    }
    else {
      uVar18 = 0x65;
    }
    iVar21 = FUN_010209e0(bVar6);
    uVar9 = uVar18 + iVar21 + iVar22;
    uVar18 = U(0x14);
    G58U = uVar9;
    if (uVar18 < 0x1d4c) {
      uVar7 = FUN_0100d6e8(uVar18,iVar22,0x21000f58,&local_38);
      B(0x333) = uVar7;
      uVar9 = G58U;
      uVar18 = U(0x14);
    }
    break;
  default:
    FUN_01008d00(0x30,0x586);
    goto after_thunk;
  }
  local_38 = local_38 - uVar11;
  uVar11 = (uVar18 - I(0x324)) - 0x1d8;
  if (uVar9 <= uVar11) {
    uVar11 = uVar9;
  }
  U(0x2f0) = uVar11;
  {
    uint _a358 = U(0x358);
    U(0x348) = _a358 + local_38;
    U(0x34c) = I(0x35c) + (uint)(((ulonglong)_a358 + local_38) >> 0x20);
  }
  B(0x338) = 0;
  H(0x340) = 0x92;
  iVar22 = FUN_0100f0fc(param_1 + 0x30);
  S(0x360) = sVar4;
  U(0x33c) = uVar11 + iVar22;
  U(0x358) = U(0x348);
  U(0x35c) = U(0x34c);
  iVar22 = FUN_01016160();
  if (iVar22 != 0) {
    I(0x33c) = I(0x33c) + 0x1e;
  }
  sVar4 = S(0x2e0) - sVar4;
  B(0x342) = 0;
  if (0 < sVar4) {
    B(0x342) = 2;
  }
  if (cVar1 == '\x0e') {
    if (param_4 == 0) goto LAB_010130aa;
  }
  else if (param_4 == 0) {
    if ((SC(0x31c) != '\0') &&
       (sVar8 = FUN_0100d4d0(param_1 + 0x338,I(0x14) - I(0x324)), sVar8 != 0)) {
      if (param_5 == (short *)0x0) {
        return 1;
      }
      *param_5 = sVar8;
      return 1;
    }
    goto LAB_010130aa;
  }
  uVar3 = H(0x308);
  if (uVar3 == 0) {
    H(0x30a) = uVar3;
  }
  else if (((uint)H(0x30a) * (uint)B(0x30c) + (uint)B(0x30c) < (uint)uVar3) && (0 < sVar4)) {
    H(0x30a) = H(0x30a) + 1;
    B(0x342) = 0;
    bVar6 = FUN_0100f63c();
    B(0x30c) = (bVar6 & 7) + 1;
  }
LAB_010130aa:
  iVar22 = FUN_010231c8(B(0x364),param_1 + 0x338);
  if (iVar22 != 0) {
    B(0x330) = (byte)param_3 ^ 1;
    return 0;
  }
  PANIC(0x5cf);
  return 0;
}

