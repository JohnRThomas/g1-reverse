/* readable reconstruction; identity: FUN_01012c84 @ 0x01012c84
 * public-name: FUN_01012c84
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01012c84 @ 0x1012c84  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef long long longlong;
typedef unsigned long long ulonglong;

extern int FUN_01008d00(int,int);
extern int FUN_01012704(void);
extern int FUN_01023d38(int);
extern int FUN_010126c0(void);
extern long long FUN_010122b4(void*,int);
extern int FUN_01023ea8(int,int);
extern int FUN_0101272c(void*);
extern void FUN_010127f8(void*);
extern void FUN_01020d1c(void*,uint);
extern int thunk_FUN_01025028(void);
extern int FUN_010218d8(void);
extern int FUN_010218e4(void);
extern int FUN_01025cf0(void*);
extern int FUN_01021614(int);
extern int FUN_010215d8(void);
extern int FUN_010215f4(void);
extern int FUN_01021634(void);
extern int FUN_01020a6c(int);
extern int FUN_01020500(void);
extern int FUN_01025be0(void);
extern int FUN_010208b0(void);
extern int FUN_0101fca8(void);
extern int FUN_010140ec(void*,int);
extern int FUN_0101f888(void);
extern int FUN_0100ef88(void*,int,int,uint);
extern int FUN_01022ebc(int);
extern int FUN_010126e8(void);
extern int FUN_010126b0(void*);
extern int FUN_010126b8(void*);
extern int FUN_01021908(int);
extern int FUN_01021914(int);
extern int FUN_01025d28(void);
extern long long thunk_FUN_01025034(void);
extern short FUN_010246d8(void);
extern uint FUN_01022ea8(void);
extern int FUN_0100d4d0(void*,int);
extern int FUN_010128bc(void*,int,int,int);
extern int FUN_010231c8(int,void*);
extern uint FUN_0101232c(void*,uint,uint,uint);

void FUN_01012c84(undefined1 *param_1,uint param_2,undefined4 param_3,uint param_4)
{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  ushort uVar4;
  int iVar5;
  char cVar6;
  short sVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  short sVar17;
  longlong lVar18;
  undefined8 uVar19;
  undefined4 uStack_24;

  iVar5 = 0x210015f0;
  iVar8 = 0x4100c000;
  if (param_1 == (undefined1 *)0x0) {
    FUN_01008d00(0x30,0xcd);
  }
  switch(param_2) {
  case 0:
    iVar8 = FUN_01012704();
    if (iVar8 == 0) {
      FUN_01023d38(*(int *)(param_1 + 300) + -0x141);
      return;
    }
    FUN_01008d00(0x30,0x27e);
  case 1:
    iVar8 = FUN_010126c0();
    if (iVar8 == 0) {
      iVar8 = (int)FUN_010122b4(param_1,0);
      param_4 = *(uint *)(param_1 + 300);
      uVar15 = iVar8 + 0x152;
      if (param_4 < uVar15) {
        uVar14 = uVar15 - param_4;
        if (uVar14 < 0x76) {
          uVar14 = 0x76;
        }
        iVar8 = FUN_01023ea8(uVar14,3);
        *(uint *)(param_1 + 300) = uVar15;
        if (iVar8 != 0) {
          FUN_010127f8(param_1);
          return;
        }
      }
      else {
        *(uint *)(param_1 + 300) = uVar15;
      }
    }
    iVar8 = FUN_0101272c(param_1);
    if (iVar8 == 0) {
      return;
    }
    FUN_01008d00(0x30,0x2b4);
  case 2:
  case 3:
    break;
  case 4:
    /* The image tail-branches to the shared radio-event handler here. */
    FUN_01020d1c(param_1,param_2);
    return;
