#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00042a64 @ 0x00042a64
 * public-name: onboarding_ble_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   check_ancs_inbox_flag_change             <= FUN_0002eb40 @ 0x0002eb40
 *   onboarding_retry_watchdog_update         <= FUN_00040708 @ 0x00040708
 *   k_uptime_get_8                           <= FUN_0007d382 @ 0x0007d382
 * address symbols (name @ address):
 *   rodata_aa611                             @ 0x000aa611
 *   rodata_aa63d                             @ 0x000aa63d
 *   rodata_aa661                             @ 0x000aa661
 *   rodata_aa665                             @ 0x000aa665
 *   rodata_aa669                             @ 0x000aa669
 *   rodata_aa66d                             @ 0x000aa66d
 *   rodata_aa671                             @ 0x000aa671
 *   rodata_aa675                             @ 0x000aa675
 *   rodata_aa778                             @ 0x000aa778
 *   g_log_level                              @ 0x2000230c
 *   g_onboarding_step_retry_cnt              @ 0x20004bf0
 *   g_log_use_alt_sink                       @ 0x20007554
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 *   g_onboarding_primary_reset_flag          @ 0x2001cdcf
 *   onboarding_attempt_counter               @ 0x2001cdd2
 */
/* Reconstructed onboarding_ble_process @ 0x42a64  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void DEBUG_PRINT(u32,u32,...);
extern u32 get_device_info(void);
extern void debug_print(u32,u32,...);
extern u32 check_ancs_inbox_flag_change(void);
extern void onboarding_retry_watchdog_update(void);
extern u64 k_uptime_get_8(void);
extern void thunk_FUN_00043308(void);
extern void update_persist_task_status(u32,u32,u32);

u32 onboarding_ble_process(u32 param_1, u32 param_2, u32 param_3, u32 param_4)
{
  u8 cVar1;
  u32 uVar4;
  u64 uVar9;
  u32 ctx;
  u32 puVar6;

  if (0x17 < *(volatile u8*)(param_3 + 1)) {
    if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(((unsigned long)&rodata_aa611) /*=0xaa611*/, ((unsigned long)&rodata_aa778) /*=0xaa778*/,
                    (u32)*(volatile u8*)(param_3+1));
      } else {
        debug_print(((unsigned long)&rodata_aa611) /*=0xaa611*/, ((unsigned long)&rodata_aa778) /*=0xaa778*/,
                     (u32)*(volatile u8*)(param_3+1));
      }
    }
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xca;
    return 3;
  }

  *(volatile u8*)((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/ = 0;
  uVar9 = k_uptime_get_8();
  cVar1 = *(volatile u8*)(param_3 + 1);
  *(volatile u64*)(((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/ + 8) = uVar9;
  if (cVar1 == 0x12) goto LAB_tail;

  onboarding_retry_watchdog_update();
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u8*)ctx = 1;
  uVar9 = k_uptime_get_8();
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u32*)(ctx + 4) = (u32)uVar9;
  *(volatile u32*)(ctx + 8) = (u32)(uVar9 >> 32);
  ctx = *(volatile u32*)(param_1 + 0x1014);
  *(volatile u8*)(ctx + 2) = *(volatile u8*)(param_3 + 1);

  if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
    ctx = *(volatile u32*)(param_1 + 0x1014);
    if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT(((unsigned long)&rodata_aa63d) /*=0xaa63d*/, ((unsigned long)&rodata_aa778) /*=0xaa778*/,
                  (u32)*(volatile u8*)(ctx+2));
    } else {
      debug_print(((unsigned long)&rodata_aa63d) /*=0xaa63d*/, ((unsigned long)&rodata_aa778) /*=0xaa778*/,
                   (u32)*(volatile u8*)(ctx+2));
    }
  }

  ctx = *(volatile u32*)(param_1 + 0x1014);
  switch (*(volatile u8*)(ctx + 2)) {
  case 1:
    *(volatile u8*)(ctx + 1) = 1;
    ctx = *(volatile u32*)(param_1 + 0x1014);
    puVar6 = ((unsigned long)&rodata_aa661) /*=0xaa661*/;
    goto LAB_00042b1c;
  case 2:
    puVar6 = ((unsigned long)&rodata_aa665) /*=0xaa665*/;
    goto LAB_00042b1c;
  case 3:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)((unsigned long)&rodata_aa669) /*=0xaa669*/;
    *(volatile u8*)((unsigned long)&g_onboarding_primary_reset_flag) /*=0x2001cdcf*/ = 0;
    *(volatile u8*)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/ = 0;
    *(volatile u8*)(ctx + 3) = 0;
    *(volatile u8*)(ctx + 0xd) = 0;
    *(volatile u8*)(ctx + 0xe) = 0;
    *(volatile u8*)(ctx + 0xf) = 0;
    *(volatile u8*)(ctx + 0x10) = 0;
    *(volatile u8*)(ctx + 0x11) = 0;
    *(volatile u8*)(ctx + 0x12) = 0;
    *(volatile u8*)(ctx + 0x13) = 0;
    *(volatile u8*)(ctx + 0x14) = 0;
    *(volatile u8*)(ctx + 0x15) = 0;
    *(volatile u8*)(ctx + 0x16) = 0;
    *(volatile u8*)(ctx + 0x17) = 0;
    *(volatile u8*)(ctx + 0x18) = 0;
    *(volatile u8*)(ctx + 0x19) = 0;
    *(volatile u8*)(ctx + 0x1a) = 0;
    *(volatile u8*)(ctx + 0xc) = 0;
    break;
  case 4:
  case 5:
  case 6:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)((unsigned long)&rodata_aa66d) /*=0xaa66d*/;
    *(volatile u8*)((unsigned long)&onboarding_attempt_counter) /*=0x2001cdd2*/ = 0;
    *(volatile u8*)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/ = 0;
    uVar4 = get_device_info();
    *(volatile u8*)(ctx + 3) = *(volatile u8*)(uVar4 + 0xee4);
    if (*(volatile u8*)(ctx + 2) == 6) {
      *(volatile u8*)(ctx + 0x1f) = 0;
    }
    break;
  case 7:
    puVar6 = ((unsigned long)&rodata_aa671) /*=0xaa671*/;
    goto LAB_00042b1c;
  case 8:
  case 9:
    puVar6 = ((unsigned long)&rodata_aa66d) /*=0xaa66d*/;
    goto LAB_00042b1c;
  case 10:
  case 11:
    *(volatile u8*)ctx = 0;
    *(volatile u8*)(ctx + 1) = 0;
    break;
  case 12:
    *(volatile u8*)(ctx + 1) = 1;
    ctx = *(volatile u32*)(param_1 + 0x1014);
    puVar6 = ((unsigned long)&rodata_aa675) /*=0xaa675*/;
