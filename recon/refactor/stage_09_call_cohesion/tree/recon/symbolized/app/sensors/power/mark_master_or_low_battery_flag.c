#include "g1_app_symbols.h"
#include "g1_power.h"
/* readable reconstruction; identity: FUN_0002efc0 @ 0x0002efc0
 * public-name: mark_master_or_low_battery_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 * address symbols (name @ address):
 *   g_low_battery_sync_flag                  @ 0x2000302f
 */
/* Reconstructed FUN_0002efc0 @ 0x2efc0  (parity: 300/300 trials, PROVEN) */

unsigned int mark_master_or_low_battery_flag(void)
{
  int iVar1;
  char *pcVar2;
  iVar1 = is_battery_critical();
  if ((iVar1 == 1) || (pcVar2 = get_device_info(), *pcVar2 == (char)1)) {
    *(volatile unsigned char *)((unsigned long)&g_low_battery_sync_flag) /*=0x2000302f*/ = 1;
  }
  return 0;
}
