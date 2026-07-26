#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00027cfc @ 0x00027cfc
 * public-name: slave_display_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   onboarding_mark_retry_if_reset           <= FUN_000429f8 @ 0x000429f8
 *   device_addr_is_default                   <= FUN_0007c132 @ 0x0007c132
 *   atomic_or_bit1                           <= FUN_0007cb54 @ 0x0007cb54
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_99969                             @ 0x00099969
 *   rodata_a0354                             @ 0x000a0354
 *   rodata_a036a                             @ 0x000a036a
 *   rodata_a0396                             @ 0x000a0396
 *   rodata_a03b3                             @ 0x000a03b3
 *   rodata_a03d9                             @ 0x000a03d9
 *   rodata_a03f5                             @ 0x000a03f5
 *   rodata_a0434                             @ 0x000a0434
 *   rodata_a044e                             @ 0x000a044e
 *   rodata_a0477                             @ 0x000a0477
 *   rodata_a04cb                             @ 0x000a04cb
 *   rodata_a050a                             @ 0x000a050a
 *   rodata_a052d                             @ 0x000a052d
 *   rodata_a0568                             @ 0x000a0568
 *   rodata_a05c2                             @ 0x000a05c2
 *   rodata_a0621                             @ 0x000a0621
 *   rodata_a067b                             @ 0x000a067b
 *   rodata_a06d7                             @ 0x000a06d7
 *   rodata_a07eb                             @ 0x000a07eb
 *   rodata_a0889                             @ 0x000a0889
 *   rodata_a0932                             @ 0x000a0932
 *   rodata_a0962                             @ 0x000a0962
 *   rodata_a09ac                             @ 0x000a09ac
 *   rodata_a09ee                             @ 0x000a09ee
 *   rodata_a0a04                             @ 0x000a0a04
 *   rodata_a0a2e                             @ 0x000a0a2e
 *   rodata_a0a47                             @ 0x000a0a47
 *   rodata_a0a61                             @ 0x000a0a61
 *   rodata_a0a7b                             @ 0x000a0a7b
 *   rodata_a1a43                             @ 0x000a1a43
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b38                               @ 0x20007b38
 *   g_ui_mode_flag                           @ 0x20018462
 *   g_new_notification_pending_flag          @ 0x20018d8d
 *   g_20018d96                               @ 0x20018d96
 *   g_notify_wakeup_delay_flag               @ 0x20018d97
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 *   g_even_ai_mic_icon_visible               @ 0x2001b9ab
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 */
/* Reconstructed slave_display_thread @ 0x00027cfc; raw Ghidra identity FUN_00027cfe.
 * Ghidra omitted the live `movs r3,#1` at the thread entry and treated r3 as
 * a fourth argument. Reviewed image span: 0x9fc bytes through 0x286f7. The final branch occupies
 * 0x286c0..0x286c3; its literal pool is 0x286c4..0x286f7, immediately before
 * the independent FUN_000286f8 entry.
 * Durable name/back mapping: recon/catalogs/function_names_app.json.
 */
#include <stdint.h>
#include "../../../headers/g1_log.h"

/* FUN_00019c70 @ 0x19c70 */
extern uintptr_t get_device_info(void);         /* get_device_info @ 0x167a8 */
extern int is_battery_critical(void);            /* is_battery_critical @ 0x32ee4 */
extern void change_work_mode_to(uint32_t mode);
extern int k_sem_take(void *object, uint64_t timeout); /* 0x7cb48 */
extern void process_sync_buffer(void *object);                  /* 0x7cb4c */
extern void process_touch_event(void);                          /* 0x7cb50 */
extern void wait_for_event(uint32_t timeout, uint32_t flags);   /* 0x7cb8a */
extern void set_brightness_to_panel_reg_in_running(uint32_t level);
extern int display_panel_is_secondary(void *context);
extern void set_shutdown_flag(void *context, uint32_t publish);
extern void trigger_screen_state_change(uintptr_t reason, void *context,
                                        uint32_t enabled);
extern void cal_panel_canvas_coord(void *panel, void *canvas);
extern void upgradeDashboardStartupModeInfoToFlash(uint32_t mode);
extern void display_DelayClose(uint32_t delay_ms);
extern void prepare_quick_note_mode(void *context, uint32_t side);
extern void update_persist_task_status(void *context, uint32_t task,
                                       uint32_t state);
