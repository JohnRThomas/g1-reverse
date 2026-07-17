#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a0d8 @ 0x0002a0d8
 * public-name: touch_key_thread
 * durable-map: recon/catalogs/function_names_app.json
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
/* Reconstructed touch_key_thread @ 0x0002a0d8.
 * Back-map: FUN_0002a0d8.  Executable extent [0x0002a0d8,0x0002a4a0)
 * includes the internal switch/literal islands; 0x0002a4a0 begins the
 * trailing literal pool.
 */
#include <stdint.h>

extern void log_message(uint32_t format, ...);                 /* FUN_0007dda4 */
extern uintptr_t get_device_info(void);                        /* FUN_000167a8 */
extern void debug_print(uint32_t format, uint32_t module,
                        uint32_t value, ...);                  /* FUN_00019c70 */
extern void trigger_touch_key_hw_reset(void);                  /* FUN_0002a0c0 */
extern void handle_touch_key_irq(void);                        /* FUN_00030af0 */
extern void k_msleep(int32_t milliseconds);                    /* FUN_0007cb8e */
extern void read_rtc_counter_ms(void *destination);            /* FUN_0007d0aa */
extern int32_t get_uptime_ms(void);                            /* FUN_00086690 */
extern int k_sem_take(void *semaphore, int64_t timeout);       /* FUN_0007cb48 */
extern void reset_all_usr_data(void *context, int32_t erase);  /* FUN_0002316c */
extern void send_touch_click_event(int32_t event);             /* FUN_0007c058 */
extern void touch_pmic_reset_assert(void);                     /* FUN_00017a28 */
extern void touch_pmic_reset_deassert(void);                   /* FUN_00017a34 */
extern uint32_t sys_reboot(int32_t type);                      /* FUN_0004c0a8 */

#define TOUCH_IRQ_PENDING \
    (*(volatile int32_t *)((unsigned long)&g_touch_key_irq_pending) /*=0x20006a00*/) /* g_touch_key_irq_pending */
#define TOUCH_IRQ_LINE_STATUS \
    (*(volatile uint8_t *)((unsigned long)&g_touch_key_irq_line_status) /*=0x20019dac*/) /* g_touch_key_irq_line_status */
#define TOUCH_PRESS_ACTIVE \
    (*(volatile uint8_t *)((unsigned long)&g_touch_key_press_active) /*=0x20018d89*/) /* g_touch_key_press_active */
#define TOUCH_RESET_REASON \
    (*(volatile int32_t *)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/) /* g_touch_key_reset_reason */
#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_ALTERNATE_SINK (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

