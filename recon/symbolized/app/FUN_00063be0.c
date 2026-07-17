#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063be0 @ 0x00063be0
 * public-name: FUN_00063be0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_caf_power_manager_timer                @ 0x200066f0
 *   g_caf_power_manager_wake_evt_cnt         @ 0x2000b310
 *   g_caf_power_manager_system_off_flag      @ 0x2001d563
 */
/* Reconstructed FUN_00063be0 @ 0x63be0  (parity: 300/300 trials, PROVEN) */

extern long long FUN_00063ba8(int a0);
extern void FUN_0007350c(unsigned int a0, int a1, unsigned int a2, unsigned int a3);

void FUN_00063be0(void)
{
  if (*(volatile unsigned char*)((unsigned long)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/ == 0) {
    long long uVar1 = FUN_00063ba8(0);
    if ((int)uVar1 != 0) {
      *(volatile unsigned int*)((unsigned long)&g_caf_power_manager_wake_evt_cnt) /*=0x2000b310*/ = 0;
      FUN_0007350c(((unsigned long)&g_caf_power_manager_timer) /*=0x200066f0*/, (int)((unsigned long long)uVar1 >> 0x20), 0x8000, 0);
    }
  }
}
