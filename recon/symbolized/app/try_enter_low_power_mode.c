#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026c8c @ 0x00026c8c
 * public-name: try_enter_low_power_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   refresh_and_read_box_field_timer         <= FUN_00025448 @ 0x00025448
 *   try_enter_low_power_mode                 <= FUN_00026c8c @ 0x00026c8c
 *   disable_watchdog                         <= FUN_0002aeb4 @ 0x0002aeb4
 * address symbols (name @ address):
 *   g_low_power_mode_enabled                 @ 0x20018d94
 */
/* Reconstructed FUN_00026c8c @ 0x26c8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int refresh_and_read_box_field_timer(int,...); extern int get_device_info(int,...);
extern int disable_watchdog(int,...);

void try_enter_low_power_mode(void)
{
  byte *pbVar1; int iVar7;
  uint uVar6 = refresh_and_read_box_field_timer(0);
  if (((4999 < uVar6) ||
       (iVar7 = get_device_info(0), pbVar1 = (byte*)((unsigned long)&g_low_power_mode_enabled) /*=0x20018d94*/, *(byte *)(iVar7 + 0xfc0) < 0x62)) ||
      (*(volatile byte*)((unsigned long)&g_low_power_mode_enabled) /*=0x20018d94*/ == 0)) {
    return;
  }
  (void)pbVar1;
  disable_watchdog(0);
  for(;;) disable_watchdog(0);
}
