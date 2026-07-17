#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a0d8 @ 0x0002a0d8
 * public-name: touch_key_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   reset_all_usr_data                       <= FUN_0002316c @ 0x0002316c
 *   trigger_touch_key_hw_reset               <= FUN_0002a0c0 @ 0x0002a0c0
 *   handle_touch_key_irq                     <= FUN_00030af0 @ 0x00030af0
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   k_msleep_ticks32768_a                    <= FUN_0007cb8e @ 0x0007cb8e
 *   read_rtc_counter_ms                      <= FUN_0007d0aa @ 0x0007d0aa
 *   get_uptime_ms                            <= FUN_00086690 @ 0x00086690
 * address symbols (name @ address):
 *   rodata_a15d6                             @ 0x000a15d6
 *   rodata_a1626                             @ 0x000a1626
 *   rodata_a1681                             @ 0x000a1681
 *   rodata_a172a                             @ 0x000a172a
 *   rodata_a1a76                             @ 0x000a1a76
 *   g_log_level                              @ 0x2000230c
 *   g_touch_key_irq_pending                  @ 0x20006a00
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_touch_key_reset_reason                 @ 0x20007b18
 *   g_touch_key_press_active                 @ 0x20018d89
 *   g_touch_key_irq_line_status              @ 0x20019dac
 */
