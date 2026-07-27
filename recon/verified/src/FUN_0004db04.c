/* Reconstructed FUN_0004db04 @ 0x4db04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int FUN_0004da6c(unsigned,...);
extern int FUN_0004da90(unsigned,unsigned);
extern int FUN_0007db9e(unsigned,unsigned,unsigned,int);
extern int FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_0007ee44(void);
extern int FUN_0007eece(unsigned);
#define U8(a)  (*(volatile uint8_t*)(uintptr_t)(a))
#define U32(a) (*(volatile uint32_t*)(uintptr_t)(a))

void FUN_0004db04(uint param_1,uint param_2,int param_3,int param_4,uint param_5,
                  unsigned char param_6,int param_7,unsigned char *param_8,uint param_9,uint param_10)
{
  uint uVar1=0, uVar6;
  int iVar2, iVar3, iVar5;
  uint uVar4, uVar7, uVar8, uVar9, uVar10, local_3c;
  unsigned char *local_38;

  uVar8 = (uint)param_6;
  local_38 = param_8;
  local_3c = param_9;
  if (uVar8 == 0) {
    uVar6 = 0x0007eee9;
    if (param_4 == 1) uVar6 = 0x0004daad;
    if (param_7 == 0) {
      if (param_9 != 0) {
        iVar2 = 0;
        uVar6 = 0x000a7993;
        uVar1 = 0x000f7b6f;
        goto LAB_dcaa;
      }
      goto LAB_dd7a;
    }
    iVar2 = 0;
LAB_dc74:
    iVar3 = FUN_0007db9e(uVar6,0x0007eec1,param_1,param_7);
    if (iVar3 < 0) {
      FUN_0007e2fa(0x00099cbd,0x000f0f1b,0x000f0e73,0x219);
      uVar6 = 0x219;
LAB_db3e:
      FUN_0007e2ec(0x000f0e73,uVar6);
    }
    uVar6 = 0x000a7993;
    uVar1 = 0x000f7b6f;
    if (param_9 != 0) {
LAB_dcaa:
      uVar4 = local_3c;
      if (0xf < local_3c) uVar4 = 0x10;
      FUN_0004da90(param_1,param_10);
      for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
        FUN_0004da6c(param_1,uVar1);
      }
      FUN_0004da6c(param_1,uVar6,*local_38);
      uVar9 = 1;
      do {
        if ((uVar9 & 7) == 0) FUN_0004da6c(param_1,uVar1);
        if (uVar9 < uVar4) FUN_0004da6c(param_1,uVar6,local_38[uVar9]);
        else FUN_0004da6c(param_1,0x000f7b6d);
        uVar9 = uVar9 + 1;
      } while (uVar9 != 0x10);
      uVar9 = 0;
      FUN_0004da6c(param_1,0x000f0f24);
      do {
        uVar7 = (uint)(unsigned char)local_38[uVar9];
        if ((U8(0x000f8a6b + uVar7) & 0x97) == 0) uVar7 = 0x2e;
        FUN_0004da6c(param_1,0x000f0f26,uVar7);
        while (1) {
          uVar9 = uVar9 + 1;
          if (uVar9 == 0x10) {
            local_38 = local_38 + uVar4;
            local_3c = local_3c - uVar4;
            if (local_3c != 0) goto LAB_dcaa;
            goto LAB_dd74;
          }
          if ((uVar9 & 7) == 0) FUN_0004da6c(param_1,uVar1);
          if (uVar9 < uVar4) break;
          FUN_0004da6c(param_1,uVar1);
        }
      } while (1);
    }
LAB_dd74:
    if (uVar8 == 0) goto LAB_dd7a;
  } else {
    if (4 < uVar8) {
      FUN_0007e2fa(0x00099cbd,0x000f0ed7,0x000f0e73,0x1bf);
      uVar6 = 0x1bf;
      goto LAB_db3e;
    }
    iVar2 = FUN_0007ee44();
    if (iVar2 == 0) iVar3 = 0;
    else iVar3 = FUN_0004da6c(param_1,0x000f0ee3,iVar2);
    if ((param_10 & 2) != 0) {
      if ((param_10 & 0x44) == 0) {
        uVar4 = FUN_0004da6c(param_1,0x000f0ee7,param_2);
      } else {
        uVar4 = U32(0x2000a0e4);
        if (uVar4 != 0) {
          uVar9 = (param_2 / U32(0x2000a0e0)) / uVar4;
          uVar7 = (param_2 / U32(0x2000a0e0) - uVar4 * uVar9) * 1000;
          uVar10 = uVar7 / uVar4;
          uVar4 = FUN_0004da6c(param_1,0x000f0ef0,uVar9/0xe10,(uVar9%0xe10)/0x3c,
                               (uVar9%0xe10)%0x3c,uVar10,((uVar7 - uVar4*uVar10)*1000)/uVar4);
        }
      }
      iVar3 = iVar3 + uVar4;
    }
    if ((param_10 & 1) != 0) {
      iVar2 = U32(0x0008acc4 + uVar8*4);
      if (iVar2 == 0) iVar2 = 0x000f0ed2;
      FUN_0004da6c(param_1,0x000a8c37,iVar2);
    }
    if ((param_10 & 8) == 0) iVar2 = 0;
    else iVar2 = FUN_0004da6c(param_1,0x000f0f0c,U32(0x0008acd8 + uVar8*4));
    if (param_3 != 0) {
      iVar5 = FUN_0004da6c(param_1,0x000f0f12,param_3);
      iVar2 = iVar2 + iVar5;
    }
    if (param_4 != 0) {
      iVar5 = FUN_0004da6c(param_1,0x000f0f16,param_4);
      iVar2 = iVar2 + iVar5;
    }
    iVar2 = iVar2 + iVar3;
    uVar6 = 0x0004daad;
    if (param_7 != 0) goto LAB_dc74;
    uVar6 = 0x000a7993;
    uVar1 = 0x000f7b6f;
    if (param_9 != 0) goto LAB_dcaa;
  }
  if ((int)(param_10 << 0x1f) < 0) {
    FUN_0004da6c(param_1,0x000a8c37,0x000f0ed2);
  }
  FUN_0004da90(param_1,param_10);
LAB_dd7a:
  FUN_0007eece(param_1);
  return;
}

