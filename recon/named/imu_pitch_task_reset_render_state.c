/* named: imu_pitch_task_reset_render_state */
/* Reconstructed imu_pitch_task_reset_render_state @ 0x436f8  (parity: 300/300 trials, PROVEN) */

void imu_pitch_task_reset_render_state(void)
{
  *(volatile unsigned int *)0x2000a02cUL = 0;
  *(volatile unsigned int *)0x2000a028UL = 0;
  *(volatile unsigned int *)0x2000a024UL = 0;
  *(volatile unsigned int *)0x2000a020UL = 0;
  *(volatile unsigned int *)0x2000a01cUL = 0;
  *(volatile unsigned int *)0x2000a018UL = 0;
}

