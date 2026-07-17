/* Reconstructed FUN_00028a1c @ 0x28a1c  (parity: 60/60 trials, PROVEN) */
/* CFG_VERIFY_PREFIX_FIRST: modeled first oracle result cannot take the only return. */

#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, ...);
extern uintptr_t get_device_info(void);
extern void handle_touch_key_irq(void);
extern void FUN_00032fd0(int32_t);
extern int64_t FUN_00032fdc(void);
extern void k_msleep(int32_t milliseconds); /* FUN_0007cb8e@0x0007cb8e */
#define k_msleep_ticks32768_a k_msleep
extern void read_rtc_counter_ms(void *a);
extern int32_t get_uptime_ms(void);
extern void update_sync_buffer(void *queue, int32_t key, int32_t timeout,
                               int32_t flags);
extern void FUN_0002893c(void);
extern void on_triple_click(void);
extern void FUN_00028964(void);
extern uint32_t sys_reboot(int32_t a);
extern void debug_print(uint32_t a, uint32_t b, uint32_t c, ...);

void FUN_00028a1c(char *param_1, int32_t param_2, uint32_t param_3)
{
  volatile uint8_t *pcVar2;
  volatile int32_t *piVar1;
  int32_t iVar3;
  int32_t iVar4;
  uint32_t uVar5;
  int32_t iVar6;
  int32_t iVar7;
  int32_t iVar8;
  int32_t iVar9;
  int64_t uVar10;

  pcVar2 = (volatile uint8_t *)0x20019dacUL;
  piVar1 = (volatile int32_t *)0x20006a00UL;
  iVar6 = 0;
  iVar8 = 0;
  iVar7 = 0;
  iVar9 = 0;
LAB_00028a32:
  do {
    while (1) {
      uVar10 = FUN_00032fdc();
      if ((int32_t)uVar10 == 1) {
        return;
      }
      update_sync_buffer(param_1 + 0xb0,
                         (int32_t)((uint64_t)uVar10 >> 32), 0x4000, 0);
      if ((*(char *)(param_1 + 1) != '\x01') &&
          (iVar3 = (int32_t)get_device_info(), *(char *)(iVar3 + 1) != '\b')) break;
      k_msleep_ticks32768_a(5000);
    }
  } while (-1 < (int32_t)((uint32_t)*(uint16_t *)(param_1 + 0x105c) << 0x1f));
  if (*piVar1 != 0) {
    get_uptime_ms();
    handle_touch_key_irq();
    get_uptime_ms();
    *piVar1 = 0;
  }
  if (*pcVar2 == '\x01') {
    iVar3 = get_uptime_ms();
    read_rtc_counter_ms(param_1 + 0x1078);
    if (30000 < iVar3 - iVar9) {
      iVar8 = 0;
      iVar6 = iVar8;
    }
    iVar6 = iVar6 + 1;
    *pcVar2 = 0;
  }
  else {
    iVar3 = iVar9;
    if (*pcVar2 == '\x02') {
      iVar8 = get_uptime_ms();
      *pcVar2 = 0;
    }
  }
  param_2 = get_uptime_ms();
  iVar4 = get_uptime_ms();
  iVar9 = iVar3;
  if (iVar6 != 1) goto LAB_00028b3a;
  if (iVar7 == 0) {
    if ((iVar8 == 0) && (30000 < param_2 - iVar3)) {
      DEBUG_PRINT(0xa0b33);
      param_2 = iVar4;
      goto LAB_00028aae;
    }
  }
  else {
LAB_00028aae:
    iVar7 = 1;
  }
  goto LAB_00028ab0;
LAB_00028b3a:
  if (iVar6 == 0) goto LAB_00028a32;
LAB_00028ab0:
  if ((iVar8 <= iVar3) || (iVar4 - iVar8 < 0x2711)) goto LAB_00028a32;
  if (0x249f0 < iVar8 - iVar3) {
    DEBUG_PRINT(0xa0b7c);
    read_rtc_counter_ms(param_1 + 0x1078);
code_r0x00028ad6:
    DEBUG_PRINT(0xa6990, *(uint32_t *)(param_1 + 0x1078));
    goto LAB_00028b4e;
  }
  uVar5 = 0xa0bc5;
  if (0x15f90 < iVar8 - iVar3) {
code_r0x00028b4a:
    DEBUG_PRINT(uVar5);
  }
  else {
    switch (iVar6) {
    case 1:
      uVar5 = 0xa0c0f;
      if (iVar7 == 0) {
        DEBUG_PRINT(0xa0c21);
        goto code_r0x00028ad6;
      }
      goto code_r0x00028b4a;
    case 2:
      FUN_0002893c();
      break;
    case 3:
      on_triple_click();
      break;
    case 4:
      if (0 < *(volatile int32_t *)0x2000230cUL) {
        if (*(volatile int32_t *)0x20007554UL == 0)
          DEBUG_PRINT(0xa0c6c, 0xa1a58, 4);
        else
          debug_print(0xa0c6c, 0xa1a58, 4);
      }
      do {
        k_msleep_ticks32768_a(500);
        uVar5 = sys_reboot(1);
        DEBUG_PRINT(uVar5);
      } while (1);
    default:
      FUN_00028964();
      FUN_00032fd0(1);
    }
  }
LAB_00028b4e:
  iVar6 = 0;
  iVar7 = iVar6;
  goto LAB_00028a32;
}
