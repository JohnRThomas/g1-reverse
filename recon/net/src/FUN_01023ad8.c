/* net-core FUN_01023ad8 @ 0x1023ad8  (parity 200 trials PROVEN) */
/* net-core FUN_01023ad8 @ 0x1023ad8  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef short i16;
typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;
typedef long long i64;

extern void FUN_01021b04(void);
extern void FUN_0102460c(void);
extern u32  FUN_01024664(void);
extern void FUN_010246e4(void);
extern void FUN_01024ad0_v(void); /* placeholder unused */
extern u32  FUN_01024ad0(void);
extern void FUN_01024e1c(u32,u32);
extern u64  FUN_01025084(void);
extern u32  FUN_010250d0(u32);
extern void FUN_010256dc(u32,u32);
extern void g1_fatal_physical_fallthrough(void);

#define DAT_01023cfc 0x210016f0u
#define CARRY4(a,b) ((u32)(a) > (0xFFFFFFFFu - (u32)(b)))

void FUN_01023ad8(u32 param_1)
{
  u8 bVar1;
  i32 iVar2;
  u32 uVar3;
  i32 iVar4;
  u32 uVar5;
  u32 uVar6;
  u64 uVar7;

  iVar2 = (i32)DAT_01023cfc;
  switch (param_1) {
  case 0:
    if (*(volatile i32*)(iVar2 + 0x44) == -1 && *(volatile i32*)(iVar2 + 0x40) == -1) {
      FUN_010246e4();
      uVar7 = FUN_01025084();
      *(volatile u64*)(iVar2 + 0x40) = uVar7;
    }
    if ((*(volatile i16*)(iVar2 + 0x1e) != 0)) {
      iVar4 = (i32)FUN_01024ad0();
      if (iVar4 == 0) {
        FUN_010256dc(0x70, 0x850);
      }
    }
    if (*(volatile i8*)(iVar2 + 0x4a) == 0x20) {
      FUN_01021b04();
    }
    *(volatile u8*)(iVar2 + 0x37) = 0xff;
    if ((*(volatile i32*)(iVar2 + 0xc) != -1 || *(volatile i32*)(iVar2 + 8) != -1)) {
      iVar4 = (i32)FUN_010250d0(5);
      if (iVar4 == 0) {
        goto fatal_858;
      }
    }
    if (*(volatile i8*)(iVar2 + 0x21) == 1) {
      uVar6 = *(volatile u32*)(iVar2 + 0x10) - 1;
      FUN_01024e1c(uVar6 + *(volatile u32*)(iVar2 + 0x18),
                   *(volatile i32*)(iVar2 + 0x14) - 1 + (u32)(*(volatile i32*)(iVar2 + 0x10) != 0) +
                   CARRY4(uVar6, *(volatile u32*)(iVar2 + 0x18)));
    }
    {
      u8 idx0 = *(volatile u8*)(iVar2 + 0x4a);
      u32 arg0 = *(volatile u32*)(iVar2 + (u32)idx0 * 0x20 + 0xd4);
      void (*fp)(u32,u32) = (void(*)(u32,u32))(u32)(*(volatile u32*)(iVar2 + (u32)idx0 * 0x20 + 0xd0));
      fp(arg0, 1);
    }
    return;
  case 1:
    if (*(volatile i8*)(DAT_01023cfc + 0x4a) == 0x20) {
      FUN_01021b04();
    }
    *(volatile u8*)(iVar2 + 0x36) = 1;
    iVar4 = (i32)FUN_01024ad0();
    if (iVar4 != 0) {
      if (*(volatile i32*)(iVar2 + 0x44) == -1 && *(volatile i32*)(iVar2 + 0x40) == -1) {
        FUN_010246e4();
        uVar7 = FUN_01025084();
        *(volatile u64*)(iVar2 + 0x40) = uVar7;
      }
      {
        u8 idx1 = *(volatile u8*)(iVar2 + 0x4a);
        u32 arg1 = *(volatile u32*)(iVar2 + (u32)idx1 * 0x20 + 0xd4);
        void (*fp)(u32,u32) = (void(*)(u32,u32))(u32)(*(volatile u32*)(iVar2 + (u32)idx1 * 0x20 + 0xd0));
        fp(arg1, 0);
      }
      return;
    }
    goto fatal_889;
  case 2:
    FUN_0102460c();
    if ((*(volatile i16*)(iVar2 + 0x1e) != 0)) {
      iVar4 = (i32)FUN_01024ad0();
      if (iVar4 == 0) {
        goto fatal_894;
      }
    }
    iVar4 = (i32)FUN_01024664();
    if (iVar4 != 0) {
      *(volatile u8*)(iVar2 + 0x29) = 1;
    }
    break;
  case 3:
    **(volatile u32**)(DAT_01023cfc + 0x4d4) = 1;
    break;
  case 5:
    if (*(volatile i8*)(DAT_01023cfc + 0x48) == 0) {
      if (*(volatile i8*)(DAT_01023cfc + 0x4a) == 0x20) {
        FUN_01021b04();
      }
      *(volatile u32*)(iVar2 + 8) = 0xffffffffu;
      *(volatile u32*)(iVar2 + 0xc) = 0xffffffffu;
      if (*(volatile i8*)(iVar2 + 0x37) == 0) {
        goto fatal_871;
      }
      bVar1 = *(volatile u8*)(iVar2 + 0x4a);
      uVar5 = 6;
      uVar3 = *(volatile u32*)(iVar2 + (u32)(*(volatile u8*)(iVar2 + 0x4a)) * 0x20 + 0xd4);
      goto LAB_01023b1c;
    }
    if (*(volatile i32*)(DAT_01023cfc + 0x44) == -1 && *(volatile i32*)(DAT_01023cfc + 0x40) == -1) {
      FUN_010246e4();
      uVar7 = FUN_01025084();
      *(volatile u64*)(iVar2 + 0x40) = uVar7;
    }
    *(volatile u8*)(iVar2 + 0x48) = 0;
    break;
  case 6:
    if (*(volatile i8*)(DAT_01023cfc + 0x4a) == 0x20) {
      FUN_01021b04();
    }
    bVar1 = *(volatile u8*)(iVar2 + 0x4a);
    uVar5 = 5;
    uVar3 = *(volatile u32*)(iVar2 + (u32)(*(volatile u8*)(iVar2 + 0x4a)) * 0x20 + 0xd4);
LAB_01023b1c:
    {
      void (*fp)(u32,u32) = (void(*)(u32,u32))(u32)(*(volatile u32*)(iVar2 + (u32)bVar1 * 0x20 + 0xd0));
      fp(uVar3, uVar5);
    }
    return;
  default:
    break;
  }
  return;

fatal_889:
  FUN_010256dc(0x70, 0x889);
fatal_858:
  FUN_010256dc(0x70, 0x858);
fatal_871:
  FUN_010256dc(0x70, 0x871);
fatal_894:
  FUN_010256dc(0x70, 0x894);
  for (;;) {
    g1_fatal_physical_fallthrough();
  }
}

