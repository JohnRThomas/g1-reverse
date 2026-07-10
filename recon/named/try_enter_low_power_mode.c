/* named: try_enter_low_power_mode */
/* globals referenced:
//   0x20018d94  g_low_power_mode_enabled     
*/
/* Reconstructed try_enter_low_power_mode @ 0x26c8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int FUN_00025448(int,...); extern int get_device_info(int,...);
extern int disable_watchdog(int,...);

void try_enter_low_power_mode(void)
{
  byte *pbVar1; int iVar7;
  uint uVar6 = FUN_00025448(0);
  if (((4999 < uVar6) ||
       (iVar7 = get_device_info(0), pbVar1 = (byte*)0x20018d94, *(byte *)(iVar7 + 0xfc0) < 0x62)) ||
      (*(volatile byte*)0x20018d94 == 0)) {
    return;
  }
  (void)pbVar1;
  disable_watchdog(0);
  for(;;) disable_watchdog(0);
}