/* Reconstructed touch_key_thread @ 0x2a0d8  (parity: 1/1 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, ...);
extern uintptr_t get_device_info(void);
extern void debug_print(uint32_t a, uint32_t b, uint32_t c, ...);
extern void trigger_touch_key_hw_reset(void);
extern void handle_touch_key_irq(void);
extern void k_msleep_ticks32768_a(int32_t);
extern void read_rtc_counter_ms(void *a);
extern int32_t get_uptime_ms(void);
extern void thunk_FUN_00072908(void *a);
extern void reset_all_usr_data(void *a, int32_t b);
extern void FUN_0007c058(int32_t a);
extern void FUN_00017a28(void);
extern void FUN_00017a34(void);
extern uint32_t sys_reboot(int32_t a);

void touch_key_thread(char *param_1)
{
  volatile int32_t *piVar1;
  volatile int32_t *piVar2;
  int32_t iVar3;
  int32_t iVar4;
  int32_t iVar5;
  uint32_t format_string;
  uint32_t uVar6;
  int32_t iVar7;
  int32_t iVar8;
  int32_t iVar9;
  int32_t iVar10;
  int32_t iVar11;
  int32_t iVar12;
  int32_t iVar13;

  iVar10 = 0;
  iVar9 = 0;
  iVar7 = 0;
  iVar11 = 0;
  iVar12 = 0;
LAB_0002a0e8:
  do {
    while ((thunk_FUN_00072908(param_1 + 0xb0), *(char *)(param_1 + 1) == '\x01' ||
            ((iVar3 = (int32_t)get_device_info(), *(char *)(iVar3 + 1) == '\b')))) {
      k_msleep_ticks32768_a(5000);
    }
    if (*(volatile int32_t *)((unsigned long)&g_touch_key_irq_pending) /*=0x20006a00*/ != 0) {
      handle_touch_key_irq();
      *(volatile int32_t *)((unsigned long)&g_touch_key_irq_pending) /*=0x20006a00*/ = 0;
    }
  } while (-1 < (int32_t)((uint32_t)*(uint16_t *)(param_1 + 0x105c) << 0x1f));
  if (*(volatile uint8_t *)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ == 1) {
    iVar3 = get_uptime_ms();
    read_rtc_counter_ms(param_1 + 0x1078);
    if (10000 < iVar3 - iVar11) {
      iVar9 = 0;
      iVar7 = iVar9;
    }
    iVar8 = iVar7 + 1;
    *(volatile uint8_t *)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ = 0;
  }
  else {
    iVar8 = iVar7;
    iVar3 = iVar11;
    if (*(volatile uint8_t *)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ == 2) {
      iVar9 = get_uptime_ms();
      *(volatile uint8_t *)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/ = 0;
      *(volatile uint8_t *)((unsigned long)&g_touch_key_press_active) /*=0x20018d89*/ = 0;
    }
  }
  iVar4 = get_uptime_ms();
  iVar5 = get_uptime_ms();
  piVar2 = (volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  piVar1 = (volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/;
  iVar5 = iVar5 - iVar9;
  iVar13 = iVar9 - iVar3;
  iVar7 = iVar8;
  iVar11 = iVar3;
  if (iVar8 != 1) goto LAB_0002a2c0;
  iVar4 = iVar4 - iVar3;
  if (iVar10 != 0) {
    if (iVar9 == 0) {
LAB_0002a222:
      if (iVar12 == 0) {
        iVar7 = 0x23;
      }
      else {
        iVar7 = 3;
      }
      if (iVar7 * 30000 < iVar4) {
        if (0 < *piVar1) {
          if (*piVar2 == 0) {
            DEBUG_PRINT(((unsigned long)&rodata_a1626) /*=0xa1626*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, iVar12);
          }
          else {
            debug_print(0,0,0);
          }
        }
        iVar10 = 0;
        *(volatile int32_t *)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/ = 6;
        trigger_touch_key_hw_reset();
        iVar7 = 0;
        iVar12 = iVar10;
        goto LAB_0002a0e8;
      }
      if (iVar3 < 0) goto LAB_0002a24e;
    }
    else {
      iVar7 = iVar10;
      if (iVar9 <= iVar3) goto LAB_0002a0e8;
LAB_0002a24e:
      if (10000 < iVar5) {
        if (15000 < iVar13) {
          iVar10 = 1;
          goto LAB_0002a260;
        }
        goto LAB_0002a174;
      }
    }
    iVar10 = 1;
    iVar7 = iVar8;
    goto LAB_0002a0e8;
  }
  if (iVar9 == 0) {
    read_rtc_counter_ms(param_1 + 0x1078);
    if (((int32_t)0xffffb1e1 <= *(int32_t *)(param_1 + 0x1078)) &&
        (*(int32_t *)(param_1 + 0x1078) < 20000)) {
      iVar7 = 0;
      goto LAB_0002a0e8;
    }
    if (15000 < iVar4) {
      if (0 < *piVar1) {
        if (*piVar2 == 0) {
          DEBUG_PRINT(((unsigned long)&rodata_a15d6) /*=0xa15d6*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, iVar4);
        }
        else {
          debug_print(0,0,0);
        }
      }
      *(volatile int32_t *)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/ = 4;
      trigger_touch_key_hw_reset();
      goto LAB_0002a222;
    }
    if (-1 < iVar3) {
      iVar10 = 0;
      goto LAB_0002a0e8;
    }
  }
  else if (iVar9 <= iVar3) goto LAB_0002a0e8;
  if (10000 < iVar5) {
    if (15000 < iVar13) goto LAB_0002a260;
LAB_0002a174:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(((unsigned long)&rodata_a172a) /*=0xa172a*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, *(uint32_t *)(param_1 + 0x1078));
      }
      else {
        debug_print(0,0,0);
      }
    }
    uVar6 = 1;
    goto LAB_0002a282;
  }
  goto LAB_0002a0e8;
LAB_0002a2c0:
  if (((iVar8 == 0) || (iVar9 <= iVar3)) || (iVar5 < 0x2711)) goto LAB_0002a0e8;
  if (15000 < iVar13) {
LAB_0002a260:
    if (iVar13 <= (int32_t)0x11940) {
      if (0 < *piVar1) {
        if (*piVar2 == 0) {
          DEBUG_PRINT(((unsigned long)&rodata_a1626) /*=0xa1626*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
        }
        else {
          debug_print(0,0,0);
        }
      }
      iVar9 = 0;
      iVar7 = iVar8;
      iVar12 = 1;
      goto LAB_0002a0e8;
    }
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(((unsigned long)&rodata_a1681) /*=0xa1681*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    uVar6 = 5;
    goto LAB_0002a282;
  }
  switch (iVar8) {
  case 2:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa177f, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    uVar6 = 2;
    goto LAB_0002a282;
  case 3:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa17d1, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    uVar6 = 3;
LAB_0002a282:
    *(volatile int32_t *)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/ = uVar6;
    trigger_touch_key_hw_reset();
    break;
  case 5:
    goto code_r0x0002a410;
  case 10:
    reset_all_usr_data(param_1, 1);
    break;
  case 0xf:
    FUN_0007c058(10);
    if (0 < *(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(0xa1823, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 0xf);
      }
      else {
        debug_print(0,0,0);
      }
    }
  }
  iVar10 = 0;
  iVar7 = iVar10;
  goto LAB_0002a0e8;
code_r0x0002a410:
  if (0 < *(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
    format_string = 0xa184b;
    if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) goto code_r0x0002a476;
    debug_print(0xa184b, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 5);
  }
  do {
    FUN_00017a28();
    if (0 < *(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(0xa1868, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    FUN_00017a34();
    if (0 < *(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(0xa187e, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
      if (0 < *(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          DEBUG_PRINT(0xa0c6c, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 5);
        }
        else {
          debug_print(0,0,0);
        }
      }
    }
    k_msleep_ticks32768_a(500);
    format_string = sys_reboot(1);
code_r0x0002a476:
    DEBUG_PRINT(format_string);
  } while (1);
}
