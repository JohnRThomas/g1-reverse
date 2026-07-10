/*
 * dashboard: the glasses "home" HUD screen and its startup-mode config.
 *
 * The dashboard is the default heads-up screen (time, date, weather, and one
 * configurable widget slot: default / stocks / news). This module owns the
 * dashboard screen render routine (ui_DashBoard_task, driven by the display
 * thread), the double-click / gesture entry action (handle_dashboard_action),
 * the persisted "startup mode" configuration (which widget + index, stored to
 * flash and synced master->slave), a dwell timer, and the analytics
 * burial-points for dashboard usage. It draws through the gui_* canvas API and
 * is opened via the display screen state machine; startup-mode changes arrive
 * over the app BLE protocol and are mirrored to the slave lens over ESB.
 *
 * PUBLIC API (graph-verified cross-module callers only)
 *   FUN_0001672c  set_dashboard_startup_default_byte   <- touch_key, quicknote
 *   FUN_00037060  sync_dashboard_widget_index          <- ipc_core, ui task
 *   ui_DashBoard_task                                  <- display (screen cb)
 *   FUN_0007dac0  dashboard_burial_point_day_slot      <- analytics, system
 *
 * Everything else below is module-internal or a dispatch/thread ENTRY POINT
 * (reached only from protocol dispatch, flash-restore, or the boot path -- not
 * a normal cross-module call), and is not part of the stable public surface.
 */
#ifndef G1_DASHBOARD_H
#define G1_DASHBOARD_H

#include <stdint.h>

/* ==== PUBLIC API (the graph's api set — only these are cross-module) ======= */

/* Write the persisted startup-mode "default" selector byte into the dashboard
 * config snapshot mirror (0x2007fc69). Called by the touch handler and quicknote. */
void          FUN_0001672c(unsigned char sel);              /* aka set_dashboard_startup_default_byte */

/* Copy the live widget-0 index (0x2001b816) into g_dashboard_widget_state[1],
 * mirror it into the config snapshot, and return the value. Called by ipc_core
 * status-sync and by the dashboard render task. */
unsigned char FUN_00037060(void);                           /* aka sync_dashboard_widget_index */

/* Dashboard screen render/update routine. NOT a K_THREAD_DEFINE thread — it is a
 * screen-state callback invoked by the display thread (ui_raster_height_task).
 * action selects the behaviour: 0/1 reflash, 2 exit, 4 switch widget, 6/7 flags. */
undefined4    ui_DashBoard_task(int screen, undefined4 b, int action);

/* Return today's burial-point day slot (0..6; 7 = unavailable). Shared analytics
 * helper, also used by the wear-time and system burial points. */
unsigned char FUN_0007dac0(void);                           /* aka dashboard_burial_point_day_slot */

/* ==== ENTRY POINTS (protocol dispatch / flash-restore / boot; not plain API) */

/* Boot init: restore persisted dashboard state or apply defaults, load quicknotes. */
void          init_dashboard_info(void);                    /* entry: boot */
/* Gesture / BLE "enter dashboard widget" action sink. */
unsigned int  handle_dashboard_action(unsigned char act, unsigned int b, unsigned int c, unsigned int d);
/* Startup-mode config: persist / load / reset (BLE + flash-restore dispatch). */
unsigned int  upgradeDashboardStartupModeInfoToFlash(unsigned int mode, unsigned int b, unsigned int idx);
unsigned char getDashboardStartUpModeInfofromFlash(unsigned int a, unsigned int b, unsigned int c);
unsigned int  cleanDashBoardStartUpModeInfo(unsigned int a, unsigned int b);
/* Mirror the startup mode to the slave lens over ESB. */
unsigned int  SendDashBoardStartupModeInfoToSlave(int arg);
/* Report dashboard lock state to the phone. */
void          SendDashboardLockInfoToApp(unsigned int a, unsigned int b, unsigned int c);

/* ==== INTERNAL (module-private; declared here for the reconstruction only) == */

/* init helpers */
void          FUN_00016658(void);   /* restore config snapshot (0x2007fc00) -> live device_info */
void          FUN_0004a4b4(unsigned int a, unsigned int b); /* stamp session marker + k_uptime */

/* render-task helpers */
unsigned int  FUN_00048b44(int level);          /* clamp [0x21..0x7d] -> display reg 0x20002544 */
unsigned int  FUN_0007d1d0(volatile unsigned int *flags);   /* read status/flags word */
unsigned int  FUN_0007ca4e(volatile unsigned int *flags);   /* read lock flag word */
int           FUN_0007d248(void);               /* L/R charge-status range check (0 / -1) */

/* dwell timer + analytics */
long long     get_dashboard_sum_time(void);
void          enter_dashboard_burial_point(void);
unsigned int  exit_dashboard_burial_point(void);
void          FUN_0007db50(int ms_lo, int ms_hi, int c, int d); /* add dwell seconds to today's bucket */

#endif /* G1_DASHBOARD_H */