extern void handle_touch_single_click(uint32_t side);
extern void display_inputEvent(uint32_t event, uint32_t pressed);
extern uint32_t get_timestamp(void);
extern void handle_dashboard_action(uint32_t side);
extern void handle_stocks_action(uint32_t side);
extern void display_MasterSendClose(void);
extern void display_powerEvent(uint32_t event);
extern void upgradeAppLanguageInfoToFlash(uint32_t language);
extern void onboarding_retry_watchdog_update(void);
extern uint64_t k_uptime_get_1(void);
extern void update_temp_task_status(void *context, uint32_t task,
                                    uint32_t state);
extern void clear_timeout_message(uint32_t reason);
extern void check_pending_messages_flag(void);
extern void push_message_3439c(void);
extern void msg_count_dec(void);
extern int msg_content_recalc_unread(void);
extern void update_display_status(void *context, uint32_t status);
extern void msg_content_decrement_timer(void);
extern void update_persist_task_status_to_idle(void *context);
extern void update_not_disturb_settings(void);

/* Readable aliases for still-unnamed raw identities. */
#define refresh_onboarding_retry_state onboarding_mark_retry_if_reset
extern void onboarding_mark_retry_if_reset(void); /* @ 0x429f8 */
#define peer_address_is_uninitialized device_addr_is_default
extern int device_addr_is_default(uint32_t low, uint32_t high); /* @ 0x7c132 */
#define reset_onboarding_bitmap_state thunk_FUN_00043308
extern void thunk_FUN_00043308(void); /* @ 0x7d3be */
#define set_message_indicator set_message_pending_state
extern void set_message_pending_state(uint32_t value); /* @ 0x3443c */
#define get_pending_language_code get_ui_mode_flag2
extern uint8_t get_ui_mode_flag2(void); /* @ 0x23eec */
#define set_atomic_flag_bits atomic_or_bit1
extern void atomic_or_bit1(volatile uint32_t *flags); /* @ 0x7cb54 */

typedef struct {
    uint8_t device_side;
    uint8_t synchronization_paused;
    uint8_t reserved_0002[0x00c9];
    uint8_t panel_brightness;
    uint8_t reserved_00cc;
    uint8_t onboarding_previous_fragment;
    uint8_t reserved_00ce[0x0006];
    uint8_t display_event;
    uint8_t work_mode;
    uint8_t reserved_00d6[0x000f];
    uint8_t remote_command;
    uint8_t remote_value;
    uint8_t remote_aux;
    uint8_t remote_flag;
    uint8_t reserved_00e9[3];
    uint8_t pending_task_mode;
    uint8_t reserved_00ed[0x0de8];
    uint8_t requested_brightness;
    uint8_t reserved_0ed6;
    uint8_t brightness_shadow;
    uint8_t reserved_0ed8[0x000c];
    uint8_t screen_state;
    uint8_t reserved_0ee5[0x0101];
    uint8_t slave_ready;
    uint8_t thread_argument;
    uint8_t reserved_0fe8[2];
    uint8_t lifecycle_mode;
    uint8_t reserved_0feb[0x0025];
    uintptr_t do_not_disturb_record;
    uintptr_t onboarding_record;
    uint8_t reserved_1018[8];
    uintptr_t quick_note_record;
    uint8_t reserved_1024[0x28];
    uint32_t dispatch_status;
    uint8_t reserved_1050[4];
    uintptr_t system_event_record;
} slave_display_context_t;

_Static_assert(__builtin_offsetof(slave_display_context_t, panel_brightness) == 0xcb, "panel offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, display_event) == 0xd4, "event offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, remote_command) == 0xe5, "command offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, requested_brightness) == 0xed5, "brightness offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, slave_ready) == 0xfe6, "ready offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, do_not_disturb_record) == 0x1010, "dnd offset");
_Static_assert(__builtin_offsetof(slave_display_context_t, system_event_record) == 0x1054, "event-record offset");

static volatile int32_t *const log_level_reg =
    (volatile int32_t *)(uintptr_t)((unsigned long)&g_log_level) /*=0x2000230c*/;
static volatile int32_t *const g_log_backend =
    (volatile int32_t *)(uintptr_t)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
