#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063be0 @ 0x00063be0
 * public-name: caf_power_manager_restart_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_notify_table_is_idle                <= FUN_00063ba8 @ 0x00063ba8
 *   caf_power_manager_restart_timer          <= FUN_00063be0 @ 0x00063be0
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 * address symbols (name @ address):
 *   g_caf_power_manager_timer                @ 0x200066f0
 *   g_caf_power_manager_wake_evt_cnt         @ 0x2000b310
 *   g_caf_power_manager_system_off_flag      @ 0x2001d563
 */
/* Reconstructed FUN_00063be0 @ 0x63be0  (parity: 300/300 trials, PROVEN) */

extern long long ancs_notify_table_is_idle(int a0);
extern void k_work_reschedule(unsigned int, unsigned int, unsigned int, unsigned int);

void caf_power_manager_restart_timer(void)
{
  if (*(volatile unsigned char*)((unsigned long)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/ == 0) {
    long long uVar1 = ancs_notify_table_is_idle(0);
    if ((int)uVar1 != 0) {
      *(volatile unsigned int*)((unsigned long)&g_caf_power_manager_wake_evt_cnt) /*=0x2000b310*/ = 0;
      k_work_reschedule(((unsigned long)&g_caf_power_manager_timer) /*=0x200066f0*/, (int)((unsigned long long)uVar1 >> 0x20), 0x8000, 0);
    }
  }
}
