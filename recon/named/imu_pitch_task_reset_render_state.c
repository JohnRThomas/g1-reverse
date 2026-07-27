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
  *(volatile unsigned int *)0x2000a02cUL = 0;
  *(volatile unsigned int *)0x2000a028UL = 0;
  *(volatile unsigned int *)0x2000a024UL = 0;
  *(volatile unsigned int *)0x2000a020UL = 0;
  *(volatile unsigned int *)0x2000a01cUL = 0;
  *(volatile unsigned int *)0x2000a018UL = 0;
}