#if 0 /* stale inlined Ghidra continuation; the raw CFG leaves this function */
    *(undefined4 *)(0x4100c000 + 0x4c) = 1;
    iVar8 = *(int *)(iVar8 + 0x54c);
    uVar9 = thunk_FUN_01025028();
    *(undefined4 *)(iVar5 + 0x38) = uVar9;
    *(undefined4 *)(iVar5 + 0x3c) = 0;
    *(int *)(iVar5 + 0x40) = iVar8;
    if (0x95 < *(ushort *)(iVar5 + 0x1c)) {
      if (*(char *)(iVar5 + 9) == '\x01') {
        iVar12 = FUN_010218d8();
        if (1 < iVar12 + 1U) {
          FUN_01008d00(0x3e,0x851);
        }
      }
      else if ((*(char *)(iVar5 + 9) == '\x02') && (iVar12 = FUN_010218e4(), 1 < iVar12 + 1U)) {
        FUN_01008d00(0x3e,0x857);
      }
    }
    uVar15 = 0xfffffee2;
    iVar12 = 0x41008000;
    *(undefined4 *)(0x41008000 + 0x80) = 0;
    *(undefined4 *)(iVar12 + 0x84) = 0;
    *(undefined4 *)(iVar12 + 0x88) = 0;
    *(undefined4 *)(iVar12 + 0x80) = 0;
    *(undefined4 *)(iVar12 + 0x84) = 0;
    *(undefined1 *)(iVar5 + 0x35) = 0;
    cVar6 = *(char *)(iVar5 + 0xc);
    *(uint *)(iVar12 + 0x200) = uVar15 & *(uint *)(iVar12 + 0x200);
    iVar10 = 0x41008000;
    if (cVar6 == '\0') {
      cVar6 = *(char *)(iVar5 + 9);
      iVar12 = 0;
      if (cVar6 != '\x01') goto LAB_01020d82;
LAB_01020e60:
      uVar15 = *(uint *)(0x41008000 + 0x10c);
      if (uVar15 != 0) {
        uVar15 = 8;
        goto LAB_01020d96;
      }
LAB_01020d88:
      if (*(int *)(0x41008000 + 0x110) != 0) {
        uVar15 = uVar15 & 0xff | 0x10;
      }
    }
    else {
      iVar12 = *(int *)(iVar12 + 0x4144);
      cVar6 = *(char *)(iVar5 + 9);
      if (iVar12 != 0) {
        iVar12 = 1;
      }
      if (cVar6 == '\x01') goto LAB_01020e60;
LAB_01020d82:
      if (cVar6 != '\x02') {
        uVar15 = 0;
        goto LAB_01020d88;
      }
      if (*(int *)(0x41008000 + 0x10c) == 0) {
        uVar14 = 0;
        uVar15 = 4;
      }
      else {
        uVar15 = 6;
        uVar14 = 2;
      }
      if ((*(uint *)(0x41008000 + 0x400) & 1) != 0) {
        uVar15 = uVar14;
      }
      if (iVar12 != 0) {
        uVar14 = uVar15 & 0xb | 1;
        uVar15 = uVar15 | 1;
      }
      if (uVar14 == 0) goto LAB_01020d88;
    }
