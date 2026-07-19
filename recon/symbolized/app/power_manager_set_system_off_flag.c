#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063c14 @ 0x00063c14
 * public-name: power_manager_set_system_off_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   caf_power_manager_restart_timer          <= FUN_00063be0 @ 0x00063be0
 *   power_manager_set_system_off_flag        <= FUN_00063c14 @ 0x00063c14
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 * address symbols (name @ address):
 *   g_caf_power_manager_timer                @ 0x200066f0
 *   g_caf_power_manager_system_off_flag      @ 0x2001d563
 */
/* Reconstructed FUN_00063c14 @ 0x63c14  (parity: 300/300 trials, PROVEN) */

extern void caf_power_manager_restart_timer(void);
extern void k_work_cancel_delayable(unsigned int);
void power_manager_set_system_off_flag(int param_1)
{
  unsigned char b;
  b = *(volatile unsigned char*)((unsigned long)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/;
  if (b == 0) {
    if (param_1 != 0) {
      k_work_cancel_delayable(((unsigned long)&g_caf_power_manager_timer) /*=0x200066f0*/);
    }
  } else if (param_1 == 0) {
    caf_power_manager_restart_timer();
  }
  *(volatile unsigned char*)((unsigned long)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/ = (unsigned char)param_1;
  return;
}
