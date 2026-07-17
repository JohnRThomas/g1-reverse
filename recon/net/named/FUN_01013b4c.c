/* readable reconstruction; identity: FUN_01013b4c @ 0x01013b4c
 * public-name: FUN_01013b4c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_packet_duration_calculate     <= FUN_010122b4 @ 0x010122b4
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 *   sdc_timing_scale                         <= FUN_01024678 @ 0x01024678
 * address symbols (name @ address):
 *   g_net_radio_ack_pending_flag             @ 0x21000f54
 */
/* net-core FUN_01013b4c @ 0x1013b4c  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void sdc_assertion_fail(u32,u32);
extern u32 FUN_0100f66c(void);
extern u32 controller_packet_duration_calculate(void*,u32);
extern u32 FUN_010126c0(void*);
extern u32 FUN_010126f0(void*);
extern void FUN_01012960(void*,u32);
extern u32 FUN_01012b98(u32);
extern u16 FUN_01012c14(void*);
extern u32 FUN_01022e34(u32,void*);
extern u32 FUN_01022ea8(void);
extern u32 sdc_conn_window_admit(u8,void*);
extern u32 sdc_timing_scale(u32,u16);
extern short FUN_010246d8(void);
extern void FUN_01025a84(void*,u32,u32);
extern short sdc_timing_compensation_get(void);
extern u64 controller_time_now(void);

static u32 *const DAT_01013cd4 = (u32*)0x21000f54;

unsigned int FUN_01013b4c(void *param_1_v, void *param_2_v, unsigned int param_3)
{
  u8 *param_1 = (u8*)param_1_v;
  u8 *param_2 = (u8*)param_2_v;
  int iVar5;
  u32 uVar6;
  u32 uVar8, uVar9;
  u64 lVar10;
  u16 uVar1, uVar3;
  short sVar4;

  if (*(volatile char *)(param_1 + 0x120) != 0) {
    return 0xc;
  }
  iVar5 = (int)FUN_01022e34(0x01013485, param_1);
  if (iVar5 == 0x20) {
    return 0xc;
  }
  FUN_01025a84(param_1 + 0x100, 0, 0x50);
  *(volatile u8 *)(param_1 + 0x100) = (u8)iVar5;
  *(volatile void **)(param_1 + 0x104) = param_2;
  *(volatile u8 *)(param_1 + 0x120) = 1;
  if (param_2 != 0) {
    u8 bVar2 = (u8)FUN_0100f66c();
    *(volatile u8 *)(param_2 + 0x30c) = (bVar2 & 7) + 1;
  }
  uVar3 = FUN_01012c14(param_1);
  *(volatile u8 *)(param_1 + 0x128) = 0;
  *(volatile u16 *)(param_1 + 0x132) = 0x102;
  *(volatile u16 *)(param_1 + 0x130) = uVar3;
  sVar4 = FUN_010246d8();
  uVar6 = FUN_01022ea8();
  uVar1 = *(volatile u16 *)(param_1 + 0x130);
  if (uVar1 < uVar6) {
    uVar1 = (u16)uVar6;
  }
  uVar6 = (u32)(u16)(sVar4 + 0xe7 + uVar1);
  iVar5 = (int)FUN_010126c0(param_1);
  if (iVar5 == 0) {
    int iVar7 = (int)controller_packet_duration_calculate(param_1, 0);
    u8 *iVar5p = (u8*)DAT_01013cd4;
    *(volatile int *)(param_1 + 300) = iVar7 + 0x152;
    uVar8 = (u32)*(volatile u16 *)(iVar5p + 0x12);
    if ((uVar8 != 0) && (uVar8 = (u32)*(volatile u16 *)(param_1 + 0x22), uVar8 != 0)) {
      uVar8 = FUN_0100f66c();
      uVar9 = (u32)*(volatile u16 *)(iVar5p + 0x12);
      uVar8 = uVar8 - (uVar8 / uVar9) * uVar9;
    }
    lVar10 = controller_time_now();
    lVar10 = lVar10 + (u64)(uVar6 + uVar8);
    *(volatile u64 *)(param_1 + 0x138) = lVar10;
    if (param_3 != 0) {
      *(volatile u64 *)(param_1 + 0x140) = lVar10 + (u64)param_3;
      goto LAB_01013c32;
    }
  }
  else {
    sVar4 = sdc_timing_compensation_get();
    iVar5 = (int)sdc_timing_scale(param_3, (u16)(sVar4 + 0x668));
    *(volatile u32 *)(param_1 + 300) = (u32)(iVar5 + (int)param_3);
    lVar10 = controller_time_now();
    lVar10 = lVar10 + (u64)uVar6;
    *(volatile u16 *)(param_1 + 0x22) = 0;
    *(volatile int *)(param_1 + 0x138) = (int)lVar10;
    *(volatile u8 *)(param_1 + 0x108) = 1;
    *(volatile int *)(param_1 + 0x13c) = (int)(lVar10 >> 0x20);
    iVar5 = (int)FUN_010126f0(param_1);
    if (iVar5 == 0) {
      iVar5 = (int)FUN_01012b98(1);
      *(volatile u32 *)(param_1 + 0x10c) = (param_3 - 0x152) - iVar5;
    }
    else {
      iVar5 = (int)controller_packet_duration_calculate(param_1, 1);
      *(volatile u32 *)(param_1 + 0x10c) = (param_3 - 0x54e) - iVar5;
    }
  }
  *(volatile u32 *)(param_1 + 0x140) = 0xffffffff;
  *(volatile u32 *)(param_1 + 0x144) = 0x7fffffff;
LAB_01013c32:
  iVar5 = (int)sdc_conn_window_admit(*(volatile u8 *)(param_1 + 0x100), param_1 + 0x128);
  if (iVar5 != 0) {
    *(volatile u16 *)(param_1 + 0x122) = 0;
    *(volatile u32 *)(param_1 + 0x118) = *(volatile u32 *)(param_1 + 0x138);
    *(volatile u32 *)(param_1 + 0x11c) = *(volatile u32 *)(param_1 + 0x13c);
    FUN_01012960(param_1, 0);
    return 0;
  }
  sdc_assertion_fail(0x30, 0x1ec);
  return 0;
}