LAB_00042b1c:
    *(volatile u32*)(ctx + 0x1b) = *(volatile u32*)puVar6;
    break;
  case 15:
  case 17: {
    u32 t1 = get_device_info();
    u32 t2 = get_device_info();
    ctx = *(volatile u32*)(t2 + 0x1014);
    *(volatile u8*)(ctx + 3) = *(volatile u8*)(t1 + 0xee4);
    break;
  }
  default:
    break;
  }
  thunk_FUN_00043308();

LAB_tail:
  if (*(volatile u16*)(param_2 + 2) == 2) {
    uVar4 = 3;
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xc9;
  } else if (*(volatile u16*)(param_2 + 2) == 3) {
    u8 uVar2;
    *(volatile u16*)(param_4) = *(volatile u16*)(param_3);
    *(volatile u8*)(param_4+2) = 0xc9;
    uVar2 = *(volatile u8*)(param_3 + 2);
    *(volatile u8*)(param_4+3) = uVar2;
    if (*(volatile u8*)(*(volatile u32*)(param_1 + 0x1014)) != 0) {
      *(volatile u8*)(param_1 + 0xcd) = uVar2;
    }
    uVar4 = 4;
  } else {
    uVar4 = 0;
  }

  if (*(volatile u8*)(param_3 + 1) != 0x12) {
    u32 t1 = get_device_info();
    u32 p = *(volatile u32*)(t1 + 0x1054);
    if (*(volatile u32*)p != 0xe) {
      if (check_ancs_inbox_flag_change() == 0) {
        u32 t2 = get_device_info();
        update_persist_task_status(t2, 0xe, 2);
        {
          u32 t3 = get_device_info();
          u32 t4 = get_device_info();
          ctx = *(volatile u32*)(t4 + 0x1014);
          *(volatile u8*)(ctx + 0x20) = *(volatile u8*)(t3 + 0xed5);
          {
            u32 t5 = get_device_info();
            *(volatile u8*)(t5 + 0xed5) = 0x2a;
          }
        }
      }
    }
  }

  return uVar4;
}
