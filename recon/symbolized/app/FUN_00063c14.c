#include "g1_app_symbols.h"
/* named: FUN_00063c14 */
/* Reconstructed FUN_00063c14 @ 0x63c14  (parity: 300/300 trials, PROVEN) */

extern void FUN_00063be0(void);
extern void FUN_00073518(unsigned int);
void FUN_00063c14(int param_1)
{
  unsigned char b;
  b = *(volatile unsigned char*)((uintptr_t)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/;
  if (b == 0) {
    if (param_1 != 0) {
      FUN_00073518(((uintptr_t)&g_caf_power_manager_timer) /*=0x200066f0*/);
    }
  } else if (param_1 == 0) {
    FUN_00063be0();
  }
  *(volatile unsigned char*)((uintptr_t)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/ = (unsigned char)param_1;
  return;
}

