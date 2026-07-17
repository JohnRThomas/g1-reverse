/* readable reconstruction; identity: FUN_0101b54c @ 0x0101b54c
 * public-name: FUN_0101b54c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_phy_timing_offset_get                <= FUN_0100d58c @ 0x0100d58c
 *   controller_radio_state_get               <= FUN_01019204 @ 0x01019204
 *   schedule_phase_offset_get                <= FUN_0101de10 @ 0x0101de10
 *   schedule_node_list_is_locked             <= FUN_0101dec4 @ 0x0101dec4
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 * address symbols (name @ address):
 *   rodata_103c254                           @ 0x0103c254
 *   g_net_session_state_block                @ 0x210010a0
 *   g_net_session_queue_obj                  @ 0x210010f0
 */
/* net-core FUN_0101b54c @ 0x101b54c  (parity 200 trials PROVEN) */
/* net-core FUN_0101b54c @ 0x101b54c  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef short i16;
typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;
typedef long long i64;

extern void sdc_assertion_fail(u32,u32);
extern u32  sdc_phy_timing_offset_get(u32,u32,u32,u32);
extern u16  FUN_0100d624(u32,i32);
extern u32  FUN_0100d6b0(u32,u32);
extern void FUN_0100f1a8(u32,u32);
extern i32  controller_radio_state_get(void);
extern void FUN_0101bc3c(void);
extern i32  FUN_0101dd9c(u32,i32);
extern u32  schedule_phase_offset_get(u32,i32,u32,u32,u32,i32);
extern i32  schedule_node_list_is_locked(void);
extern u32  FUN_010202f0(void);
extern void FUN_01020634(void);
extern u32  radio_phy_airtime_base_get(u32);
extern void FUN_01022a84(void);

#define DAT_0101b73c 0x210010a0u
#define DAT_0101b740 0x0103c254u
#define DAT_0101b744 0x10624dd3u
#define DAT_0101b748 0x210010f0u

#define CARRY4(a,b) ((u32)(a) > (0xFFFFFFFFu - (u32)(b)))


void FUN_0101b54c(u32 param_1)
{
  u8 *pcVar5;
  i8 cVar2;
  u8 bVar3;
  i64 lVar4;
  u16 uVar6;
  u32 uVar7;
  i32 iVar8;
  u32 uVar9;
  u32 uVar10;
  i32 iVar11;
  u32 uVar12;
  u32 uVar13;
  u32 uVar14;
  u32 uVar15;
  u32 uVar16;
  u32 uVar17;
  u32 uVar18;
  i32 iVar19;
  i32 iVar20;
  u32 bVar21;
  i32 *piVar1;

  pcVar5 = (u8*)DAT_0101b73c;
  if (1 < param_1) {
    if (1 < param_1 - 2) {
      goto TRAP_8c3;
    }
    piVar1 = (i32*)(DAT_0101b73c + 0x28);
    *(volatile u8*)(DAT_0101b73c + 0x2c) = 1;
    *(volatile u8*)((u32)*piVar1 + 0x300) = 0;
    pcVar5[0x2d] = (u8)(param_1 == 3);
    if (pcVar5[0] != 5) {
      goto TRAP_866;
    }
    FUN_0101bc3c();
    cVar2 = (i8)pcVar5[0x14];
    *(volatile u32*)(pcVar5 + 0x28) = 0;
    if (cVar2 != 0) {
      FUN_01020634();
      FUN_01022a84();
      pcVar5[0x14] = 0;
      pcVar5[0x15] = 0;
      return;
    }
    return;
  }
  uVar18 = *(volatile u32*)(DAT_0101b73c + 0x18);
  iVar19 = *(volatile i32*)(DAT_0101b73c + 0x1c);
  uVar7 = FUN_010202f0();
  iVar8 = controller_radio_state_get();
  bVar3 = *(u8*)((u32)iVar8 + 1);
  uVar16 = (u32)bVar3;
  iVar11 = *(volatile i32*)(pcVar5 + 0x28);
  *(volatile u16*)((u32)iVar11 + 0x6e) = (u16)(((u32)bVar3 << 8) | bVar3);
  iVar8 = *(volatile i32*)(pcVar5 + 0x28);
  *(volatile u8*)((u32)iVar11 + 0x70) = 0xff;
  FUN_0100f1a8((u32)iVar8 + 0x30, (bVar3 & 0xc) != 0);
  uVar9 = sdc_phy_timing_offset_get(param_1 & 1, uVar16, 0, 0xff);
  iVar8 = (i32)radio_phy_airtime_base_get(uVar16);
  if (param_1 == 1) {
    if (uVar16 == 8) uVar12 = 0xbe8;
    else if (uVar16 == 4) uVar12 = 0x486;
    else if (uVar16 == 2) uVar12 = 0x14c;
    else uVar12 = 0x1f8;
  } else {
    uVar12 = 0x1f8;
  }
  iVar11 = *(volatile i32*)(pcVar5 + 0x28);
  uVar14 = uVar9 + uVar7 + uVar18;
  uVar17 = *(volatile u32*)((u32)iVar11 + 0x14);
  lVar4 = (i64)((u64)DAT_0101b744 *
          (u64)((u32)*(volatile u16*)(DAT_0101b740 + uVar16 * 2 + 0x28) + (u32)iVar8 + 999));
  uVar16 = (u32)((u64)lVar4 >> 0x26);
  uVar13 = uVar14 - uVar16;
  uVar15 = uVar13 + uVar12;
  iVar19 = ((iVar19 + (i32)CARRY4(uVar9,uVar7) + (i32)CARRY4(uVar9 + uVar7, uVar18)) -
           (i32)(uVar14 < uVar16)) + (i32)CARRY4(uVar13, uVar12);
  iVar8 = FUN_0101dd9c(DAT_0101b744, (i32)lVar4);
  if (DAT_0101b748 == (u32)iVar8) {
    if (*(volatile i8*)((u32)iVar11 + 0x73) != 0) {
      uVar7 = *(volatile u32*)(pcVar5 + 0x50);
      iVar20 = *(volatile i32*)(pcVar5 + 0x54);
      iVar8 = schedule_node_list_is_locked();
      if (iVar8 == 0) {
        uVar9 = (u32)(i16)(*(volatile i16*)((u32)iVar11 + 0x2fc));
        *(volatile u16*)((u32)iVar11 + 0x2fc) = 0;
        bVar21 = CARRY4(uVar9, uVar7);
        uVar7 = uVar9 + uVar7;
        iVar20 = iVar20 + ((i32)uVar9 >> 0x1f) + (i32)bVar21;
      }
      uVar7 = schedule_phase_offset_get(uVar7, iVar20, uVar17, 0,0,0);
      goto LAB_0101b666;
    }
    iVar8 = *(volatile i32*)(pcVar5 + 0x28);
    uVar7 = 0;
    uVar9 = 0;
    if (*(volatile i32*)(pcVar5 + 0x78) == 0) goto LAB_0101b6b8;
  } else {
    uVar7 = schedule_phase_offset_get(*(volatile u32*)((u32)iVar11 + 0x2d8), *(volatile i32*)((u32)iVar11 + 0x2dc),
                          uVar17, DAT_0101b748, uVar15, iVar19);
    if (uVar17 < uVar7) {
      goto TRAP_40f;
    }
LAB_0101b666:
    iVar8 = *(volatile i32*)(pcVar5 + 0x28);
    uVar9 = uVar7;
    if (*(volatile u32*)(pcVar5 + 0x78) <= uVar7) {
LAB_0101b6b8:
      uVar10 = FUN_0100d6b0(uVar7, *(volatile u32*)((u32)iVar8 + 0x14));
      *(volatile u32*)((u32)iVar8 + 0x24) = uVar10;
      iVar8 = *(volatile i32*)(pcVar5 + 0x28);
      iVar11 = *(volatile i32*)((u32)iVar8 + 0x14);
      goto LAB_0101b67a;
    }
  }
  iVar11 = *(volatile i32*)((u32)iVar8 + 0x14);
  uVar7 = uVar9 + (u32)iVar11;
  *(volatile i32*)((u32)iVar8 + 0x24) = iVar11;
LAB_0101b67a:
  uVar6 = FUN_0100d624(5, iVar11);
  iVar11 = *(volatile i32*)(pcVar5 + 0x28);
  *(volatile u16*)((u32)iVar8 + 0x28) = uVar6;
  if ((u32)*(volatile u16*)((u32)iVar11 + 0x28) <= uVar7 - (u32)*(volatile i32*)((u32)iVar11 + 0x24)) {
    goto TRAP_854;
  }
  *(volatile u32*)((u32)iVar11 + 0x2d8) = uVar7 + uVar15;
  *(volatile u32*)((u32)iVar11 + 0x2dc) = (u32)iVar19 + CARRY4(uVar7, uVar15);
  return;

TRAP_866:
  sdc_assertion_fail(0x21,0x866);
TRAP_8c3:
  sdc_assertion_fail(0x21,0x8c3);
TRAP_854:
  sdc_assertion_fail(0x21,0x854);
TRAP_40f:
  sdc_assertion_fail(0x21,0x40f);
  for (;;) { sdc_assertion_fail(0x21,0x40f); }
}
