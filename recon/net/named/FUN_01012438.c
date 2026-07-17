/* readable reconstruction; identity: FUN_01012438 @ 0x01012438
 * public-name: FUN_01012438
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c1bc                           @ 0x0103c1bc
 */
/* net-core FUN_01012438 @ 0x1012438  (parity 200 trials PROVEN) */
/* net-core FUN_01012438 @ 0x1012438  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef int i32;

extern void FUN_01008d00(u32, u32);
extern u32 FUN_0100a4d0(void);
extern u32 FUN_01010990(u32, i8);
extern i32 FUN_010109ec(u32, u32, i8, int, u32);
extern int FUN_01011d14(u32, void *);
extern void FUN_010129a4(void *);
extern void FUN_010129b4(void *, u8);
extern void FUN_010129b8(void *, i8, u8);
extern u32 FUN_01012b24(void *);
extern i32 FUN_01012b50(u32, u32, int);
extern u32 FUN_010280be(u32);
extern u32 FUN_010280d8(u32);

#define DAT_0101263c 0x0103c1bcu
#define DAT_01012640 0xd1b71759ull

static inline u32 read_u24(volatile u8 *p) {
  return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16);
}

u32 FUN_01012438(u32 *param_1, u8 *param_2)
{
  u8 *pb1 = (u8 *)param_1;
  i8 cVar12, cVar9, cVar13;
  u32 local_50, local_4c, local_48, local_44, local_40;
  u32 uStack_3c, uStack_38, uStack_34, local_30, uStack_2c;
  u8 uVar1, bVar2, uVar4, uVar3;
  u32 uVar10, uVar11, uVar6, uVar5;
  i32 iVar7;
  u32 uVar14;
  u32 uVar8;
  u8 local_68[6];

  cVar12 = (i8)pb1[5];
  cVar9 = (i8)pb1[0xe];
  local_50 = param_1[0];
  local_4c = param_1[1];
  local_48 = param_1[2];
  local_44 = param_1[3];
  local_40 = param_1[4];
  uStack_3c = param_1[5];
  uStack_38 = param_1[6];
  uStack_34 = param_1[7];
  local_30 = param_1[8];
  uStack_2c = param_1[9];
  (void)local_48;

  FUN_010129a4(local_68);

  uVar1 = param_2[0];
  bVar2 = param_2[1];
  uVar4 = param_2[10];
  uVar10 = (u32)((u8)(param_2[0x14] - 1));
  if (uVar10 < 3) {
    volatile u8 *tbl = (volatile u8 *)(DAT_0101263c + 0x14);
    uVar11 = bVar2 & 0x7f;
    cVar13 = (i8)tbl[uVar10];
    if ((int)((u32)bVar2 << 0x1b) >= 0) {
      uVar10 = (u32)((u8)(param_2[0x16] - 1));
      if (uVar10 > 2) {
        FUN_01008d00(6, 0x2a6);
        __builtin_unreachable();
      }
      cVar12 = (i8)tbl[uVar10];
    }
    if (cVar9 == 1) {
      if (cVar13 == 8) cVar13 = 4;
      if (cVar12 == 8) cVar12 = 4;
    }
    FUN_010129b4(local_68, param_2[9]);
    if (param_2[0x14] == 2) {
      cVar9 = (i8)(param_2[0x15] + 1);
    } else {
      cVar9 = 1;
    }
    FUN_010129b8(local_68, cVar9, (u8)(param_2[0x1a] + 1));
    if ((int)(uVar11 << 0x1c) < 0) {
      uVar10 = 0;
    } else {
      uVar14 = FUN_01012b24(local_68);
      if ((int)((u32)bVar2 << 0x1b) < 0) {
        iVar7 = FUN_01012b50(uVar14, uVar11, 0x28);
      } else {
        uVar8 = FUN_0100a4d0();
        uVar14 = FUN_01010990(uVar14, cVar13);
        iVar7 = FUN_010109ec(uVar8, uVar14, cVar12, 1, uVar11);
      }
      uVar6 = (u32)((DAT_01012640 * (u64)(u32)(iVar7 + 0x2f1)) >> 0x29) * 0x271u;
      uVar10 = read_u24((volatile u8 *)(param_2 + 3)) * 0x271u;
      if ((uVar10 <= uVar6) && (uVar6 - uVar10 != 0)) {
        uVar10 = read_u24((volatile u8 *)(param_2 + 6)) * 0x271u;
        if (uVar6 <= uVar10) {
          uVar10 = uVar6;
        }
      }
    }
    cVar9 = (i8)param_2[0x18];
    uVar3 = param_2[0x12];
    uVar5 = FUN_010280be(param_1[0x11]);
    uVar6 = FUN_010280d8(param_1[0x11]);
    if (uVar6 < uVar5) {
      uVar6 = uVar5;
    }
    {
      int take_slow = 0;
      if (((uVar6 & 0xffff) == 0) || ((bVar2 & 0x18) != 0)) {
        take_slow = 1;
      } else {
        iVar7 = FUN_01011d14(uVar6 & 0xffff, local_68);
        if (iVar7 != 0) take_slow = 1;
      }
      if (take_slow) {
        u32 new_local_50, new_local_4c, new_local_44, new_local_40;
        u32 local68 = *(u32 *)local_68;
        u16 uStack_64 = *(u16 *)(local_68 + 4);

        new_local_50 = (local_50 & 0xff00u) | (u32)uVar1 | ((u32)(u16)uVar11 << 16);
        new_local_4c = (local_4c & 0xffff0000u) | (u32)(u8)cVar13 | ((u32)(u8)cVar12 << 8);
        new_local_44 = (local_44 & 0xffffff00u) | (u32)(cVar9 == 1);
        new_local_40 = (local_40 & 0xff0000ffu) | ((u32)uVar3 << 8) | ((u32)uVar4 << 16);

        uVar14 = 0;
        *(volatile u32 *)(pb1 + 0) = new_local_50;
        *(volatile u32 *)(pb1 + 4) = new_local_4c;
        *(volatile u32 *)(pb1 + 8) = uVar10;
        *(volatile u32 *)(pb1 + 12) = new_local_44;
        *(volatile u32 *)(pb1 + 16) = new_local_40;
        *(volatile u32 *)(pb1 + 20) = uStack_3c;
        *(volatile u32 *)(pb1 + 24) = uStack_38;
        *(volatile u32 *)(pb1 + 28) = uStack_34;
        *(volatile u32 *)(pb1 + 32) = local_30;
        *(volatile u32 *)(pb1 + 36) = uStack_2c;
        *(volatile u32 *)(pb1 + 40) = local68;
        *(volatile u16 *)(param_1 + 0xb) = uStack_64;
        *(volatile u8 *)((u8 *)param_1 + 0x67) = (u8)((param_2[0xb] & 0xfd) != 0);
        param_1[0x1a] = *(volatile u32 *)(param_2 + 0xc);
        *(volatile u16 *)((u8 *)param_1 + 0x6c) = *(volatile u16 *)(param_2 + 0x10);
        *((volatile u8 *)param_1 + 0x3e) =
            (u8)((*((volatile u8 *)param_1 + 0x3e) & 0xf) | ((param_2[0x17] & 0xf) << 4));
      } else {
        uVar14 = 0x45;
      }
    }
    return uVar14;
  }
  FUN_01008d00(6, 0x2a6);
  __builtin_unreachable();
}