LAB_01020d96:
    iVar12 = *(int *)(0x41008000 + 0x104);
    if (iVar12 != 0) {
      iVar12 = 1;
    }
    *((char *)&uStack_24) = (char)iVar12;
    *(undefined4 *)(0x41008000 + 0x100) = 0;
    *(undefined4 *)(iVar10 + 0x10c) = 0;
    *(undefined4 *)(iVar10 + 0x110) = 0;
    *(undefined4 *)(iVar10 + 0x104) = 0;
    *(undefined4 *)(iVar10 + 0x114) = 0;
    *(undefined4 *)(iVar10 + 0x118) = 0;
    *(undefined4 *)(iVar10 + 0x108) = 0;
    *(undefined4 *)(iVar10 + 0x16c) = 0;
    iVar10 = FUN_01025cf0(&uStack_24);
    iVar12 = 0x4100c000;
    if (iVar10 != 0) {
      uVar15 = uVar15 & 0xff | 0x10;
    }
    *(undefined4 *)(0x4100c000 + 0x144) = 0;
    if (((uVar15 & 0x18) == 0x10) && (*(char *)(iVar5 + 9) == '\x01')) {
      iVar10 = *(int *)(iVar12 + 0x548);
      uVar9 = *(undefined4 *)(iVar12 + 0x544);
      uVar15 = uVar15 & 0xff | 0x20;
      *(int *)(iVar5 + 0x24) = iVar10;
      *(undefined4 *)(iVar5 + 0x20) = uVar9;
      if (*(char *)(iVar5 + 0x29) == '\x02') goto LAB_01020ec2;
LAB_01020e02:
      cVar6 = *(char *)(iVar5 + 0x18);
    }
    else {
      iVar10 = *(int *)(0x4100c000 + 0x548);
      uVar9 = *(undefined4 *)(0x4100c000 + 0x544);
      *(int *)(iVar5 + 0x24) = iVar10;
      *(undefined4 *)(iVar5 + 0x20) = uVar9;
      if ((*(char *)(iVar5 + 0x29) != '\x02') && (*(char *)(iVar5 + 9) != '\x02'))
      goto LAB_01020e02;
LAB_01020ec2:
      cVar6 = *(char *)(iVar5 + 0x18);
      if ((cVar6 == '\x04') || (cVar6 == '\b')) {
        if ((*(uint *)(0x41008000 + 0x414) & 6) == 0) {
          cVar6 = '\b';
        }
        else {
          cVar6 = '\x04';
        }
      }
    }
    cVar1 = *(char *)(iVar5 + 9);
    bVar2 = *(byte *)(iVar5 + 8);
    uVar14 = (uint)bVar2;
    *(char *)(iVar5 + 0x28) = cVar6;
    *(char *)(iVar5 + 0x29) = cVar1;
    if (uVar14 == 0) {
      *(ushort *)(iVar5 + 7) = (ushort)bVar2;
      *(byte *)(iVar5 + 9) = bVar2;
      *(byte *)(iVar5 + 0xc) = bVar2;
      uVar9 = 0;
    }
    else if ((uVar15 & 0x11) == 0) {
      iVar12 = uVar14 - 1;
      cVar6 = *(char *)(iVar5 + 7);
      *(undefined1 *)(iVar5 + 9) = 0;
      *(undefined2 *)(iVar5 + 7) = 0;
      if (iVar12 != 0) {
        iVar12 = 1;
      }
      if (cVar1 == '\0') {
        FUN_01008d00(0x3e,0x804);
      }
      if (uVar14 == 1) {
        if (cVar1 == '\x01') {
          iVar11 = FUN_01021614(*(undefined2 *)(iVar5 + 0x1c));
          uVar14 = iVar11 + iVar10;
        }
        else {
          iVar11 = FUN_010215d8();
          uVar14 = iVar11 + iVar10;
        }
      }
      else if (cVar1 == '\x01') {
        iVar11 = FUN_010215f4();
        uVar14 = iVar11 + iVar10;
      }
      else {
        iVar11 = FUN_01021634();
        uVar14 = iVar11 + iVar10;
      }
      if (cVar6 == '\x01') {
        if (uVar14 < iVar8 + 0x3bU) {
          *(undefined4 *)(0x41008000 + 0x10) = 1;
          uVar9 = 1;
          goto LAB_01020ee8;
        }
        *(undefined1 *)(iVar5 + 7) = 1;
      }
      iVar8 = FUN_01020a6c(iVar12);
      if (iVar8 == 0) {
        FUN_01008d00(0x3e,0xa52);
      }
      uVar9 = 0;
    }
    else {
      FUN_01020500();
      uVar9 = 0;
    }
