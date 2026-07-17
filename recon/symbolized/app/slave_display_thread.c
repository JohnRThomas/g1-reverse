#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00027cfe @ 0x00027cfe
 * public-name: slave_display_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   upgradeAppLanguageInfoToFlash            <= FUN_00023af0 @ 0x00023af0
 *   upgradeDashboardStartupModeInfoToFlash   <= FUN_00023bfc @ 0x00023bfc
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   check_battery_critical                   <= FUN_0002bed0 @ 0x0002bed0
 *   update_persist_task_status               <= FUN_0002bef4 @ 0x0002bef4
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   msg_count_dec                            <= FUN_00034274 @ 0x00034274
 *   push_message_3439c                       <= FUN_0003439c @ 0x0003439c
 *   msg_content_decrement_timer              <= FUN_0003441c @ 0x0003441c
 *   handle_touch_single_click                <= FUN_0003707c @ 0x0003707c
 *   handle_dashboard_action                  <= FUN_00037108 @ 0x00037108
 *   handle_stocks_action                     <= FUN_000371e8 @ 0x000371e8
 *   update_not_disturb_settings              <= FUN_0003cb4c @ 0x0003cb4c
 *   onboarding_retry_watchdog_update         <= FUN_00040708 @ 0x00040708
 *   cal_panel_canvas_coord                   <= FUN_00042fb0 @ 0x00042fb0
 *   set_brightness_to_panel_reg_in_running   <= FUN_00047058 @ 0x00047058
 *   display_DelayClose                       <= FUN_000498c0 @ 0x000498c0
 *   display_inputEvent                       <= FUN_00049938 @ 0x00049938
 *   display_MasterSendClose                  <= FUN_000499b8 @ 0x000499b8
 *   display_powerEvent                       <= FUN_00049a28 @ 0x00049a28
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   update_display_status                    <= FUN_0007cce8 @ 0x0007cce8
 *   prepare_quick_note_mode                  <= FUN_0007cdb6 @ 0x0007cdb6
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_mode_flag                           @ 0x20018462
 *   g_new_notification_pending_flag          @ 0x20018d8d
 *   g_20018d96                               @ 0x20018d96
 *   g_notify_wakeup_delay_flag               @ 0x20018d97
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 *   g_even_ai_mic_icon_visible               @ 0x2001b9ab
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 */
/* Reconstructed slave_display_thread @ 0x27cfe  (parity: 1/1 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT();
extern void debug_print();
extern int32_t get_device_info();
extern int32_t is_battery_critical();
extern void change_work_mode_to();
extern void thunk_FUN_00072908();
extern void thunk_FUN_00074844();
extern void thunk_FUN_00072880();
extern void thunk_FUN_000745c8();
extern void thunk_FUN_00043308();
extern void set_brightness_to_panel_reg_in_running();
extern int32_t check_battery_critical();
extern void set_shutdown_flag();
extern void trigger_screen_state_change();
extern void cal_panel_canvas_coord();
extern void upgradeDashboardStartupModeInfoToFlash();
extern void display_DelayClose();
extern void prepare_quick_note_mode();
extern void update_persist_task_status();
extern void handle_touch_single_click();
extern void display_inputEvent();
extern int32_t get_timestamp();
extern void handle_dashboard_action();
extern void handle_stocks_action();
extern void display_MasterSendClose();
extern void display_powerEvent();
extern void upgradeAppLanguageInfoToFlash();
extern void FUN_000429f8();
extern void onboarding_retry_watchdog_update();
extern uint64_t k_uptime_get_1();
extern int32_t FUN_0007c132();
extern void update_temp_task_status();
extern void clear_timeout_message();
extern void check_pending_messages_flag();
extern void push_message_3439c();
extern void msg_count_dec();
extern void FUN_0003443c();
extern int32_t msg_content_recalc_unread();
extern void update_display_status();
extern void msg_content_decrement_timer();
extern void FUN_00023eec();
extern void update_persist_task_status_to_idle();
extern void update_not_disturb_settings();
extern void FUN_0007cb54();

#define B(o)   (*(volatile uint8_t *)(param_1+(o)))
#define SB(o)  (*(volatile int8_t  *)(param_1+(o)))
#define I32(o) (*(volatile int32_t *)(param_1+(o)))
#define DL     (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define GV     (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DBG1     do{ if (GV==0) DEBUG_PRINT(); else debug_print(); }while(0)
#define DBG_D224 do{ get_timestamp(); if (GV==0) DEBUG_PRINT(); else debug_print(); goto top; }while(0)

void slave_display_thread(int param_1, uint32_t param_2, uint32_t param_3, uint8_t param_4)
{
  int32_t p;
  int8_t cv;
  uint8_t b2, b15;

  B(0xfe7) = param_4;
  B(0xd5) = 0;
  if (1 < DL) DBG1;
  if (B(0xfea) == 0xb) change_work_mode_to();

top:
  if (B(0xfea) == 0xb) {
    B(0xd4) = B(0xd4) & 0xc0;
    B(0xd5) = (is_battery_critical() == 0) ? 6 : 3;
    thunk_FUN_00074844();
    goto while_cond;
  }
  thunk_FUN_00072908();
  goto while_cond;
while_body:
  thunk_FUN_00074844();
while_cond:
  if (SB(1) == 1 || *(volatile int8_t *)(get_device_info() + 1) == 8) goto while_body;

  if (SB(0xed7) != SB(0xcb) || SB(0xed5) != SB(0xed7)) {
    if (is_battery_critical() == 1) {
      set_brightness_to_panel_reg_in_running();
      B(0xcb)  = B(0xed5);
      B(0xed7) = B(0xed5);
    } else {
      B(0xed7) = B(0xcb);
      B(0xed5) = B(0xcb);
      set_brightness_to_panel_reg_in_running();
    }
  }

  switch (B(0xd4) & 0x3f) {

  case 0:
    if (SB(0xfe6) != 1) goto Ldefault;
    if (SB(0xd5) != 6 && check_battery_critical() == 0) {
      if (0 < DL) DBG1;
      goto top;
    }
    if (2 < DL) DBG1;
    change_work_mode_to();
    if (SB(0xd5) == 6 && SB(0xee4) != 2) B(0xee4) = 2;
    goto Ldefault;

  case 1:
    if (2 < DL) DBG1;
    cv = SB(0xfe6);
    *(volatile uint8_t *)((unsigned long)&g_notify_wakeup_delay_flag) /*=0x20018d97*/ = 1;
    *(volatile uint8_t *)((unsigned long)&g_20018d96) /*=0x20018d96*/ = 1;
    if (cv == 0) {
      set_shutdown_flag();
      B(0xee4) = 1;
      {
        volatile uint8_t *p13 = *(volatile uint8_t **)(param_1 + 0x1054);
        p13[0] = 0; p13[1] = 0; p13[2] = 0; p13[3] = 0;
      }
      trigger_screen_state_change();
      thunk_FUN_00072880();
    } else {
      thunk_FUN_00074844();
    }
    if (2 < DL) DBG1;
    goto top;

  case 2:
    if (2 < DL) DBG1;
    if (SB(0xe5) == 0xb) {
      if (1 < DL) DBG1;
      if (B(0xe6) < 10 && B(0xe7) < 9) {
        *(volatile uint8_t *)(get_device_info() + 0xec1) = B(0xe6);
        *(volatile uint8_t *)(get_device_info() + 0xec0) = B(0xe7);
        (void)get_device_info();
        (void)get_device_info();
        cal_panel_canvas_coord();
      }
    }
    *(volatile uint8_t *)((unsigned long)&g_20018d96) /*=0x20018d96*/ = 1;
    {
      int8_t d5 = SB(0xd5);
      if (d5 == 9 || d5 == 0xc || d5 == 0xa || d5 == 0xb || d5 == 6 ||
          d5 == 7 || d5 == 0xe || d5 == 0xf || d5 == 0x10 || d5 == 0x11 || d5 == 0)
        B(0xee4) = 2;
      change_work_mode_to();
      if (d5 != 9 || d5 != 0xa || d5 != 0xb || d5 != 0x10) thunk_FUN_00072880();
    }
    if (2 < DL) DBG1;
    *(volatile uint8_t *)((unsigned long)&g_20018d96) /*=0x20018d96*/ = 0;
    goto top;

  case 3:
    set_shutdown_flag();
    change_work_mode_to();
    goto top;

  case 4:
    set_shutdown_flag();
    B(0xfea) = 0xc;
    I32(0x104c) = 3;
    thunk_FUN_00072880();
    goto top;

  case 5:
    B(0xfea) = 0xa;
    I32(0x104c) = 3;
    thunk_FUN_00072880();
    goto top;

  case 6:
    if (2 < DL) DBG1;
    if (SB(0xe5) == 9) {
      if (2 < DL) DBG1;
      upgradeDashboardStartupModeInfoToFlash();
      goto top;
    }
    switch (B(0xe5)) {

    case 1:
      if (SB(0xd5) == 0xc) {
        if (SB(0xe6) == 0) {
          if (2 < DL) DBG1;
          display_DelayClose();
          goto L2812a;
        }
      } else if (SB(0xe6) == 1) {
        if (2 < DL) DBG1;
        prepare_quick_note_mode();
        B(0xec) = 0xc;
        **(volatile uint8_t **)(param_1 + 0x1020) = 1;
        update_persist_task_status();
        {
          volatile int8_t *q = (volatile int8_t *)(I32(0x1020) + 2);
          *q = (int8_t)(*q + 1);
        }
        goto Ldefault;
      }
      goto top;

    case 2: {
      b2 = B(0xe6);
      b15 = b2 & 0xf;
      if (b15 == 1) {
        if (SB(0xd5) != 6) goto L282f6;
        handle_touch_single_click();
        display_inputEvent();
        thunk_FUN_000745c8();
        if (DL < 3) goto top;
        DBG_D224;
      } else if (b15 == 2) {
        handle_touch_single_click();
        if (2 < DL) DBG_D224;
      } else if (b15 == 3) {
        if (SB(0xd5) != 6) goto L282f6;
        handle_dashboard_action();
      L28260:
        display_inputEvent();
        thunk_FUN_000745c8();
        if (2 < DL) DBG_D224;
      } else if (b15 == 4) {
        handle_dashboard_action();
      L28296:
        if (2 < DL) DBG_D224;
      } else {
        if (b15 == 5) {
          if (SB(0xd5) == 6) { handle_stocks_action(); goto L28260; }
        } else if (b15 == 6) {
          handle_stocks_action();
          goto L28296;
        }
      L282f6:
        if (1 < DL) DBG1;
      }
      goto top;
    }

    case 3:
      if (SB(0xd5) == 9) {
        if (SB(0xe6) == 1) {
          if (2 < DL) DBG1;
          goto L28342;
        }
        if (0 < DL) DBG1;
        goto top;
      }
      if (0 < DL) DBG1;
      goto top;

    case 4: {
      volatile uint8_t *sb5 = (volatile uint8_t *)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/;
      if (2 < DL) DBG1;
      B(0xcd) = *(volatile uint8_t *)(I32(0x1014) + 3);
      *(volatile uint8_t *)(I32(0x1014) + 2) = B(0xe6);
      *(volatile uint8_t *)(I32(0x1014) + 3) = B(0xe7);
      FUN_000429f8();
      cv = SB(0xe8);
      *sb5 = B(0xe7);
      thunk_FUN_00043308();
      onboarding_retry_watchdog_update();
      {
        uint64_t r = k_uptime_get_1();
        *(volatile int32_t *)(I32(0x1014) + 4) = (int32_t)r;
        *(volatile int32_t *)(I32(0x1014) + 8) = (int32_t)(r >> 32);
      }
      if (**(volatile int32_t **)(param_1 + 0x1054) == 0xe ||
          (FUN_0007c132() != 0 && *(volatile int8_t *)(I32(0x1014) + 1) == 0)) {
        int8_t c1 = *(volatile int8_t *)(I32(0x1014) + 2);
        if (c1 == 3) {
          if (*sb5 == 0x12) {
            *(volatile int8_t  *)(I32(0x1014) + 0xc) = cv;
            *(volatile uint8_t *)(I32(0x1014) + 0xd) = 3;
            *(volatile uint8_t *)(I32(0x1014) + 0xe) = 3;
          }
        } else if (c1 == 0xb) {
          **(volatile uint8_t **)(get_device_info() + 0x1014) = 0;
          *(volatile uint8_t *)(*(volatile int32_t *)(get_device_info() + 0x1014) + 1) = 0;
        }
      } else {
        if (cv == 1) {
          **(volatile uint8_t **)(param_1 + 0x1014) = 1;
          update_persist_task_status();
          *(volatile uint8_t *)(I32(0x1014) + 0x20) = B(0xed5);
          B(0xed5) = 0x2a;
        }
      }
      goto L2850c;
    }

    case 5:
      if (2 < DL) DBG1;
      {
        uint8_t v = B(0xe6);
        *(volatile uint8_t *)(I32(0x1010) + 2) = v;
        *(volatile uint8_t *)((unsigned long)&g_even_ai_mic_icon_visible) /*=0x2001b9ab*/ = v;
      }
      *(volatile uint8_t *)(get_device_info() + 0xcd) = *(volatile uint8_t *)((unsigned long)&g_even_ai_mic_icon_visible) /*=0x2001b9ab*/;
      update_not_disturb_settings();
      **(volatile uint8_t **)(param_1 + 0x1010) = 1;
      update_persist_task_status();
      goto L2850c;

    case 6:
      if (SB(0xd5) == 0xa) {
        if (SB(0xe6) != 1) { if (0 < DL) DBG1; goto top; }
        if (2 < DL) DBG1;
      L28342:
        display_MasterSendClose();
      L2812a:
        thunk_FUN_000745c8();
        goto top;
      }
      if (0 < DL) DBG1;
      goto top;

    case 7:
      if (SB(0xd5) == 6) {
        if (2 < DL) DBG1;
        display_powerEvent();
        goto L2812a;
      }
      if (0 < DL) DBG1;
      goto top;

    case 8:
      if (2 < DL) DBG1;
      cv = SB(0xe6);
      if (*(volatile int8_t *)((unsigned long)&g_ui_mode_flag) /*=0x20018462*/ != cv && 1 < DL) DBG1;
      upgradeAppLanguageInfoToFlash();
      goto top;

    case 10:
      if (2 < DL) DBG1;
      FUN_0007cb54();
      goto top;

    default:
      goto top;
    }

  case 7:
    switch (B(0xe5)) {
    case 0:
      update_temp_task_status();
      goto L2850c;
    case 1:
      *(volatile uint8_t *)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/ = 1;
      clear_timeout_message();
      check_pending_messages_flag();
      push_message_3439c();
      update_temp_task_status();
    L2850c:
      trigger_screen_state_change();
      goto Ldefault;
    case 2:
      msg_count_dec();
      cv = *(volatile int8_t *)(get_device_info() + 0xdd);
      if (cv != 0) cv = 6;
      FUN_0003443c();
      goto Ldefault;
    case 3:
      *(volatile uint8_t *)((unsigned long)&g_new_notification_pending_flag) /*=0x20018d8d*/ = 1;
      if (*(volatile int8_t *)(get_device_info() + 0x108f) != 0 &&
          msg_content_recalc_unread() != 0 &&
          *(volatile int8_t *)(get_device_info() + 0xd5) != 4) {
        (void)get_device_info();
        update_temp_task_status();
        (void)get_device_info();
        trigger_screen_state_change();
        check_pending_messages_flag();
      }
      goto Ldefault;
    default:
      goto Ldefault;
    }

  case 8:
    update_display_status();
    if (SB(0xe5) != 0 && SB(0xd5) == 4) {
      msg_content_decrement_timer();
      cv = *(volatile int8_t *)(get_device_info() + 0xdd);
      if (cv != 0) cv = 6;
      FUN_0003443c();
    }
    if (SB(0xee4) == 2) FUN_00023eec();
    update_persist_task_status_to_idle();
    goto Ldefault;

  default:
    goto top;
  }

Ldefault:
  thunk_FUN_00072880();
  goto top;
  (void)p; (void)param_2; (void)param_3;
}
