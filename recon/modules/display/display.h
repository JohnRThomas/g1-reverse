/*
 * display: micro-LED projector panel driver + framebuffer refresh pipeline.
 *
 * Owns the two JBD (jbd/jdb) micro-projector panels (left/right, master/slave),
 * their power rails, brightness registers and the frame-refresh loop. The app
 * renders a 1-bit/4-bit framebuffer ("canvas") in RAM (gui_text draws into it);
 * this module pushes the canvas to the LCD over the panel bus
 * (reflash_fb_data_to_lcd), controls panel power/suspend, applies brightness
 * (manual or ambient-driven), and runs the screen state machine that opens and
 * closes the display for the on-glasses apps (dashboard, navigation,
 * teleprompter, notifications, translate).
 *
 * Threading model: display commands (reflash / close / delay-close / input /
 * power) are marshalled into a 24-byte message and posted to the display
 * command message queue (g_display_msgq @ 0x200038c4). A dispatch thread
 * (entry FUN_00049090) drains the queue and drives display_reflash_handler ->
 * ui_refalsh_warp -> reflash_fb_data_to_lcd. A separate work item on the
 * display worker thread (g_display_thread_id @ 0x2000a09c) performs the actual
 * deferred blit so BLE/ESB callbacks stay short. See wiring.md.
 *
 * Hardware: JBD micro-LED projector panels on the nRF5340 app core.
 *
 * Public API below == exactly the reference-graph "api" set (functions called
 * from OUTSIDE this module). Everything not listed here is module-internal and
 * must be declared `static` in its .c (see "internal" section at the bottom for
 * the recovered helper inventory). NOTE: the topic classifier folded a handful
 * of shared OpenAMP/RPMsg/GATT/msgq primitives into this module's api set
 * because the master<->slave display sync rides on them; those are flagged
 * [shared-infra] and are NOT owned/defined here -- do not re-export them as
 * display API.
 */
#ifndef G1_DISPLAY_H
#define G1_DISPLAY_H

#include <stdint.h>

/* ==== PUBLIC API (reference-graph api set, display-owned) ================== */

/* ---- panel power / init ---------------------------------------------------- */
unsigned int  power_down_panel(void);                    /* 0x15fdc */
unsigned int  jdb_panel_init(unsigned char *cfg);        /* 0x46fc0 */
unsigned int  panel_off(int arg);                        /* 0x46d2c */
int           panel_on(int arg);                         /* 0x46dd8 */
unsigned int  jbd_panel_suspend(unsigned a, unsigned b, unsigned c);          /* 0x475f0 */
unsigned int  jbd_panel_resume(int a, unsigned b, unsigned c, unsigned d);    /* 0x47638 */

/* ---- brightness ------------------------------------------------------------ */
unsigned      set_brightness_lum_base(int a, unsigned b, unsigned **c, unsigned char *d); /* 0x31cbc */

/* ---- framebuffer refresh --------------------------------------------------- */
unsigned      reflash_fb_data_to_lcd(int a, int b, int c, int d, int e, int f);          /* 0x47260 */
unsigned      reflash_fb_data_to_lcd_ex(int a, int b, int c, int d, int e, int f, int g);/* 0x473c8 */
unsigned int  gui_screen_clear(void);                    /* 0x431c0 */
unsigned int  projector_reflash_and_release(unsigned a, unsigned b, unsigned c); /* 0x7d874: build reflash msg, post, unlock */

/* ---- screen / app open-close state machine --------------------------------- */
unsigned int  trigger_screen_state_change(unsigned screen_id, int b, unsigned c, unsigned d); /* 0x2bc2c */
int           draw_template_translate_screen(int arg);   /* 0x3fd44 */
int           display_close_screen(int id, uint32_t b);  /* 0x49858 */
unsigned int  display_DelayClose(unsigned int ms);       /* 0x498c0 */

/* ---- low-level panel-bus register primitive (called from gui layer) -------- */
int           panel_bus_get_handle(void);                /* 0x7d4ec: fetch panel SPI/bus handle via get_device_info */
unsigned int  panel_reg_seq_7d70a(void);                 /* 0x7d70a: panel register access sequence */

/* ==== PUBLIC API [shared-infra] -- classified into display but NOT owned ==== *
 * These belong to the OpenAMP/RPMsg IPC, Zephyr msgq ring, and BLE-GATT layers
 * that the display master<->slave channel uses. Declared here only to record
 * the graph's api set; their real home is the ipc/ble modules. Do not treat as
 * display-owned in the wiring reconstruction.
 *
 *   0x527dc  conn_lookup_by_id            - find active transfer conn by id
 *   0x52880  gatt_notify_chunked          - chunked bt_gatt_notify over a conn
 *   0x609f4  cond_mutex_lock              - mutex lock gated on 0x0bad0000 magic
 *   0x71294  rpmsg_tx_payload             - write payload into virtqueue buffer
 *   0x72908  msgq_ring_put                - irq-locked ring/msgq enqueue
 *   0x73cdc  irq_lock_field_helper        - small irq-locked field update
 *   0x80c20  ccc_notify_enabled_check     - BLE CCC / notify-enabled check
 *   0x85a9c  virtqueue_buffer_release     - OpenAMP virtqueue buffer release
 */

/* ==== INTERNAL (declare `static` in the owning .c; listed for reconstruction) *
 * Named, display-owned, but internal (no external callers):
 *   0x15df4  power_for_panel              0x46e3c  set_brightness_to_panel_reg
 *   0x47058  set_brightness_to_panel_reg_in_running
 *   0x47538  panel_init                   0x42fb0  cal_panel_canvas_coord
 *   0x430c0  ui_raster_height_task (thread body / work entry)
 *   0x3dff8  navigation_direction_img_display
 *   0x497b0  display_close                0x4967c  display_reflash
 *   0x48e28  display_reflash_handler      0x4904c  submit_display_reflash_work
 *   0x49938  display_inputEvent           0x499b8  display_MasterSendClose
 *   0x49a28  display_powerEvent           0x7cce8  update_display_status
 *   0x49090  <display dispatch thread>    0x49638  <display thread creator>
 *   0x4906c  flush_pending_display_reflash
 *
 * Unnamed helpers (purpose deduced from callers/callees/data -- see README):
 *   0x1655c  panel_state_flag_stub        0x179e0  panel_rail_const_helper
 *   0x36024  display_close_getter         0x36d38  dashboard_status_field_refresh
 *   0x47028  brightness_reg_subwrite      0x745c8  queue_put_with_wake
 *   0x7d642/0x7d658/0x7d67e/0x7d6ae/0x7d6f4/0x7d74e/0x7d772/0x7d77c/0x7d82e
 *            JBD panel-register read/write bit-bang cluster
 */

#endif /* G1_DISPLAY_H */
