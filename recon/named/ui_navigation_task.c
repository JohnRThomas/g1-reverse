/* readable reconstruction; identity: FUN_0003f410 @ 0x0003f410
 * public-name: ui_navigation_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   sync_to_slave                            <= FUN_00026f74 @ 0x00026f74
 *   reset_ipc_evt_ctx                        <= FUN_0003dfe4 @ 0x0003dfe4
 *   navigation_overview_map_display          <= FUN_0003e05c @ 0x0003e05c
 *   navigation_panoramic_map_display         <= FUN_0003e7f8 @ 0x0003e7f8
 *   draw_locale_adjusted_label_pair          <= FUN_0003f2a8 @ 0x0003f2a8
 *   draw_locale_adjusted_label               <= FUN_0003f380 @ 0x0003f380
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   gui_bmp_dynamic_bitmap_draw              <= FUN_0004334c @ 0x0004334c
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   gui_bitmps_merge_draw                    <= FUN_00043bd8 @ 0x00043bd8
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   k_uptime_get_7                           <= FUN_0007d35a @ 0x0007d35a
 *   u64_sub                                  <= FUN_0007d3c2 @ 0x0007d3c2
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a9b76                             @ 0x000a9b76   [INLINED -- G6 literal batch]
 *   rodata_a9c22                             @ 0x000a9c22   [INLINED -- G6 literal batch]
 *   rodata_a9c63                             @ 0x000a9c63   [INLINED -- G6 literal batch]
 *   rodata_a9dba                             @ 0x000a9dba   [INLINED -- G6 literal batch]
 *   rodata_aa0ae                             @ 0x000aa0ae   [INLINED -- G6 literal batch]
 *   rodata_aa0d7                             @ 0x000aa0d7   [INLINED -- G6 literal batch]
 *   rodata_aa112                             @ 0x000aa112   [INLINED -- G6 literal batch]
 *   rodata_aa138                             @ 0x000aa138   [INLINED -- G6 literal batch]
 *   rodata_aa166                             @ 0x000aa166   [INLINED -- G6 literal batch]
 *   rodata_aa1af                             @ 0x000aa1af   [INLINED -- G6 literal batch]
 *   rodata_aa204                             @ 0x000aa204   [INLINED -- G6 literal batch]
 *   rodata_aa23d                             @ 0x000aa23d   [INLINED -- G6 literal batch]
 *   rodata_aa265                             @ 0x000aa265   [INLINED -- G6 literal batch]
 *   rodata_aa297                             @ 0x000aa297   [INLINED -- G6 literal batch]
 *   rodata_aa2e9                             @ 0x000aa2e9   [INLINED -- G6 literal batch]
 *   rodata_aa341                             @ 0x000aa341   [INLINED -- G6 literal batch]
 *   rodata_aa370                             @ 0x000aa370   [INLINED -- G6 literal batch]
 *   rodata_aa3a8                             @ 0x000aa3a8   [INLINED -- G6 literal batch]
 *   rodata_aa3ed                             @ 0x000aa3ed   [INLINED -- G6 literal batch]
 *   rodata_aa412                             @ 0x000aa412   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ipc_or_evt_ctx                         @ 0x20004bb8
 *   g_20004bbc                               @ 0x20004bbc
 *   g_20004bbd                               @ 0x20004bbd
 *   g_20004bbe                               @ 0x20004bbe
 *   g_20004bc6                               @ 0x20004bc6
 *   g_20004bc8                               @ 0x20004bc8
 *   g_20004bcc                               @ 0x20004bcc
 *   g_20004bcd                               @ 0x20004bcd
 *   g_20004bd0                               @ 0x20004bd0
 *   g_20004bd8                               @ 0x20004bd8
 *   g_20004be0                               @ 0x20004be0
 *   g_20004be5                               @ 0x20004be5
 *   g_20004be8                               @ 0x20004be8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007568                               @ 0x20007568
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_20010325                               @ 0x20010325
 *   g_20010326                               @ 0x20010326
 *   g_2001ba2c                               @ 0x2001ba2c
 *   g_2001ba2d                               @ 0x2001ba2d
 *   g_buf_2001ba2e                           @ 0x2001ba2e
 *   g_2001c336                               @ 0x2001c336
 */
