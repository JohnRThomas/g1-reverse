/* net-core FUN_01021108 @ 0x1021108  (parity 200 trials PROVEN) */
/* net-core FUN_01021108 @ 0x1021108  (parity 300 trials PROVEN) */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#define W32(a) (*(volatile u32*)(u32)(a))
#define W16(a) (*(volatile u16*)(u32)(a))
#define W8(a)  (*(volatile u8*)(u32)(a))
#define S8(a)  (*(volatile signed char*)(u32)(a))

extern void FUN_01008d00(unsigned,unsigned,...);
extern void FUN_01020168(unsigned);
extern void FUN_01020a00(unsigned);
extern void FUN_010215a8(int);
extern void FUN_010216d4(unsigned,unsigned,int,void*);
extern int FUN_010218c0(unsigned,unsigned);
extern int FUN_010218cc(unsigned,unsigned);
extern unsigned FUN_010218fc(void*);
extern unsigned FUN_01023e88(void);
extern unsigned FUN_01025bb0(void*);
extern unsigned FUN_01025bc8(void*);
extern void FUN_01025c9c(void*);

#define IVAR3 0x210015f0u
#define PUVAR4 0x41008000u
#define DAT_010212dc 0x4100c000u
#define DAT_010212e0 0x0103c4d0u
#define DAT_010212e4 0x21000028u
#define DAT_010212e8 0x0103c578u

void FUN_01021108(unsigned param_1, unsigned param_2)
{
  if ((W8(IVAR3+0x35) & 1u) == 0) {
    FUN_01008d00(0x3e,0x716);
    __builtin_unreachable();
  }

  u8 local_2c;
  u8 local_2b;
  u8 local_2d;

  if (param_1 == 0) local_2c = 4; else local_2c = 2;
  u8 local_2a = 0; (void)local_2a;

  u32 uVar7 = FUN_01023e88();
  local_2b = 0xff;
  if (uVar7 > 1) local_2b = 0;

  u32 iVar8 = FUN_01025bb0(&local_2c);
  if (iVar8 != 0) { FUN_01008d00(0x3e,0xa69); __builtin_unreachable(); }

  W8(IVAR3+0x45) = 1;
  W8(IVAR3+0x35) = (u8)(W8(IVAR3+0x35) | 2u);
  W32(PUVAR4+0x200) = W32(PUVAR4+0x200) | 1u;

  if (param_1 == 0) {
    FUN_01020a00(param_2);
    u32 uVar7b = (u32)W8(IVAR3+0x1a);
    int cVar2 = (signed char)W8(IVAR3+0x19);
    W32(PUVAR4+0x508) = (u32)W8(DAT_010212e0 + uVar7b);
    W32(PUVAR4+0x554) = uVar7b & 0x7fu;
    FUN_010216d4(param_2, uVar7b, cVar2, &local_2c);
    FUN_010215a8((int)(signed char)local_2c);
    u32 iVar9 = FUN_010218fc(&local_2b);
    if (iVar9 != 0) { FUN_01008d00(0x3e,0x57e); __builtin_unreachable(); }
    u16 uVar1 = W16(IVAR3+0x1c);
    W32(PUVAR4) = 1;
    W8(IVAR3+9) = 1;
    W32(DAT_010212dc+0x4c) = 1;
    u32 iVar8b = W32(DAT_010212dc+0x54c);
    if (uVar1 > 0x95) {
      W32(DAT_010212e4+8) = iVar8b;
      W32(DAT_010212e4+0xc) = iVar8b + 0x28u;
      int r = FUN_010218c0(DAT_010212e4, DAT_010212e0 + 0xa8u);
      if ((unsigned)(r+1) > 1u) { FUN_01008d00(0x3e,0x6e9); __builtin_unreachable(); }
    }
  } else if (param_1 == 1) {
    FUN_01020168(param_2);
    W32(PUVAR4+4) = 1;
    W8(IVAR3+9) = 2;
    u16 uVar1 = W16(IVAR3+0x1c);
    W32(DAT_010212dc+0x4c) = 1;
    u32 iVar8c = W32(DAT_010212dc+0x54c);
    if (uVar1 > 0x95) {
      W32(DAT_010212e4+8) = iVar8c;
      W32(DAT_010212e4+0xc) = iVar8c + 0x29u;
      int r = FUN_010218cc(DAT_010212e4, DAT_010212e8);
      if ((unsigned)(r+1) > 1u) { FUN_01008d00(0x3e,0x6f6); __builtin_unreachable(); }
    }
  } else {
    u16 uVar1 = W16(IVAR3+0x1c);
    W32(DAT_010212dc+0x4c) = 1;
    u32 r3 = W32(DAT_010212dc+0x54c);
    if (uVar1 > 0x95) {
      FUN_01008d00(0x3e,0x6fa,(unsigned)uVar1,r3);
      __builtin_unreachable();
    }
  }

  local_2b = (u8)(param_1 == 0);
  local_2c = 2;
  FUN_01025c9c(&local_2c);
  u32 iv = FUN_01025bc8(&local_2d);
  if (iv != 0) { FUN_01008d00(0x3e,0xa8b); __builtin_unreachable(); }

  if (W8(IVAR3+9) == 1) {
    int iVar8f = (int)((unsigned)(local_2d ^ 4) << 29);
    S8(IVAR3+0x46) = -(iVar8f >> 31);
    if (-(iVar8f >> 31) != 0) {
      W32(PUVAR4+0x80) = 0;
      W32(PUVAR4+0x84) = 0;
      W32(PUVAR4+0x10) = 1;
    }
  } else if (W8(IVAR3+9) == 2) {
    int iVar8f = (int)((unsigned)(local_2d ^ 2) << 30);
    S8(IVAR3+0x46) = -(iVar8f >> 31);
    if (-(iVar8f >> 31) != 0) {
      W32(PUVAR4+0x80) = 0;
      W32(PUVAR4+0x84) = 0;
      W32(PUVAR4+0x10) = 1;
    }
  } else {
    W8(IVAR3+0x46) = 0;
  }
}


