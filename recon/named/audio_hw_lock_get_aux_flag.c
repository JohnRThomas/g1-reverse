/* named: audio_hw_lock_get_aux_flag */
/* Reconstructed audio_hw_lock_get_aux_flag @ 0x7ef6e  (parity: 300/300 trials, PROVEN) */

unsigned int audio_hw_lock_get_aux_flag(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x14);
  if (v != 0) {
    unsigned int w = *(volatile unsigned int*)(v + 4);
    v = (w >> 6) & 1;
  }
  return v;
}