static volatile uint8_t *const g_display_update_active =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_20018d96) /*=0x20018d96*/;
static volatile uint8_t *const g_display_shutdown_active =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_notify_wakeup_delay_flag) /*=0x20018d97*/;
static volatile uint8_t *const g_message_clear_pending =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/;
static volatile uint8_t *const g_message_recalc_pending =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_new_notification_pending_flag) /*=0x20018d8d*/;
static volatile uint8_t *const g_remote_language =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_ui_mode_flag) /*=0x20018462*/;
static volatile uint8_t *const g_onboarding_fragment =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/;
static volatile uint8_t *const g_do_not_disturb_value =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_even_ai_mic_icon_visible) /*=0x2001b9ab*/;

#define DISPLAY_LOG_TAG ((uintptr_t)((unsigned long)&rodata_a1a43) /*=0xa1a43*/)
#define LOG_IF(level_, format_, ...) do { \
    if (*log_level_reg > (level_)) { \
        if (*g_log_backend == 0) \
            log_message((format_), DISPLAY_LOG_TAG, ##__VA_ARGS__); \
        else \
            debug_print((format_), DISPLAY_LOG_TAG, ##__VA_ARGS__); \
    } \
} while (0)
#define LOG_ACTION(format_, side_) do { \
    if (*log_level_reg > 2) { \
        uint32_t stamp_ = get_timestamp(); \
        if (*g_log_backend == 0) \
            log_message((format_), DISPLAY_LOG_TAG, stamp_, (side_)); \
        else \
            debug_print((format_), DISPLAY_LOG_TAG, stamp_, (side_)); \
    } \
} while (0)