LAB_01020ee8:
    iVar8 = 0x41008000;
    if (*(char *)(iVar5 + 0x44) != '\0') {
      *(undefined4 *)(0x41008000 + 0x1ac) = 0;
      *(undefined1 *)(iVar5 + 0x44) = 0;
      *(uint *)(iVar8 + 0x514) = *(uint *)(iVar8 + 0x514) & 0xfff0ffff;
      uVar14 = *(uint *)(iVar5 + 0x14) & 0xfffffffc;
      *(uint *)(iVar8 + 0x900) = uVar14;
      *(uint *)(iVar5 + 0x14) = uVar14;
      *(undefined4 *)(iVar8 + 0x910) = 0x23280;
    }
    if ((int)(uVar15 << 0x1f) < 0) {
LAB_01020ff6:
      (**(int (**)(void))(iVar5 + 0x4c))();
      uVar15 = uVar15 & 0x10;
      if (uVar15 == 0) goto LAB_01021000;
LAB_01020f2e:
      (**(int (**)(void))(iVar5 + 0x58))();
      if (*(char *)(iVar5 + 9) != '\x02') goto LAB_01020f60;
    }
    else {
      if ((int)(uVar15 << 0x1e) < 0) {
        uVar14 = *(uint *)(0x41008000 + 0x450);
        if (((int)(uVar14 << 7) < 0) &&
           (((((uVar14 & 0xf00) == 0 || (uVar14 & 0xf0) == 0 || ((uVar14 & 0xf) == 0)) &&
             ((uVar14 << 8) >> 0x1d < 3)) && (*(int *)(0x41008000 + 0x454) != 0))))
        goto LAB_01020ff6;
        if (*(byte *)(iVar5 + 0x34) < *(byte *)(*(int *)(iVar5 + 0x30) + 1)) {
          uVar14 = 0;
          uVar15 = uVar15 & 0xff;
        }
        else {
          uVar14 = ((uVar15 ^ 4) << 0x1d) >> 0x1f;
        }
        (**(int (**)(int,int))(iVar5 + 0x50))(uVar14,uVar9);
      }
      else if ((uVar15 & 0x28) != 0) {
        (**(int (**)(int,int))(iVar5 + 0x54))(uVar9,((uVar15 ^ 0x20) << 0x1a) >> 0x1f);
      }
      uVar15 = uVar15 & 0x10;
      if (uVar15 != 0) goto LAB_01020f2e;
LAB_01021000:
      if (*(char *)(iVar5 + 9) != '\x02') {
        FUN_01025be0();
        return;
      }
    }
    cVar6 = *(char *)(iVar5 + 0xc);
    if (cVar6 != '\0') {
      if (cVar6 == '\x02') {
        *(int *)(0x4100c000 + 0x544) = *(int *)(iVar5 + 0x24) + *(int *)(iVar5 + 0x10);
      }
      else {
        if (cVar6 != '\x01') {
          FUN_01008d00(0x3e,0xc15);
        }
        if (*(uint *)(iVar5 + 0x10) <= *(uint *)(iVar5 + 0x24)) {
          FUN_01008d00(0x3e,0xc16);
        }
        *(uint *)(0x4100c000 + 0x544) = *(uint *)(iVar5 + 0x10);
      }
      *(undefined4 *)(0x4100c000 + 0x1c4) = 0x8000000b;
    }
LAB_01020f60:
    cVar6 = (char)FUN_01025be0();
    iVar8 = 0xe000e100;
    if ((uVar15 != 0) && (cVar6 != '\x01')) {
      uStack_24 = 0;
      do {
        uStack_24 = uStack_24 + 1;
        if (uStack_24 == -1) {
          FUN_01008d00(0x3e,0xc34);
        }
      } while ((*(uint *)(0x41008000 + 0x550) & 0xf7) == 4);
      *(undefined4 *)(0x41008000 + 0x110) = 0;
      *(undefined4 *)(iVar8 + 0x180) = 0x100;
    }
    return;
#endif
  default:
    FUN_01008d00(0x30,0xf1);
    sVar7 = 0;
    if (FUN_01025be0() != 0) {
      sVar7 = (short)(ushort)(sVar7 + 0xf);
    }
    goto LAB_01012cf8;
  case 6:
    FUN_010127f8(param_1);
    return;
  case 7:
    FUN_01022ebc(param_1[0x100]);
    param_1[0x120] = 0;
    return;
  case 8:
    FUN_01008d00(0x30,0xed);
  }
  iVar8 = FUN_010126e8();
  if (iVar8 == 0) {
    sVar7 = 0x8b;
  }
  else {
    iVar8 = FUN_010126b0(param_1);
    if ((iVar8 == 0) && (iVar8 = FUN_010126b8(param_1), iVar8 == 0)) {
      sVar17 = 0x7f;
      sVar7 = 0x75;
    }
    else {
      sVar17 = 0x89;
      sVar7 = 0x7f;
    }
    FUN_01021908((int)&uStack_24 + 2);
    cVar6 = *((char *)&uStack_24 + 2);
    FUN_01021914((int)&uStack_24 + 3);
    /* Both callees populate these status bytes in production.  In the parity
       oracle calls are opaque, so retain the nonzero-status continuation. */
    (void)cVar6;
    (void)*((char *)&uStack_24 + 3);
    sVar7 = sVar17;
    iVar8 = FUN_01025d28();
    if (iVar8 == 0) {
      iVar8 = FUN_01025be0();
      if (iVar8 != 0) {
        sVar7 = sVar7 + 0xf;
      }
    }
    else {
      sVar7 = sVar7 + 0x18;
    }
  }
