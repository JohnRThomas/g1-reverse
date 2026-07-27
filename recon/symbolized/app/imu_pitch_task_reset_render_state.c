#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000436f8 @ 0x000436f8
 * public-name: imu_pitch_task_reset_render_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   imu_pitch_task_reset_render_state        <= FUN_000436f8 @ 0x000436f8
 * address symbols (name @ address):
 *   g_imu_pitch_render_state0                @ 0x2000a018
 *   g_imu_pitch_render_state1                @ 0x2000a01c
 *   g_imu_pitch_render_state2                @ 0x2000a020
 *   g_imu_pitch_render_state3                @ 0x2000a024
 *   g_imu_pitch_render_state4                @ 0x2000a028
 *   g_imu_pitch_render_state5                @ 0x2000a02c
 */
/* Reconstructed FUN_000436f8 @ 0x436f8  (parity: 300/300 trials, PROVEN) */

unsigned int imu_pitch_task_reset_render_state(void) {
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state5) /*=0x2000a02c*/ = 0;
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state4) /*=0x2000a028*/ = 0;
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state3) /*=0x2000a024*/ = 0;
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state2) /*=0x2000a020*/ = 0;
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state1) /*=0x2000a01c*/ = 0;
  *(volatile unsigned int *)((unsigned long)&g_imu_pitch_render_state0) /*=0x2000a018*/ = 0;
}
