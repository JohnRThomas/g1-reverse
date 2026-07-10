/* named: get_system_unix_time */
/* Reconstructed get_system_unix_time @ 0x7d216  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
uint32_t get_system_unix_time(void)
{
  int iVar1 = get_device_info();
  return **(volatile uint32_t **)(iVar1 + 0xfec);
}