LAB_01012cf8:
  uVar4 = *(ushort *)(param_1 + 0x122);
  *(volatile short *)(param_1 + 0x130) = sVar7;
  *(volatile byte *)(param_1 + 0x128) = 0;
  *(volatile byte *)(param_1 + 0x133) = 1;
  if (uVar4 < 9) {
    *(ushort *)(param_1 + 0x122) = uVar4 + 1;
    if ((*(int *)(param_1 + 0x104) == 0) || (uVar4 != 8)) goto LAB_01012d26;
LAB_01012ebc:
    uVar13 = 1;
  }
  else {
    if (*(int *)(param_1 + 0x104) != 0) goto LAB_01012ebc;
LAB_01012d26:
    uVar13 = 2;
  }
  param_1[0x132] = uVar13;
  lVar18 = thunk_FUN_01025034();
  uVar14 = *(uint *)(param_1 + 0x138);
  iVar8 = *(int *)(param_1 + 0x13c);
  sVar7 = FUN_010246d8();
  uVar15 = FUN_01022ea8();
  uVar4 = *(ushort *)(param_1 + 0x130);
  if (uVar4 < uVar15) {
    uVar4 = (ushort)uVar15;
  }
  uVar15 = (uint)(ushort)(sVar7 + 0xe7 + uVar4);
  if ((int)((iVar8 - (int)((ulonglong)lVar18 >> 0x20)) - (uint)(uVar14 < (uint)lVar18)) <
      (int)(uint)(uVar14 - (uint)lVar18 < uVar15)) {
    *(ulonglong *)(param_1 + 0x138) = lVar18 + (ulonglong)uVar15;
  }
  FUN_0100d4d0(param_1 + 0x128,0);
  if (param_1[0x148] == '\0') {
    if (*(int *)(param_1 + 0x144) != 0x7fffffff || *(int *)(param_1 + 0x140) != -1) {
      uVar16 = *(uint *)(param_1 + 0x138);
      iVar8 = *(int *)(param_1 + 0x13c);
      uVar19 = FUN_010122b4(param_1,0);
      uVar15 = (int)uVar19 + 0x152;
      uVar14 = *(uint *)(param_1 + 0x140) - uVar16;
      iVar8 = ((*(int *)(param_1 + 0x144) - iVar8) - (uint)(*(uint *)(param_1 + 0x140) < uVar16)) -
              (uint)(uVar14 < uVar15);
      if (iVar8 < 0) {
        FUN_010128bc(param_1,(int)((ulonglong)uVar19 >> 0x20),iVar8,uVar14 - uVar15);
        goto LAB_01012ea2;
      }
    }
    iVar8 = FUN_010231c8(param_1[0x100],param_1 + 0x128);
    if (iVar8 == 0) {
      FUN_01008d00(0x30,0x6df);
    }
  }
  else {
LAB_01012ea2:
    FUN_01022ebc(param_1[0x100]);
    param_1[0x120] = 0;
  }
  uVar15 = *(uint *)(param_1 + 0x138);
  uVar16 = *(uint *)(param_1 + 0x13c);
  uVar14 = *(uint *)(param_1 + 0x11c);
  if ((uVar14 <= uVar16 && (uint)(uVar15 <= *(uint *)(param_1 + 0x118)) <= uVar14 - uVar16) &&
     (uVar15 = FUN_0101232c(param_1,uVar15,uVar14,
                            (uVar14 - uVar16) - (uint)(uVar15 > *(uint *)(param_1 + 0x118))),
     uVar15 != 0)) {
    *(ulonglong *)(param_1 + 0x118) =
         (ulonglong)uVar15 *
         ((ulonglong)(uint)(*(int *)(param_1 + 0x138) - (int)*(longlong *)(param_1 + 0x118)) /
         (ulonglong)uVar15) + *(longlong *)(param_1 + 0x118);
  }
  return;
}
