/* Reconstructed FUN_0007d216 @ 0x7d216  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
uint32_t FUN_0007d216(void)
{
  int iVar1 = get_device_info();
  return **(volatile uint32_t **)(iVar1 + 0xfec);
}

