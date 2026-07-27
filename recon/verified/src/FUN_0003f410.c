/* ui_navigation_task @ 0x0003f410 (CPUAPP), raw FUN_0003f410 */
/*
 *
 * The readable names below retain the raw firmware address at every external
 * call/global so the source remains mechanically back-mappable.
 */
#include <stdint.h>
#include <stddef.h>

/* Human identity: ui_navigation_task; raw definition remains reversible. */

extern uint64_t FUN_000167a8(void);                          /* application_context; r1 retained */
extern void FUN_000431b4(uintptr_t);                         /* ui_prepare_task */
extern void FUN_000432d0(void);                              /* ui_begin_frame */
extern void FUN_000431c0(void);                              /* ui_clear_screen */
extern void FUN_00043308(void);
extern void FUN_0004334c(int, ...);
extern void FUN_00043484(int, ...);
extern void FUN_0004382c(void);                              /* navigation_stop */
extern void FUN_00043bd8(int, ...);
extern void FUN_00043e90(int, ...);
extern void FUN_000442bc(int, ...);
extern void FUN_00047ba8(void);
extern void FUN_0003dfe4(void);                              /* navigation_reset */
extern void FUN_0003e05c(uintptr_t, uintptr_t);              /* overview display */
extern void FUN_0003e7f8(uintptr_t, uintptr_t);              /* panoramic display */
extern void FUN_0003f2a8(void);
extern void FUN_0003f380(void);
extern int FUN_00023ee0(void);
extern int FUN_00026f74(uintptr_t, int, const void *, int);  /* sync_to_slave */
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
extern uint64_t FUN_0007d35a(void); /* k_uptime_get_7 @ 0x0007d35a */
#define g1_sdk_uptime_get_7() FUN_0007d35a()
#endif
extern uint64_t FUN_0007d3c2(uint64_t, uint64_t);            /* time_delta */
extern int FUN_0007d224(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern int FUN_0004a1b8(int, void *);
extern void FUN_00086c78(void *, int, size_t);                /* memset */
extern void FUN_00019c70(unsigned long, ...);                    /* routed log */
extern void FUN_0007dda4(unsigned long, ...);                    /* direct log */

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
    if (LOG_ROUTE == 0u) FUN_0007dda4((uintptr_t)(fmt), ##__VA_ARGS__);      \
    else FUN_00019c70((uintptr_t)(fmt), ##__VA_ARGS__);                     \
  } while (0)

int ui_navigation_task(uintptr_t task, uintptr_t unused, uint32_t event)
{
  uintptr_t app = (uintptr_t)FUN_000167a8();
  const uintptr_t nav_root = app;
  uintptr_t nav_view = app + 0xefu;
  uint64_t now;
  uint8_t master_enabled;
  (void)unused;

  FUN_000431b4(task + 0x24u);
  FUN_000432d0();

  switch (NAV_STATE) {
  case 0:
    if (LOG_LEVEL > 2)
      LOG_CALL(0x000aa0aeu, 0x000aa412u); /* status/start */

    if (event == 2u) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000aa0d7u, 0x000aa412u); /* exit command */
      FUN_000431c0();
      goto clear_navigation;
    }

    if (event == 0u) {
      if (NAVIGATION_ACTIVE == 1u) {
        int w, h;
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa0f5u, 0x000aa412u); /* dynamic image reflash */
        w = FUN_0007d3ee();
        h = FUN_0007d446();
        FUN_0004334c(8, w, h + 0x3a, 0, 0, 0, 0);
        goto active_timeout_check;
      }
    }

    if (event == 1u) {
      app = (uintptr_t)FUN_000167a8();
      if (V8(app) == 1u)
        FUN_00047ba8();

      if (NAVIGATION_ACTIVE == 0u) {
        uintptr_t shared = *(volatile uintptr_t *)(app + 0x1000u);
        if (V8(shared) == 1u) {
          if (LOG_LEVEL > 2)
            LOG_CALL(0x000aa112u, 0x000aa412u);
          FUN_0003dfe4();
          NAVIGATION_ACTIVE = 1u;
          LAST_SYNC_TIME = g1_sdk_uptime_get_7();
          SYNC_RETRIES = 10u;
          FUN_000431c0();
          FUN_00043308();
          FUN_0003f380();
        }
      }

      if (NAVIGATION_ACTIVE == 1u && NAV_PENDING_VALID == 1u &&
          NAV_PENDING == 1u) {
        NAV_STATE = 1u;
        NAV_REFRESH_PENDING = 0u;
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa138u, 0x000aa412u);
        FUN_000431c0();
        NAV_BUFFER_VALID = 0u;
        SYNC_RETRIES = 10u;
        LAST_SYNC_TIME = g1_sdk_uptime_get_7();
        FUN_0003e05c(nav_root, nav_view);
      }
      goto active_timeout_check;
    }

    master_enabled = V8(FUN_000167a8());
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
      uint64_t app_result = FUN_000167a8();
      uint32_t app_high = (uint32_t)(app_result >> 32);
      app = (uintptr_t)app_result;
      if (V8(app) == 1u) {
        uintptr_t shared;
        FUN_00047ba8();
        app_result = FUN_000167a8();
        app_high = (uint32_t)(app_result >> 32);
        app = (uintptr_t)app_result;
        shared = *(volatile uintptr_t *)(app + 0x1000u);
        if (V8(shared + 6u) == 1u) {
          if (SYNC_RETRIES < 20u)
            SYNC_RETRIES = 19u;
          app_result = FUN_000167a8();
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
        FUN_000431c0();
        xoff = (FUN_00023ee0() == 6) ? 0xaa : 0xc4;
        a = FUN_0007d3ee(); b = FUN_0007d446();
        c = FUN_0007d3ee(); d = FUN_0007d446();
        FUN_00043e90(0, nav_root + 0x1a4u, 0, a + xoff, b + 0x3c,
                     c + 0x23f, d + 0x57, 2, 0, 0, 0, 0);
        app = FUN_000167a8();
        shared = *(volatile uintptr_t *)(app + 0xfecu);
        flip = (V8(shared + 0x5eu) != 1u);
        a = FUN_0007d224(); b = FUN_0007d3ee();
        c = FUN_0007d446(); d = FUN_0007d3ee();
        {
          int e = FUN_0007d446();
          FUN_000442bc(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
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
            FUN_000431c0();
            ARRIVAL_PAGE_STARTED = 1u;
          }
          a = FUN_0007d3ee(); b = FUN_0007d446();
          c = FUN_0007d3ee(); d = FUN_0007d446();
          FUN_00043bd8(a + 0x1b6, b, c + 0x240, d + 0x88,
                       (void *)(uintptr_t)0x2001ba2eu,
                       (void *)(uintptr_t)0x2001c336u, 2, 0xf);
          xoff = (FUN_00023ee0() == 6) ? 0xe8 : 0xc4;
          a = FUN_0007d3ee(); b = FUN_0007d446();
          c = FUN_0007d3ee(); d = FUN_0007d446();
          FUN_00043e90(0, nav_root + 0x1a4u, 0, a + xoff, b + 0x3c,
                       c + 0x1e4, d + 0x57, 2, 0, 0, 0, 0);
          OVERVIEW_DIRTY = 0u;
          ARRIVAL_PAGE_DRAWN = 1u;

          app = FUN_000167a8();
          shared = *(volatile uintptr_t *)(app + 0xfecu);
          flip = (V8(shared + 0x5eu) != 1u);
          a = FUN_0007d224(); b = FUN_0007d3ee();
          c = FUN_0007d446(); d = FUN_0007d3ee();
          {
            int e = FUN_0007d446();
            FUN_000442bc(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
          }
        } else {
          if (LOG_LEVEL > 2)
            LOG_CALL(0x000aa297u, 0x000aa412u);
          FUN_0003e7f8(nav_root, nav_view);
        }
      } else if (IMU_ACTION_STATUS != 2u) {
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa341u, 0x000aa412u);
        FUN_0003e05c(nav_root, nav_view);
      } else {
        if (LOG_LEVEL > 2)
          LOG_CALL(0x000aa311u, 0x000aa412u);
        FUN_0003e7f8(nav_root, nav_view);
      }
      goto active_timeout_check;
    }

    if (event == 0u) {
      uint32_t orientation[3] = { 0u, 0u, 0u };
      int sensor = FUN_0007d224();
      FUN_0004a1b8(sensor, orientation);
      if (LAST_DISTANCE != (uint16_t)orientation[2] ||
          LAST_HEADING != (uint16_t)(orientation[1] >> 16)) {
        int a, b, c, d, e;
        uintptr_t shared;
        uint8_t flip;
        LAST_DISTANCE = (uint16_t)orientation[2];
        LAST_HEADING = (uint16_t)(orientation[1] >> 16);
        app = FUN_000167a8();
        shared = *(volatile uintptr_t *)(app + 0xfecu);
        flip = (V8(shared + 0x5eu) != 1u);
        a = FUN_0007d224(); b = FUN_0007d3ee(); c = FUN_0007d446();
        d = FUN_0007d3ee(); e = FUN_0007d446();
        FUN_000442bc(a, b, c + 2, d + 0x4c, e + 0x1d, 3, flip);
      }
      goto active_timeout_check;
    }

    if (V8(FUN_000167a8()) == 1u)
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
    if ((int64_t)FUN_0007d3c2(now, LAST_SYNC_TIME) >= 8001) {
      if (LOG_LEVEL > 1)
        LOG_CALL(0x000aa3a8u, 0x000aa412u);
      FUN_0004382c();
      FUN_00086c78((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
      FUN_00086c78((void *)(uintptr_t)0x2001ba2eu, 0, 0x1210u);
      NAV_BUFFER_VALID = 0u;
      app = FUN_000167a8();
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
    if (event == 1u && V8(FUN_000167a8()) == 1u)
      FUN_00047ba8();
    now = g1_sdk_uptime_get_7();
    if ((int64_t)(AUTO_EXIT_STARTED + AUTO_EXIT_DELAY) < (int64_t)now) {
      if (LOG_LEVEL > 2)
        LOG_CALL(0x000aa3edu, 0x000aa412u);
      app = FUN_000167a8();
      V8(*(volatile uintptr_t *)(app + 0x1000u)) = 0u;
      FUN_0004382c();
      FUN_00086c78((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
    }
    return 0;

  default:
    return 0;
  }

active_timeout_check:
  if (V8(FUN_000167a8()) != 1u || NAVIGATION_ACTIVE != 1u)
    return 0;

sync_timeout:
  if (SYNC_ACTIVITY > 0) {
    SYNC_ACTIVITY = 0;
    if (SYNC_RETRIES < 20u)
      SYNC_RETRIES = 19u;
  }
  now = g1_sdk_uptime_get_7();
  if ((int64_t)FUN_0007d3c2(now, LAST_SYNC_TIME) < 1001)
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
    int result = FUN_00026f74(FUN_000167a8(), 6, &command, 2);
    if (result > 4999) {
      if (LOG_LEVEL > 0)
        LOG_CALL(0x000aa1afu, 0x000aa412u);
      return 0;
    }
  }

exit_navigation:
  NAV_STATE = 2u;
  LAST_SYNC_TIME = g1_sdk_uptime_get_7();
  FUN_000431c0();
  {
    int x = FUN_0007d3ee();
    int y = FUN_0007d446();
    FUN_00043484(0x3f, x, y + 0x3a, 0, 0, 0);
  }
  FUN_0003f2a8();
  return 0;

exit_and_clear:
  FUN_0004382c();
clear_navigation:
  FUN_00086c78((void *)(uintptr_t)0x20004bb8u, 0, 0x38u);
  FUN_00086c78((void *)(uintptr_t)0x2001ba2eu, 0, 0x1210u);
  NAV_BUFFER_VALID = 0u;
  return 0;
}
