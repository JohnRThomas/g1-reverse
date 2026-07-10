#include "g1_app_symbols.h"
/* named: imu_pitch_task_reset_render_state */
/* Reconstructed imu_pitch_task_reset_render_state @ 0x436f8  (parity: 300/300 trials, PROVEN) */

void imu_pitch_task_reset_render_state(void)
{
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state5) /*=0x2000a02c*/ = 0;
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state4) /*=0x2000a028*/ = 0;
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state3) /*=0x2000a024*/ = 0;
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state2) /*=0x2000a020*/ = 0;
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state1) /*=0x2000a01c*/ = 0;
  *(volatile unsigned int *)((uintptr_t)&g_imu_pitch_render_state0) /*=0x2000a018*/ = 0;
}

