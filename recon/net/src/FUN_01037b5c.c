/* net-core FUN_01037b5c @ 0x1037b5c  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;
typedef long long i64;

extern void FUN_0102ec10(u32);
extern i32  FUN_0103610c(u32);
extern i32  FUN_01036128(u32);
extern void FUN_01036144(u32);
extern void FUN_010374dc(void);
extern void FUN_01037a60(void);
extern void FUN_01037f8c(i32,u32,u32,u32);
extern u32  FUN_01039bb0(u32,u32);
extern void FUN_01039bbe(u32,u32,u32);
extern u32  FUN_0103b2f8(u32,u32,u32);

#define DAT_01037c48 0x0103eb0eu
#define DAT_01037c4c 0x0103d2a7u
#define DAT_01037c50 0x21004b68u
#define DAT_01037c54 0x0103d3b6u
#define DAT_01037c58 0x21004b28u
#define DAT_01037c5c 0x21004b5cu
#define DAT_01037c60 0x0103bac9u

i32 FUN_01037b5c(u32 param_1, i32 param_2)
{
  u32 r0v, r1v;
  i32 r4;
  u32 r8v;

  {
    u32 ipsr = __get_IPSR();
    if (ipsr != 0) {
      FUN_01039bbe(DAT_01037c4c, DAT_01037c48, 0x596);
      r1v = 0x596;
      r0v = DAT_01037c48;
      goto FINAL_CALL;
    }
  }
  if ((param_1 | (u32)param_2) == 0) {
    FUN_01037a60();
    return 0;
  }
  {
    i64 combined = (((i64)param_2) << 32 | (u32)param_1) + 2;
    if (combined < 0) {
      r4 = (i32)(0xFFFFFFFEu - param_1);
    } else {
      i32 iVar2 = (i32)FUN_0103b2f8(param_1, (u32)param_2, param_1 + 2);
      r4 = (i32)(param_1 + (u32)iVar2);
    }
  }

COMMON: ;
  {
    u32 oldpri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    r8v = oldpri;
  }
  {
    i32 res = FUN_0103610c(DAT_01037c50);
    if (res == 0) {
      u32 rv;
      FUN_01039bbe(DAT_01037c4c, DAT_01037c54, 0x72);
      r1v = 0x72;
      r0v = DAT_01037c54;
FINAL_CALL:
      rv = FUN_01039bb0(r0v, r1v);
      r4 = (i32)(0xFFFFFFFEu - rv);
      goto COMMON;
    }
  }
  {
    i32 iVar2addr = DAT_01037c58;
    i32 iVar3;
    FUN_01036144(DAT_01037c50);
    *(volatile u32*)DAT_01037c5c = *(volatile u32*)((u32)iVar2addr + 8);
    FUN_010374dc();
    FUN_01037f8c(*(volatile i32*)((u32)iVar2addr + 8) + 0x18, DAT_01037c60, param_1, (u32)param_2);
    {
      u32 uVar5 = DAT_01037c50;
      *(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd) =
        *(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd) | 0x10;
      iVar3 = FUN_01036128(uVar5);
      if (iVar3 == 0) {
        u32 rv;
        FUN_01039bbe(DAT_01037c4c, DAT_01037c54, 0x111);
        r1v = 0x111;
        r0v = DAT_01037c54;
        rv = FUN_01039bb0(r0v, r1v);
        r4 = (i32)(0xFFFFFFFEu - rv);
        goto COMMON;
      } else {
        FUN_0102ec10(r8v);
        if ((i32)(((u32)(*(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd))) << 0x1b) >= 0) {
          u32 uVar4 = FUN_0103b2f8(0, 0, 0);
          if ((u32)r4 < uVar4) {
            return 0;
          }
          return r4 - (i32)uVar4;
        }
        {
          u32 rv;
          FUN_01039bbe(DAT_01037c4c, DAT_01037c48, 0x5b2);
          r1v = 0x5b2;
          r0v = DAT_01037c48;
          rv = FUN_01039bb0(r0v, r1v);
          r4 = (i32)(0xFFFFFFFEu - rv);
          goto COMMON;
        }
      }
    }
  }
}
