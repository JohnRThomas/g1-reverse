/*
 * imu_motion: IMU sensor fusion for wear detection, head-tilt wake and the
 *             on-glasses pitch-calibration screen.
 *
 * Reads the inertial sensor (accel/gyro) and fuses it (register_imu_funsion_
 * context) to detect wear / head-up-look gestures that wake the display, and to
 * expose a user-tunable "pitch" (vertical look angle) so the HUD sits at a
 * comfortable elevation. imu_set_enabled / update_imu_trigger_status turn fused
 * motion into wake / anti-shake triggers and post them to a work item embedded
 * in device_info_t (device_info + 0xaf4) via the kernel scheduler primitive
 * FUN_00072880 (rtos module). ui_set_imu_pitch_task is the calibration screen
 * that lets the wearer step the pitch up/down and previews it on the panel. The
 * IMU shares its power rail with the microphone (power_for_imu_and_mic, audio).
 * Wake-angle / anti-shake / wear-detection settings live in device_info_t.
 *
 * PUBLIC API note: the refgraph "api" set for this topic group is dominated by
 * shared GUI-canvas primitives (gui_set_active_canvas, gui_canvas_flags_*,
 * gui_reset_dynamic_bitmap_frame_state, imu_pitch_task_reset_render_state) and
 * the display helper FUN_0007d3dc. These are called from many UI tasks across
 * the firmware and were topic-clustered into imu_motion because the pitch task
 * is their densest single caller; they logically belong to a gui/display layer.
 * They are declared here to match the authoritative cross-module call graph.
 * The genuinely IMU-specific routines (register/update/set_enabled/pitch_task)
 * are entry points invoked through dispatch tables and are marked internal.
 */
#ifndef G1_IMU_MOTION_H
#define G1_IMU_MOTION_H

#include <stdint.h>

/* ---- Public API (functions called from other modules, per refgraph) -------- */

/* IMU-specific */
void          dump_template_gyro_info(int arg);                 /* @0x36164  debug: print gyro template x/y/z */

/* Shared GUI-canvas primitives (clustered here; logically gui/display layer) */
unsigned int  gui_set_active_canvas(unsigned int canvas);       /* @0x431b4  g_gui_active_canvas <- canvas */
unsigned int  gui_canvas_flags_set_bit1(void);                  /* @0x432d0  g_gui_canvas_flags |= 2 */
unsigned int  gui_canvas_flags_clear_bit1(void);                /* @0x432ec  g_gui_canvas_flags &= ~2 */
void          gui_reset_dynamic_bitmap_frame_state(void);       /* @0x43308  clears dyn-bitmap cycle/frame ctrs */
void          imu_pitch_task_reset_render_state(void);          /* @0x436f8  zeroes g_obj_2000a018 render state */
unsigned int  FUN_0007d3dc(void);                               /* @0x7d3dc  display helper thunk -> _tail(8,0,0) */

/* ---- Internal / entry points (dispatch-table targets, not a linkable API) --- */
#if 0
/* register_imu_funsion_context @0x26250 : install fusion callback table into ctx
 *   (ctx+0x8c..+0x98 = fn ptrs 0x25fad/0x25df9/0x25dc5/0x25d8d); called from the
 *   system-init dispatcher FUN_00016eb8. */
unsigned int  register_imu_funsion_context(unsigned char *ctx, unsigned int a, unsigned int b, unsigned int c);

/* update_imu_trigger_status @0x2bcbc : write trigger state to device_info+0xee8;
 *   on a rising trigger while worn (mode 0xa, +0xb0c==0) sets +0xfe9 and submits
 *   the work item at device_info+0xaf4 via FUN_00072880. */
unsigned int  update_imu_trigger_status(unsigned int tag, int device_info, int state);

/* imu_set_enabled @0x2bd4c : on/off wrapper around update_imu_trigger_status +
 *   trigger_screen_state_change ("imu on"/"imu off" strings a24e4/a24dc). */
unsigned int  imu_set_enabled(unsigned int tag, unsigned int device_info, int enable, unsigned int arg);

/* ui_set_imu_pitch_task @0x46b80 : pitch-calibration screen dispatch handler
 *   (action = 1 draw/step, 2 exit); state machine over flags at 0x2001cf8f.
 *   Invoked by the UI task dispatcher FUN_00048b5c. */
unsigned      ui_set_imu_pitch_task(int screen, unsigned arg, int action);
#endif

#endif /* G1_IMU_MOTION_H */
