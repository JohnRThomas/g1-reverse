/* Reconstructed atomic_set @ 0x2f910  (parity: 300/300 trials, PROVEN) */

unsigned int atomic_set(unsigned int param_1)
{
  volatile unsigned int *p = (volatile unsigned int *)0x20007bb0UL /* device_info_t+0x11B4  (device-state region) */;
  unsigned int old = *p;
  *p = param_1;
  return old;
}

