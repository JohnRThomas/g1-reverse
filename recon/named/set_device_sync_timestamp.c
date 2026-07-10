/* named: set_device_sync_timestamp */
/* Reconstructed set_device_sync_timestamp @ 0x7d230  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);
unsigned int set_device_sync_timestamp(unsigned int param_1) {
  unsigned int r = get_device_info();
  *(unsigned int*)(r + 0xd0) = param_1;
  return param_1;
}

