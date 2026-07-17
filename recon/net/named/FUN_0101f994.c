/* readable reconstruction; identity: FUN_0101f994 @ 0x0101f994
 * public-name: FUN_0101f994
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   rodata_10100a1                           @ 0x010100a1
 */
/* net-core FUN_0101f994 @ 0x101f994  (parity 200 trials PROVEN) */
/* net-core FUN_0101f994 @ 0x101f994  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef short i16;
typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;
typedef long long i64;

extern void sdc_assertion_fail(u32,u32);
extern u32  FUN_0100e8b0(i32);
extern u32  FUN_0100e8b8(i32);
extern u16  FUN_0100e8c4(i32);
extern i32  FUN_0100e8c8(i32);
extern void FUN_0100ef88(i32,u32,u32);
extern void FUN_0100f7b0(i32);
extern u32  FUN_0100f834(i32,i32);
extern void FUN_0101f934(i32,u32,u32,i32,i32);
extern u64  FUN_0102971e(u32,u32);
extern i32  FUN_010297b4(i32,i32,void*);
extern i32  FUN_01029882(u16,u8,i32,u16);

#define DAT_0101fba0 0x010100a1u

u32 FUN_0101f994(i32 param_1, i32 param_2, u32 param_3)
{
  i8 cVar1;
  u8 bVar2;
  u16 uVar3;
  i32 iVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  u32 uVar8;
  u32 uVar9;
  u8 uVar10;
  u32 uVar11;
  i32 iVar12;
  u8 *puVar13;
  u32 bVar14;
  u64 uVar15;
  u32 local_24;
  u32 uStack_20;

  iVar12 = *(volatile i32*)(param_1 + 4);
  cVar1 = *(volatile i8*)(iVar12 + 0xc5);
  if (*(volatile u8*)(iVar12 + 0xc6) == 0x24) {
    puVar13 = (u8*)(iVar12 + 0xc6);
    goto CALL_E8C8;
  }
ELSE_BR:
  if (cVar1 != 0x22) {
    return 2;
  }
  puVar13 = (u8*)(iVar12 + 0xc5);
CALL_E8C8:
  iVar12 = param_1;
  local_24 = (u32)param_2;
  uStack_20 = param_3;
  iVar4 = FUN_0100e8c8(param_2);
  if (iVar4 == 0) {
LAB_0101fa52:
    iVar4 = *(volatile i32*)(param_1 + 4);
    if (*(volatile i8*)(iVar4 + 0x16c) == 1) {
      FUN_0101f934(param_1, 0x1e, 1, iVar4, iVar12);
    } else {
      *(volatile u8*)(iVar4 + 0x16c) = 0;
    }
    if (cVar1 != 0x22) {
      *puVar13 = 0;
      FUN_0100f7b0(param_1);
      uVar6 = FUN_0100f834(param_1, param_2);
      return uVar6;
    }
    cVar1 = *(volatile i8*)(param_2 + 3);
    iVar12 = *(volatile i32*)(param_1 + 4);
    *(volatile i8*)(iVar12 + 0x149) = cVar1;
    if (cVar1 == 0x18) {
      *(volatile u8*)(iVar12 + 0xc5) = 10;
      if (*(volatile i8*)(iVar12 + 0x100) != 0) {
        return 0;
      }
      uVar9 = 0x275;
    } else {
      uVar9 = 0x26d;
    }
    uVar6 = 0x7e;
    goto TRAP;
  }
  uVar5 = FUN_0100e8b0(param_2);
  uVar6 = FUN_0100e8b8(param_2);
  uVar15 = FUN_0102971e(uVar6, uVar6);
  uVar8 = (u32)(uVar15 >> 0x20);
  uVar7 = (u32)uVar15;
  iVar4 = *(volatile i32*)(param_1 + 4);
  if ((uVar7 != 0) && (uVar11 = (u32)*(volatile u8*)(iVar4 + 0x6e), uVar7 != uVar11)) {
    if (*(volatile i8*)(iVar4 + 0x16c) == 1) {
      bVar2 = *(volatile u8*)(iVar4 + 0x16e);
    } else {
      bVar2 = *(volatile u8*)(iVar4 + 0x6a);
    }
    if ((uVar8 & bVar2) == 0) goto LAB_0101fa52;
    if ((cVar1 != 0x22) && ((uVar8 & *(volatile u8*)(iVar4 + 0x67)) == 0)) {
      if (uVar11 == 0) {
        uVar9 = 0x178;
        uVar6 = 6;
        goto TRAP;
      }
      if ((((uVar11 == 4) || (uVar7 == 4)) || (uVar11 == 8)) || (uVar7 == 8)) {
        bVar14 = (uVar11 < uVar7) ? 1u : 0u;
      } else {
        bVar14 = (uVar7 < uVar11) ? 1u : 0u;
      }
      if (bVar14) goto LAB_0101fa52;
    }
  }
  uVar7 = (u32)FUN_0102971e(uVar5, 0);
  if ((uVar7 != 0) && (*(volatile u8*)(iVar4 + 0x6f) != uVar7)) {
    if (*(volatile i8*)(iVar4 + 0x16c) == 1) {
      bVar2 = *(volatile u8*)(iVar4 + 0x16f);
    } else {
      bVar2 = *(volatile u8*)(iVar4 + 0x6b);
    }
    if ((uVar5 & bVar2) == 0) goto LAB_0101fa52;
  }
  iVar12 = FUN_010297b4(iVar4, param_2, &local_24);
  iVar4 = *(volatile i32*)(param_1 + 4);
  if (iVar12 == 0) {
    if (*(volatile i8*)(iVar4 + 0x16c) == 1) {
      iVar12 = FUN_01029882(*(volatile u16*)(iVar4 + 0x170), *(volatile u8*)(iVar4 + 0x6e),
                             iVar4 + 0x3bc, *(volatile u16*)(iVar4 + 0xbc));
      if (iVar12 == 0) {
        FUN_0101f934(param_1, 0, 0, 0, 0);
        *puVar13 = 0;
      } else {
        *(volatile u8*)(*(volatile i32*)(param_1 + 4) + 0xc5) = 0x28;
      }
    } else {
      *(volatile u8*)(iVar4 + 0x16c) = 0;
    }
    if (puVar13 == (u8*)(*(volatile i32*)(param_1 + 4) + 0xc6)) {
      *(volatile u8*)(*(volatile i32*)(param_1 + 4) + 0xc6) = 0;
    }
  } else {
    uVar3 = FUN_0100e8c4(param_2);
    *(volatile u16*)(iVar4 + 0x3bc) = uVar3;
    iVar12 = *(volatile i32*)(param_1 + 4);
    if ((u16)((*(volatile i16*)(iVar12 + 0x3bc) - 1) - *(volatile i16*)(iVar12 + 0xbc)) < 0x7ffe) {
      if ((*(volatile u8*)(iVar12 + 0xc6) != 0xe) && (1 < (u8)(*(volatile u8*)(iVar12 + 0xc6) - 0xb))) {
        *(volatile u8*)(iVar12 + 0x3be) = (u8)local_24;
        *(volatile u8*)(iVar12 + 0x3bf) = (u8)(local_24 >> 8);
        *puVar13 = 0x26;
        goto LAB_0101fb0c;
      }
      uVar10 = 0x2a;
    } else {
      uVar10 = 0x28;
    }
    *(volatile u8*)(iVar12 + 0xe5) = uVar10;
    FUN_0100ef88(iVar12 + 0xdc, DAT_0101fba0, 2);
  }
LAB_0101fb0c:
  if (puVar13 == (u8*)(*(volatile i32*)(param_1 + 4) + 0xc6)) {
    FUN_0100f7b0(param_1);
  } else {
    *(volatile u8*)(*(volatile i32*)(param_1 + 4) + 0x100) = 0;
  }
  return 0;

TRAP:
  sdc_assertion_fail(uVar6, uVar9);
  goto ELSE_BR;
}