void slave_display_thread(slave_display_context_t *context, uint32_t param_2,
                          uint32_t param_3)
{
  int32_t p;
  int8_t cv;
  uint8_t b2, b15;

  context->thread_argument = 1;
  context->work_mode = 0;
  LOG_IF(1, ((unsigned long)&rodata_99969) /*=0x99969*/, param_3, 0, context, param_2, param_3);
  if (context->lifecycle_mode == 0xb) change_work_mode_to(2);

top:
  if (context->lifecycle_mode == 0xb) {
    context->display_event = context->display_event & 0xc0;
    context->work_mode = (is_battery_critical() == 0) ? 6 : 3;
    wait_for_event(0x8000, 0);
    goto while_cond;
  }
  k_sem_take((uint8_t *)context + 0x20, UINT64_MAX);
  goto while_cond;
while_body:
  wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
while_cond:
  if ((int8_t)context->synchronization_paused == 1 || *(volatile int8_t *)(get_device_info() + 1) == 8) goto while_body;

  if ((int8_t)context->brightness_shadow != (int8_t)context->panel_brightness ||
      (int8_t)context->requested_brightness != (int8_t)context->brightness_shadow) {
    if (is_battery_critical() == 1) {
      set_brightness_to_panel_reg_in_running(context->requested_brightness);
      context->panel_brightness  = context->requested_brightness;
      context->brightness_shadow = context->requested_brightness;
    } else {
      context->brightness_shadow = context->panel_brightness;
      context->requested_brightness = context->panel_brightness;
      set_brightness_to_panel_reg_in_running(context->panel_brightness);
    }
  }

  switch (context->display_event & 0x3f) {

  case 0:
    if ((int8_t)context->slave_ready != 1) goto Ldefault;
    if ((int8_t)context->work_mode != 6 && display_panel_is_secondary(context) == 0) {
      LOG_IF(0, ((unsigned long)&rodata_a0354) /*=0xa0354*/);
      goto top;
    }
    LOG_IF(2, ((unsigned long)&rodata_a036a) /*=0xa036a*/);
    change_work_mode_to(2);
    if ((int8_t)context->work_mode == 6 && (int8_t)context->screen_state != 2) context->screen_state = 2;
    goto Ldefault;

  case 1:
    LOG_IF(2, ((unsigned long)&rodata_a0396) /*=0xa0396*/);
    cv = (int8_t)context->slave_ready;
    *g_display_shutdown_active = 1;
    *g_display_update_active = 1;
    if (cv == 0) {
      set_shutdown_flag(context, 0);
      context->screen_state = 1;
      {
        volatile uint8_t *p13 = (volatile uint8_t *)(uintptr_t)context->system_event_record;
        p13[0] = 0; p13[1] = 0; p13[2] = 0; p13[3] = 0;
      }
      trigger_screen_state_change(((unsigned long)&rodata_a03b3) /*=0xa03b3*/, context, 0);
      process_sync_buffer((uint8_t *)context + 0x38);
    } else {
      wait_for_event(0x00000a3e, 0);
    }
    LOG_IF(2, 0x000a03be);
    goto top;

  case 2:
    LOG_IF(2, ((unsigned long)&rodata_a03d9) /*=0xa03d9*/);
    if ((int8_t)context->remote_command == 0xb) {
      LOG_IF(1, ((unsigned long)&rodata_a03f5) /*=0xa03f5*/, context->remote_value, context->remote_aux);
      if (context->remote_value < 10 && context->remote_aux < 9) {
        *(volatile uint8_t *)(get_device_info() + 0xec1) = context->remote_value;
        *(volatile uint8_t *)(get_device_info() + 0xec0) = context->remote_aux;
        uintptr_t panel = get_device_info();
        uintptr_t canvas = get_device_info();
        cal_panel_canvas_coord((void *)(panel + 0xec4),
                               (void *)(canvas + 0xeb8));
      }
    }
    *g_display_update_active = 1;
    {
      int8_t d5 = (int8_t)context->work_mode;
      if (d5 == 9 || d5 == 0xc || d5 == 0xa || d5 == 0xb || d5 == 6 ||
          d5 == 7 || d5 == 0xe || d5 == 0xf || d5 == 0x10 || d5 == 0x11 || d5 == 0)
        context->screen_state = 2;
      change_work_mode_to(2);
      if (d5 != 9 || d5 != 0xa || d5 != 0xb || d5 != 0x10)
        process_sync_buffer((uint8_t *)context + 0x38);
    }
    LOG_IF(2, ((unsigned long)&rodata_a0434) /*=0xa0434*/);
    *g_display_update_active = 0;
    goto top;

  case 3:
    set_shutdown_flag(context, 1);
    change_work_mode_to(7);
    goto top;

  case 4:
    set_shutdown_flag(context, 1);
    context->lifecycle_mode = 0xc;
    context->dispatch_status = 3;
    process_sync_buffer((uint8_t *)context + 0x80);
    goto top;

  case 5:
    context->lifecycle_mode = 0xa;
    context->dispatch_status = 3;
    process_sync_buffer((uint8_t *)context + 0x80);
    goto top;

  case 6:
    LOG_IF(2, ((unsigned long)&rodata_a044e) /*=0xa044e*/);
    if ((int8_t)context->remote_command == 9) {
      LOG_IF(2, ((unsigned long)&rodata_a0477) /*=0xa0477*/, context->remote_value);
      upgradeDashboardStartupModeInfoToFlash(context->remote_value);
      goto top;
    }
    switch (context->remote_command) {

    case 1:
      if ((int8_t)context->work_mode == 0xc) {
        if ((int8_t)context->remote_value == 0) {
          LOG_IF(2, ((unsigned long)&rodata_a050a) /*=0xa050a*/);
          display_DelayClose(10000);
          goto L2812a;
        }
      } else if ((int8_t)context->remote_value == 1) {
        LOG_IF(2, ((unsigned long)&rodata_a052d) /*=0xa052d*/, context->work_mode);
        prepare_quick_note_mode(context, 0);
        context->pending_task_mode = 0xc;
        *(volatile uint8_t *)(uintptr_t)context->quick_note_record = 1;
        update_persist_task_status(context, 0x0c, 2);
        {
          volatile int8_t *q = (volatile int8_t *)(((uintptr_t)context->quick_note_record) + 2);
          *q = (int8_t)(*q + 1);
        }
        goto Ldefault;
      }
      goto top;

    case 2: {
      b2 = context->remote_value;
      b15 = b2 & 0xf;
      if (b15 == 1) {
        if ((int8_t)context->work_mode != 6) goto L282f6;
        handle_touch_single_click(b2 >> 4);
        display_inputEvent(0, 1);
        process_touch_event();
        LOG_ACTION(((unsigned long)&rodata_a0568) /*=0xa0568*/, b2 >> 4);
        goto top;
      } else if (b15 == 2) {
        handle_touch_single_click(b2 >> 4);
        LOG_ACTION(((unsigned long)&rodata_a05c2) /*=0xa05c2*/, b2 >> 4);
        goto top;
      } else if (b15 == 3) {
        if ((int8_t)context->work_mode != 6) goto L282f6;
        handle_dashboard_action(b2 >> 4);
      L28260:
        display_inputEvent(0, 1);
        process_touch_event();
        LOG_ACTION(((unsigned long)&rodata_a0621) /*=0xa0621*/, b2 >> 4);
        goto top;
      } else if (b15 == 4) {
        handle_dashboard_action(b2 >> 4);
      L28296:
        LOG_ACTION(((unsigned long)&rodata_a067b) /*=0xa067b*/, b2 >> 4);
        goto top;
      } else {
        if (b15 == 5) {
          if ((int8_t)context->work_mode == 6) { handle_stocks_action(b2 >> 4); goto L28260; }
        } else if (b15 == 6) {
          handle_stocks_action(b2 >> 4);
          goto L28296;
        }
      L282f6:
        LOG_IF(1, ((unsigned long)&rodata_a06d7) /*=0xa06d7*/, context->work_mode);
      }
      goto top;
    }

    case 3:
      if ((int8_t)context->work_mode == 9) {
        if ((int8_t)context->remote_value == 1) {
          LOG_IF(2, 0x000a0719);
          goto L28342;
        }
        LOG_IF(0, 0x000a0743);
        goto top;
      }
      LOG_IF(0, 0x000a0771);
      goto top;

    case 4: {
      volatile uint8_t *sb5 = g_onboarding_fragment;
      uint64_t uptime;
      LOG_IF(2, ((unsigned long)&rodata_a09ac) /*=0xa09ac*/, context->remote_value, context->remote_aux,
             context->remote_flag);
      context->onboarding_previous_fragment = *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 3);
      *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 2) = context->remote_value;
      *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 3) = context->remote_aux;
      refresh_onboarding_retry_state();
      cv = (int8_t)context->remote_flag;
      *sb5 = context->remote_aux;
      reset_onboarding_bitmap_state();
      onboarding_retry_watchdog_update();
      uptime = k_uptime_get_1();
      *(volatile int32_t *)(((uintptr_t)context->onboarding_record) + 4) = (int32_t)uptime;
      *(volatile int32_t *)(((uintptr_t)context->onboarding_record) + 8) = (int32_t)(uptime >> 32);
      if (*(volatile int32_t *)(uintptr_t)context->system_event_record == 0xe ||
          (peer_address_is_uninitialized((uint32_t)uptime, (uint32_t)(uptime >> 32)) != 0 &&
           *(volatile int8_t *)(((uintptr_t)context->onboarding_record) + 1) == 0)) {
        int8_t c1 = *(volatile int8_t *)(((uintptr_t)context->onboarding_record) + 2);
        if (c1 == 3) {
          if (*sb5 == 0x12) {
            *(volatile int8_t  *)(((uintptr_t)context->onboarding_record) + 0xc) = cv;
            *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 0xd) = 3;
            *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 0xe) = 3;
          }
        } else if (c1 == 0xb) {
          uintptr_t onboarding = *(volatile uint32_t *)(get_device_info() + 0x1014);
          *(volatile uint8_t *)(onboarding + 0) = 0;
          onboarding = *(volatile uint32_t *)(get_device_info() + 0x1014);
          *(volatile uint8_t *)(onboarding + 1) = 0;
        }
      } else {
        if (cv == 1) {
          *(volatile uint8_t *)(uintptr_t)context->onboarding_record = 1;
          update_persist_task_status(context, 14, 2);
          *(volatile uint8_t *)(((uintptr_t)context->onboarding_record) + 0x20) = context->requested_brightness;
          context->requested_brightness = 0x2a;
        }
      }
      goto L2850c;
    }

    case 5:
      LOG_IF(2, ((unsigned long)&rodata_a0a04) /*=0xa0a04*/, context->remote_value);
      {
        uint8_t v = context->remote_value;
        *(volatile uint8_t *)(((uintptr_t)context->do_not_disturb_record) + 2) = v;
        *g_do_not_disturb_value = v;
      }
      *(volatile uint8_t *)(get_device_info() + 0xcd) = *g_do_not_disturb_value;
      update_not_disturb_settings();
      *(volatile uint8_t *)(uintptr_t)context->do_not_disturb_record = 1;
      update_persist_task_status(context, 7, 2);
      goto L2850c;

    case 6:
      if ((int8_t)context->work_mode == 0xa) {
        if ((int8_t)context->remote_value != 1) { LOG_IF(0, 0x000a0813); goto top; }
        LOG_IF(2, ((unsigned long)&rodata_a07eb) /*=0xa07eb*/);
      L28342:
        display_MasterSendClose();
      L2812a:
        process_touch_event();
        goto top;
      }
      LOG_IF(0, 0x000a0813);
      goto top;

    case 7:
      if ((int8_t)context->work_mode == 6) {
        LOG_IF(2, ((unsigned long)&rodata_a0889) /*=0xa0889*/);
        display_powerEvent(context->remote_value);
        goto L2812a;
      }
      LOG_IF(0, 0x000a08bb);
      goto top;

    case 8:
      LOG_IF(2, ((unsigned long)&rodata_a0932) /*=0xa0932*/);
      cv = (int8_t)context->remote_value;
      if (*(volatile int8_t *)g_remote_language != cv) LOG_IF(1, ((unsigned long)&rodata_a0962) /*=0xa0962*/);
      upgradeAppLanguageInfoToFlash((uint8_t)cv);
      goto top;

    case 10:
      LOG_IF(2, ((unsigned long)&rodata_a04cb) /*=0xa04cb*/);
      set_atomic_flag_bits((volatile uint32_t *)(uintptr_t)((unsigned long)&g_20007b38) /*=0x20007b38*/);
      goto top;

    default:
      goto top;
    }

  case 7:
    switch (context->remote_command) {
    case 0:
      update_temp_task_status(context, 5, 2);
      goto L2850c;
    case 1:
      *g_message_clear_pending = 1;
      clear_timeout_message(0);
      check_pending_messages_flag();
      push_message_3439c();
      update_temp_task_status(context, 4, 2);
    L2850c:
      trigger_screen_state_change(
          context->remote_command == 0 ? ((unsigned long)&rodata_a0a47) /*=0xa0a47*/ :
          context->remote_command == 1 ? ((unsigned long)&rodata_a0a61) /*=0xa0a61*/ :
          context->remote_command == 4 ? ((unsigned long)&rodata_a09ee) /*=0xa09ee*/ : ((unsigned long)&rodata_a0a2e) /*=0xa0a2e*/,
          context, 1);
      goto Ldefault;
    case 2:
      msg_count_dec();
      cv = *(volatile int8_t *)(get_device_info() + 0xdd);
      if (cv != 0) cv = 6;
      set_message_indicator((uint8_t)cv);
      goto Ldefault;
    case 3:
      *g_message_recalc_pending = 1;
      if (*(volatile int8_t *)(get_device_info() + 0x108f) != 0 &&
          msg_content_recalc_unread() != 0 &&
          *(volatile int8_t *)(get_device_info() + 0xd5) != 4) {
        void *status_device = (void *)get_device_info();
        void *screen_device;
        update_temp_task_status(status_device, 4, 2);
        screen_device = (void *)get_device_info();
        trigger_screen_state_change(((unsigned long)&rodata_a0a7b) /*=0xa0a7b*/, screen_device, 1);
        check_pending_messages_flag();
      }
      goto Ldefault;
    default:
      goto Ldefault;
    }

  case 8:
    update_display_status(context, 0);
    if ((int8_t)context->remote_command != 0 && (int8_t)context->work_mode == 4) {
      msg_content_decrement_timer();
      cv = *(volatile int8_t *)(get_device_info() + 0xdd);
      if (cv != 0) cv = 6;
      set_message_indicator((uint8_t)cv);
    }
    if ((int8_t)context->screen_state == 2) get_pending_language_code();
    update_persist_task_status_to_idle(context);
    goto Ldefault;

  default:
    goto top;
  }

Ldefault:
  process_sync_buffer((uint8_t *)context + 0x38);
  goto top;
  (void)p; (void)param_2; (void)param_3;
}
