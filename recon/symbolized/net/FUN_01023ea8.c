#include "g1_net_symbols.h"
/* net-core FUN_01023ea8 @ 0x1023ea8  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short i16;
typedef unsigned int u32;
typedef int i32;

extern void FUN_010244cc(u32, void *, void *);
extern i32 FUN_010246d8(void);
extern void FUN_01024e1c(u32, u32);
extern void FUN_0102524c(u32);
extern void FUN_010256dc(u32, u32);
extern void FUN_0102583c(u8);

#define DAT_01024114 ((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/
#define DAT_01024118 0x0f423f8au

static inline int CARRY4(u32 a, u32 b) {
  u32 r;
  return __builtin_add_overflow(a, b, &r);
}

#define BASE ((volatile u8 *)DAT_01024114)
#define B(off) (*(volatile u8 *)(BASE + (off)))
#define H(off) (*(volatile u16 *)(BASE + (off)))
#define I(off) (*(volatile i32 *)(BASE + (off)))

u32 FUN_01023ea8(int param_1, u32 param_2)
{
  u8 bVar1, bVar2, bVar3, bVar6;
  u32 uVar5, uVar9, uVar11, uVar12, uVar13, uVar14;
  i32 iVar7, iVar8, iVar10;
  i32 local_2c[2];
  u8 uStack_2d;

  if (B(0x4a) == ' ') {
    FUN_010256dc(0x70, 0xbb3);
    __builtin_unreachable();
  }
  bVar6 = B(0x4a);
  uVar12 = B(0x30 + (u32)B(0x49) * 3);
  iVar7 = I(0x10);
  iVar8 = I(0x18);
  FUN_010244cc((u32)(I(0) + param_1), local_2c, &uStack_2d);
  if ((u32)(param_1 - 0x76) <= DAT_01024118) {
    uVar9 = (u32)I(0x10);
    iVar10 = I(0x14);
    uVar5 = (u32)(local_2c[0] + I((u32)bVar6 * 32 + 0xd8) + I((u32)bVar6 * 32 + 0xe0)) - uVar9;
    if ((uVar5 & 0xffffff) < 0x800001u) {
      bVar6 = B(0x49);
      I(0x18) = (i32)uVar5;
      B(0x20) = (u8)param_2;
      if (uVar12 != 0x20) {
        uVar14 = 0x20;
        for (;;) {
          uVar13 = uVar12;
          uVar11 = (u32)iVar10 + (u32)CARRY4(uVar5, uVar9);
          uVar12 = (u32)I(uVar13 * 32 + 0xd8);
          if ((uVar11 < (u32)I(uVar13 * 32 + 0xdc)) ||
              (((u32)I(uVar13 * 32 + 0xdc) - uVar11) < (u32)(uVar5 + uVar9 <= uVar12))) {
            if ((H(uVar13 * 32 + 0xe6) != 0) && (H(0x1e) == 0)) {
              iVar10 = FUN_010246d8();
              if (iVar10 == 0x356) {
                iVar10 = 0x1d;
              } else if (iVar10 == 0x5f5) {
                iVar10 = 0x33;
              } else if (iVar10 == 0x18c) {
                iVar10 = 0xe;
              } else {
                iVar10 = 1;
              }
              if ((i32)(uVar12 - uVar9) < iVar10) {
                param_2 = (u32)B(0x20);
                goto LAB_01023ffa;
              }
            }
            FUN_0102524c(5);
            uVar12 = (u32)B(0x49);
            I(8) = -1;
            I(0xc) = -1;
            if (uVar14 != 0x20) goto LAB_0102405c;
            goto LAB_01023f78;
          }
LAB_01023ffa:
          if (B(uVar13 * 32 + 0xe8) <= param_2) {
            I(0x18) = (iVar8 + iVar7) - I(0x10);
            return 2;
          }
          uVar12 = (u32)B((uVar13 + (u32)bVar6 * 0x20) * 2 + 0x51);
          uVar14 = uVar13;
          if (uVar12 == 0x20) goto LAB_01024044;
          uVar9 = (u32)I(0x10);
          iVar10 = I(0x14);
          uVar5 = (u32)I(0x18);
        }
      }
      FUN_0102524c(5);
      I(8) = -1;
      I(0xc) = -1;
      uVar12 = (u32)B(0x49);
LAB_01023f78:
      uVar14 = 0x20;
      bVar6 = B(uVar12 * 3 + 0x30);
      goto LAB_01023f84;
    }
  }
  return 1;

LAB_01024044:
  FUN_0102524c(5);
  uVar12 = (u32)B(0x49);
  I(8) = -1;
  I(0xc) = -1;
LAB_0102405c:
  bVar1 = B(uVar12 * 3 + 0x30);
  iVar7 = (i32)(uVar12 * 0x20);
  B(uVar12 * 3 + 0x30) = B((uVar14 + uVar12 * 0x20) * 2 + 0x51);
  bVar6 = bVar1;
  do {
    bVar2 = bVar6;
    uVar5 = (u32)bVar2;
    bVar6 = B(((u32)iVar7 + uVar5) * 2 + 0x51);
    B(((u32)iVar7 + uVar5) * 2 + 0x50) = 5;
  } while (uVar14 != uVar5);
  bVar3 = B(uVar12 * 3 + 0x32);
  if (bVar3 == 0x20) {
    B(uVar12 * 3 + 0x31) = bVar1;
  } else {
    B(((u32)bVar3 + (u32)iVar7) * 2 + 0x51) = bVar1;
  }
  B((uVar5 + (u32)iVar7) * 2 + 0x51) = 0x20;
  B(uVar12 * 3 + 0x32) = bVar2;
LAB_01023f84:
  B(((u32)B(0x4a) + (u32)B(0x49) * 0x20) * 2 + 0x51) = bVar6;
  I(0) = I(0) + param_1;
  B(0x39) = 0xff;
  if ((B(0x37) != 0) && (B(0x21) == 1)) {
    u32 uVar12b = (u32)I(0x10) - 1;
    FUN_01024e1c(uVar12b + (u32)I(0x18),
                 (u32)I(0x14) - 1 + (u32)(I(0x10) != 0) + (u32)CARRY4(uVar12b, (u32)I(0x18)));
  }
  if (uVar14 != 0x20) {
    FUN_0102583c(B(0x4d9));
    return 0;
  }
  return 0;
}