/* ui_navigation_task @ 0x0003f410 (CPUAPP), raw FUN_0003f410 */
/*
 *
 * The readable names below retain the raw firmware address at every external
 * call/global so the source remains mechanically back-mappable.
 */
#include <stdint.h>
#include <stddef.h>
#include "../headers/g1_log.h"

/* Human identity: ui_navigation_task; raw definition remains reversible. */

extern uint64_t get_device_info(void);                          /* application_context; r1 retained */
extern void gui_set_active_canvas(uintptr_t);                         /* ui_prepare_task */
extern void gui_canvas_flags_set_bit1(void);                              /* ui_begin_frame */
extern void gui_screen_clear(void);                              /* ui_clear_screen */
extern void gui_reset_dynamic_bitmap_frame_state(void);
extern void gui_bmp_dynamic_bitmap_draw(int, ...);
extern void gui_bmp_bitmap_draw(int, ...);
extern void gui_screen_fade_out_transition(void);                              /* navigation_stop */
extern void gui_bitmps_merge_draw(int, ...);
extern void gui_utf_draw(int, ...);
extern void gui_clock_draw(int, ...);
extern void send_response_data_to_ble(void);
extern void reset_ipc_evt_ctx(void);                              /* navigation_reset */
extern void navigation_overview_map_display(uintptr_t, uintptr_t);              /* overview display */
extern void navigation_panoramic_map_display(uintptr_t, uintptr_t);              /* panoramic display */
extern void draw_locale_adjusted_label_pair(void);
extern void draw_locale_adjusted_label(void);
extern int get_ui_mode_flag_byte1(void);
extern int sync_to_slave(uintptr_t, int, const void *, int);  /* sync_to_slave */
extern int FUN_0007d376(uintptr_t, uint32_t, int, int);      /* semaphore_take */
extern int FUN_0007d37a(uintptr_t);                          /* semaphore_give */
#ifdef G1_APP_SDK_INLINE_COHESION
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline uint64_t g1_sdk_uptime_get_7(void)
{
  return ((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15;
}
#else
extern uint64_t k_uptime_get_7(void); /* k_uptime_get_7 @ 0x0007d35a */
#define g1_sdk_uptime_get_7() k_uptime_get_7()
#endif
extern uint64_t u64_sub(uint64_t, uint64_t);            /* time_delta */
extern int get_timestamp(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern int unix_timestamp_to_datetime(int, void *);
extern void memset_bytes(void *, int, size_t);                /* memset */
/* routed log */
/* direct log */

#define V8(a)  (*(volatile uint8_t  *)(uintptr_t)(a))
#define V16(a) (*(volatile uint16_t *)(uintptr_t)(a))
#define V32(a) (*(volatile uint32_t *)(uintptr_t)(a))
#define V64(a) (*(volatile uint64_t *)(uintptr_t)(a))

/* Navigation private state, raw base DAT_20004bb8. */
#define NAV_STATE             V32(0x20004bb8u)
#define OVERVIEW_DIRTY        V8 (0x20004bbcu)
#define ARRIVAL_PAGE_DRAWN    V8 (0x20004bbdu)
#define NAVIGATION_ACTIVE     V8 (0x20004bbeu)
#define LAST_HEADING          V16(0x20004bc6u)
#define LAST_DISTANCE         V16(0x20004bc8u)
#define ARRIVAL_STATUS        V8 (0x20004bccu)
#define ARRIVAL_PAGE_STARTED  V8 (0x20004bcdu)
#define AUTO_EXIT_DELAY       V64(0x20004bd0u)
#define AUTO_EXIT_STARTED     V64(0x20004bd8u)
#define IMU_ACTION_STATUS     V8 (0x20004be0u)
#define SYNC_RETRIES          V8 (0x20004be5u)
#define LAST_SYNC_TIME        V64(0x20004be8u)

#define LOG_LEVEL             (*(volatile int32_t *)(uintptr_t)0x2000230cu)
#define LOG_ROUTE             V32(0x20007554u)
#define SYNC_ACTIVITY         (*(volatile int32_t *)(uintptr_t)0x20007568u)
#define NAV_PENDING           V8(0x20010325u)
#define NAV_PENDING_VALID     V8(0x20010326u)
#define NAV_REFRESH_PENDING   V8(0x2001ba2cu)
#define NAV_BUFFER_VALID      V8(0x2001ba2du)

#define LOG_CALL(fmt, ...) do {                                             \
    if (LOG_ROUTE == 0u) log_message((uintptr_t)(fmt), ##__VA_ARGS__);      \
    else debug_print((uintptr_t)(fmt), ##__VA_ARGS__);                     \
  } while (0)

int ui_navigation_task(uintptr_t task, uintptr_t unused, uint32_t event)
{
  uintptr_t app = (uintptr_t)get_device_info();
  const uintptr_t nav_root = app;
  uintptr_t nav_view = app + 0xefu;
  uint64_t now;
  uint8_t master_enabled;
  (void)unused;

  gui_set_active_canvas(task + 0x24u);
  gui_canvas_flags_set_bit1();

  switch (NAV_STATE) {
  case 0:
    if (LOG_LEVEL > 2)
      LOG_CALL(0x000aa0aeu, 0x000aa412u); /* status/start */

    if (event == 2u) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000aa0d7u, 0x000aa412u); /* exit command */
      gui_screen_clear();
      goto clear_navigation;
    }

    if (event == 1u) {
      app = (uintptr_t)get_device_info();
      if (V8(app) == 1u)
        send_response_data_to_ble();

      if (NAVIGATION_ACTIVE == 0u) {
        uintptr_t shared = *(volatile uintptr_t *)(app + 0x1000u);
        if (V8(shared) == 1u) {
          if (LOG_LEVEL > 2)
            LOG_CALL(0x000aa112u, 0x000aa412u);
          reset_ipc_evt_ctx();
          NAVIGATION_ACTIVE = 1u;
          LAST_SYNC_TIME = g1_sdk_uptime_get_7();
          SYNC_RETRIES = 10u;
          gui_screen_clear();
          gui_reset_dynamic_bitmap_frame_state();
          draw_locale_adjusted_label();
        }
      }

      if (NAVIGATION_ACTIVE == 1u && NAV_PENDING_VALID == 1u &&
          NAV_PENDING == 1u) {
        NAV_STATE = 1u;
        NAV_REFRESH_PENDING = 0u;
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa138u, 0x000aa412u);
        gui_screen_clear();
        NAV_BUFFER_VALID = 0u;
        SYNC_RETRIES = 10u;
        LAST_SYNC_TIME = g1_sdk_uptime_get_7();
        navigation_overview_map_display(nav_root, nav_view);
      }
      goto active_timeout_check;
    }

    master_enabled = V8(get_device_info());
    if (master_enabled == 1u) {
      if (NAVIGATION_ACTIVE == 1u)
        goto sync_timeout;
    } else if (event != 5u) {
      return 0;
    }

    if (event == 5u) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000a9dbau, 0x000aa412u);
      goto exit_navigation;
    }
    return 0;

  case 1:
    if (event == 2u)
      goto exit_and_clear;

    if (event == 1u) {
      uint64_t app_result = get_device_info();
      uint32_t app_high = (uint32_t)(app_result >> 32);
      app = (uintptr_t)app_result;
      if (V8(app) == 1u) {
        uintptr_t shared;
        send_response_data_to_ble();
        app_result = get_device_info();
        app_high = (uint32_t)(app_result >> 32);
        app = (uintptr_t)app_result;
        shared = *(volatile uintptr_t *)(app + 0x1000u);
        if (V8(shared + 6u) == 1u) {
          if (SYNC_RETRIES < 20u)
            SYNC_RETRIES = 19u;
          app_result = get_device_info();
          app_high = (uint32_t)(app_result >> 32);
          app = (uintptr_t)app_result;
          shared = *(volatile uintptr_t *)(app + 0x1000u);
          V8(shared + 6u) = 0u;
        }
      }

      FUN_0007d376(0x20007b3cu, app_high, -1, -1);
      ARRIVAL_STATUS = V8(app + 0x19du);
      IMU_ACTION_STATUS = V8(app + 0xf6u);
      FUN_0007d37a(0x20007b3cu);
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000aa204u, 0x000aa412u,
                 (unsigned)ARRIVAL_STATUS, (unsigned)V8(app + 0xf6u));

      if (ARRIVAL_STATUS == 2u) {
        int xoff;
        int a, b, c, d;
        uintptr_t shared;
        uint8_t flip;
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa23du, 0x000aa412u);
        NAV_STATE = 3u;
        gui_screen_clear();
        xoff = (get_ui_mode_flag_byte1() == 6) ? 0xaa : 0xc4;
        a = device_info_text_width_get(); b = device_info_text_height_get_clamped();
        c = device_info_text_width_get(); d = device_info_text_height_get_clamped();
        gui_utf_draw(0, nav_root + 0x1a4u, 0, a + xoff, b + 0x3c,
                     c + 0x23f, d + 0x57, 2, 0, 0, 0, 0);
        app = get_device_info();
        shared = *(volatile uintptr_t *)(app + 0xfecu);
        flip = (V8(shared + 0x5eu) != 1u);
        a = get_timestamp(); b = device_info_text_width_get();
        c = device_info_text_height_get_clamped(); d = device_info_text_width_get();
        {
          int e = device_info_text_height_get_clamped();
          gui_clock_draw(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
        }
        AUTO_EXIT_STARTED = g1_sdk_uptime_get_7();
        AUTO_EXIT_DELAY = 5000u;
      } else if (ARRIVAL_STATUS == 1u) {
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa265u, 0x000aa412u);
        if (IMU_ACTION_STATUS != 2u) {
          int xoff, a, b, c, d;
          uintptr_t shared;
          uint8_t flip;
          if (LOG_LEVEL > 2)
            LOG_CALL(0x000aa2e9u, 0x000aa412u);
          if (ARRIVAL_PAGE_STARTED == 0u) {
            gui_screen_clear();
            ARRIVAL_PAGE_STARTED = 1u;
          }
          a = device_info_text_width_get(); b = device_info_text_height_get_clamped();
          c = device_info_text_width_get(); d = device_info_text_height_get_clamped();
          gui_bitmps_merge_draw(a + 0x1b6, b, c + 0x240, d + 0x88,
                       (void *)(uintptr_t)0x2001ba2eu,
                       (void *)(uintptr_t)0x2001c336u, 2, 0xf);
          xoff = (get_ui_mode_flag_byte1() == 6) ? 0xe8 : 0xc4;
          a = device_info_text_width_get(); b = device_info_text_height_get_clamped();
          c = device_info_text_width_get(); d = device_info_text_height_get_clamped();
          gui_utf_draw(0, nav_root + 0x1a4u, 0, a + xoff, b + 0x3c,
                       c + 0x1e4, d + 0x57, 2, 0, 0, 0, 0);
          OVERVIEW_DIRTY = 0u;
          ARRIVAL_PAGE_DRAWN = 1u;

          app = get_device_info();
          shared = *(volatile uintptr_t *)(app + 0xfecu);
          flip = (V8(shared + 0x5eu) != 1u);
          a = get_timestamp(); b = device_info_text_width_get();
          c = device_info_text_height_get_clamped(); d = device_info_text_width_get();
          {
            int e = device_info_text_height_get_clamped();
            gui_clock_draw(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
          }
        } else {
          if (LOG_LEVEL > 2)
            LOG_CALL(0x000aa297u, 0x000aa412u);
          navigation_panoramic_map_display(nav_root, nav_view);
        }
      } else if (IMU_ACTION_STATUS != 2u) {
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa341u, 0x000aa412u);
        navigation_overview_map_display(nav_root, nav_view);
      } else {
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa311u, 0x000aa412u);
        navigation_panoramic_map_display(nav_root, nav_view);
      }
      goto active_timeout_check;
    }

    if (event == 0u) {
      uint32_t orientation[3] = { 0u, 0u, 0u };
      int sensor = get_timestamp();
      unix_timestamp_to_datetime(sensor, orientation);
      if (LAST_DISTANCE != (uint16_t)orientation[2] ||
          LAST_HEADING != (uint16_t)(orientation[1] >> 16)) {
        int a, b, c, d, e;
        uintptr_t shared;
        uint8_t flip;
        LAST_DISTANCE = (uint16_t)orientation[2];
        LAST_HEADING = (uint16_t)(orientation[1] >> 16);
        app = get_device_info();
        shared = *(volatile uintptr_t *)(app + 0xfecu);
        flip = (V8(shared + 0x5eu) != 1u);
        a = get_timestamp(); b = device_info_text_width_get(); c = device_info_text_height_get_clamped();
        d = device_info_text_width_get(); e = device_info_text_height_get_clamped();
        gui_clock_draw(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
      }
      goto active_timeout_check;
    }

    if (V8(get_device_info()) == 1u)
      goto sync_timeout;
    if (event == 5u) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000a9dbau, 0x000aa412u);
      goto exit_navigation;
    }
    return 0;

  case 2:
    if (LOG_LEVEL > 1)
      LOG_CALL(0x000aa370u, 0x000aa412u);
    now = g1_sdk_uptime_get_7();
    if ((int64_t)u64_sub(now, LAST_SYNC_TIME) >= 8001) {
      if (LOG_LEVEL > 1)
        LOG_CALL(0x000aa3a8u, 0x000aa412u);
      gui_screen_fade_out_transition();
      memset_bytes((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
      memset_bytes((void *)(uintptr_t)0x2001ba2eu, 0, 0x1210u);
      NAV_BUFFER_VALID = 0u;
      app = get_device_info();
      V8(*(volatile uintptr_t *)(app + 0x1000u)) = 0u;
    }
    if (event != 2u)
      return 0;
    if (LOG_LEVEL > 2)
      LOG_CALL(0x000a9b76u, 0x000aa412u);
    goto exit_and_clear;

  case 3:
    if (event == 2u)
      goto exit_and_clear;
    if (event == 1u && V8(get_device_info()) == 1u)
      send_response_data_to_ble();
    now = g1_sdk_uptime_get_7();
    if ((int64_t)(AUTO_EXIT_STARTED + AUTO_EXIT_DELAY) < (int64_t)now) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000aa3edu, 0x000aa412u);
      app = get_device_info();
      V8(*(volatile uintptr_t *)(app + 0x1000u)) = 0u;
      gui_screen_fade_out_transition();
      memset_bytes((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
    }
    return 0;

  default:
    return 0;
  }

active_timeout_check:
  if (V8(get_device_info()) != 1u || NAVIGATION_ACTIVE != 1u)
    return 0;

sync_timeout:
  if (SYNC_ACTIVITY > 0) {
    SYNC_ACTIVITY = 0;
    if (SYNC_RETRIES < 20u)
      SYNC_RETRIES = 19u;
  }
  now = g1_sdk_uptime_get_7();
  if ((int64_t)u64_sub(now, LAST_SYNC_TIME) < 1001)
    return 0;
  LAST_SYNC_TIME = g1_sdk_uptime_get_7();
  SYNC_RETRIES = (uint8_t)(SYNC_RETRIES - 1u);
  if (LOG_LEVEL > 2)
    LOG_CALL(0x000a9c22u, 0x000aa412u, (unsigned)SYNC_RETRIES);
  if (SYNC_RETRIES != 0u)
    return 0;
  if (LOG_LEVEL > 1)
    LOG_CALL(0x000a9c63u, 0x000aa412u);
  if (LOG_LEVEL > 2)
    LOG_CALL(0x000aa166u, 0x000aa412u);
  {
    uint16_t command = 0x0106u;
    int result = sync_to_slave(get_device_info(), 6, &command, 2);
    if (result > 4999) {
      if (LOG_LEVEL > 0)
        LOG_CALL(0x000aa1afu, 0x000aa412u);
      return 0;
    }
  }

exit_navigation:
  NAV_STATE = 2u;
  LAST_SYNC_TIME = g1_sdk_uptime_get_7();
  gui_screen_clear();
  {
    int x = device_info_text_width_get();
    int y = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x3f, x, y + 0x3a, 0, 0, 0);
  }
  draw_locale_adjusted_label_pair();
  return 0;

exit_and_clear:
  gui_screen_fade_out_transition();
clear_navigation:
  memset_bytes((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
  memset_bytes((void *)(uintptr_t)0x2001ba2eu, 0, 0x1210u);
  NAV_BUFFER_VALID = 0u;
  return 0;
}