void touch_key_thread(char *context)
{
  volatile int32_t *log_level_ptr;
  volatile int32_t *alternate_sink_ptr;
  int32_t event_time;
  int32_t now;
  int32_t since_release;
  uint32_t format_string;
  uint32_t reset_reason;
  int32_t click_count;
  int32_t event_count;
  int32_t release_time;
  int32_t long_press_armed;
  int32_t press_time;
  int32_t short_stuck_timeout;
  int32_t held_time;
  uint8_t irq_line_status;

  /* Persistent loop state: long-press arm, release time, click count,
   * previous press time, and the shortened stuck-key timeout selector. */
  long_press_armed = 0;
  release_time = 0;
  click_count = 0;
  press_time = 0;
  short_stuck_timeout = 0;
event_loop:
  do {
    while ((k_sem_take(context + 0xb0, 0x2000), *(char *)(context + 1) == '\x01' ||
            ((event_time = (int32_t)get_device_info(), *(char *)(event_time + 1) == '\b')))) {
      k_msleep(5000);
    }
    if (TOUCH_IRQ_PENDING != 0) {
      handle_touch_key_irq();
      TOUCH_IRQ_PENDING = 0;
    }
  } while (-1 < (int32_t)((uint32_t)*(uint16_t *)(context + 0x105c) << 0x1f));
  irq_line_status = TOUCH_IRQ_LINE_STATUS;
  if (irq_line_status == 1) {
    event_time = get_uptime_ms();
    read_rtc_counter_ms(context + 0x1078);
    if (10000 < event_time - press_time) {
      release_time = 0;
      click_count = release_time;
    }
    event_count = click_count + 1;
    TOUCH_IRQ_LINE_STATUS = 0;
  }
  else {
    event_count = click_count;
    event_time = press_time;
    if (irq_line_status == 2) {
      release_time = get_uptime_ms();
      TOUCH_IRQ_LINE_STATUS = 0;
      TOUCH_PRESS_ACTIVE = 0;
    }
  }
  now = get_uptime_ms();
  since_release = get_uptime_ms();
  alternate_sink_ptr = &LOG_ALTERNATE_SINK;
  log_level_ptr = &LOG_LEVEL;
  since_release = since_release - release_time;
  held_time = release_time - event_time;
  click_count = event_count;
  press_time = event_time;
  if (event_count != 1) goto check_multi_click;
  now = now - event_time;
  if (long_press_armed != 0) {
    if (release_time == 0) {
check_stuck_key:
      if (short_stuck_timeout == 0) {
        click_count = 0x23;
      }
      else {
        click_count = 3;
      }
      if (click_count * 30000 < now) {
        if (0 < *log_level_ptr) {
          if (*alternate_sink_ptr == 0) {
            log_message(((unsigned long)&rodata_a1626) /*=0xa1626*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, short_stuck_timeout);
          }
          else {
            debug_print(0,0,0);
          }
        }
        long_press_armed = 0;
        TOUCH_RESET_REASON = 6;
        trigger_touch_key_hw_reset();
        click_count = 0;
        short_stuck_timeout = long_press_armed;
        goto event_loop;
      }
      if (event_time < 0) goto check_completed_press;
    }
    else {
      click_count = long_press_armed;
      if (release_time <= event_time) goto event_loop;
check_completed_press:
      if (10000 < since_release) {
        if (15000 < held_time) {
          long_press_armed = 1;
          goto check_long_hold;
        }
        goto emit_single_click;
      }
    }
    long_press_armed = 1;
    click_count = event_count;
    goto event_loop;
  }
  if (release_time == 0) {
    read_rtc_counter_ms(context + 0x1078);
    if (((int32_t)0xffffb1e1 <= *(int32_t *)(context + 0x1078)) &&
        (*(int32_t *)(context + 0x1078) < 20000)) {
      click_count = 0;
      goto event_loop;
    }
    if (15000 < now) {
      if (0 < *log_level_ptr) {
        if (*alternate_sink_ptr == 0) {
          log_message(((unsigned long)&rodata_a15d6) /*=0xa15d6*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, now);
        }
        else {
          debug_print(0,0,0);
        }
      }
      TOUCH_RESET_REASON = 4;
      trigger_touch_key_hw_reset();
      goto check_stuck_key;
    }
    if (-1 < event_time) {
      long_press_armed = 0;
      goto event_loop;
    }
  }
  else if (release_time <= event_time) goto event_loop;
  if (10000 < since_release) {
    if (15000 < held_time) goto check_long_hold;
emit_single_click:
    if (0 < *log_level_ptr) {
      if (*alternate_sink_ptr == 0) {
        log_message(((unsigned long)&rodata_a172a) /*=0xa172a*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, *(uint32_t *)(context + 0x1078));
      }
      else {
        debug_print(0,0,0);
      }
    }
    reset_reason = 1;
    goto publish_reset_reason;
  }
  goto event_loop;
check_multi_click:
  if (((event_count == 0) || (release_time <= event_time)) || (since_release < 0x2711)) goto event_loop;
  if (15000 < held_time) {
check_long_hold:
    if (held_time <= (int32_t)0x11940) {
      if (0 < *log_level_ptr) {
        if (*alternate_sink_ptr == 0) {
          log_message(((unsigned long)&rodata_a1626) /*=0xa1626*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
        }
        else {
          debug_print(0,0,0);
        }
      }
      release_time = 0;
      click_count = event_count;
      short_stuck_timeout = 1;
      goto event_loop;
    }
    if (0 < *log_level_ptr) {
      if (*alternate_sink_ptr == 0) {
        log_message(((unsigned long)&rodata_a1681) /*=0xa1681*/, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    reset_reason = 5;
    goto publish_reset_reason;
  }
  switch (event_count) {
  case 2:
    if (0 < *log_level_ptr) {
      if (*alternate_sink_ptr == 0) {
        log_message(0xa177f, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    reset_reason = 2;
    goto publish_reset_reason;
  case 3:
    if (0 < *log_level_ptr) {
      if (*alternate_sink_ptr == 0) {
        log_message(0xa17d1, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    reset_reason = 3;
publish_reset_reason:
    TOUCH_RESET_REASON = reset_reason;
    trigger_touch_key_hw_reset();
    break;
  case 5:
    goto five_click_reboot;
  case 10:
    reset_all_usr_data(context, 1);
    break;
  case 0xf:
    send_touch_click_event(10);
    if (0 < LOG_LEVEL) {
      if (LOG_ALTERNATE_SINK == 0) {
        log_message(0xa1823, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 0xf);
      }
      else {
        debug_print(0,0,0);
      }
    }
  }
  long_press_armed = 0;
  click_count = long_press_armed;
  goto event_loop;
five_click_reboot:
  if (0 < LOG_LEVEL) {
    format_string = 0xa184b;
    if (LOG_ALTERNATE_SINK == 0) goto log_directly;
    debug_print(0xa184b, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 5);
  }
  do {
    touch_pmic_reset_assert();
    if (0 < LOG_LEVEL) {
      if (LOG_ALTERNATE_SINK == 0) {
        log_message(0xa1868, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
    }
    touch_pmic_reset_deassert();
    if (0 < LOG_LEVEL) {
      if (LOG_ALTERNATE_SINK == 0) {
        log_message(0xa187e, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/);
      }
      else {
        debug_print(0,0,0);
      }
      if (0 < LOG_LEVEL) {
        if (LOG_ALTERNATE_SINK == 0) {
          log_message(0xa0c6c, ((unsigned long)&rodata_a1a76) /*=0xa1a76*/, 5);
        }
        else {
          debug_print(0,0,0);
        }
      }
    }
    k_msleep(500);
    format_string = sys_reboot(1);
log_directly:
    log_message(format_string);
  } while (1);
}
