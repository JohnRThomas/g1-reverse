/* Reconstructed FUN_00016854 @ 0x16854  (CFG-directed candidate) */

#include <stdint.h>
extern int FUN_00019308(int);            /* bt_start */
extern int FUN_0002bd7c(int);            /* global_system_suspend */
extern int FUN_00032ee4(int);            /* is_battery_critical */
extern int FUN_0007c038(int);            /* app_msleep_thunk_a */
extern int FUN_0007c108(int);            /* device_resume_state_advance */
extern int FUN_000167f4(int);            /* enable_ship_mode */
extern int FUN_0002bdf0(int);            /* active_mode_shutdown */
extern int FUN_00016834(int);            /* imu_apply_normalized_mode */
extern int FUN_00017a10(int);            /* gpio_set_pin1_dt_wrapper */
extern int FUN_00017a1c(int);            /* gpio_set_fixed_pin_dt */
extern int FUN_00017a04(int);            /* gpio_set_fixed_output_889f0 */
extern int FUN_000179f8(int);            /* subsystem_enable_gpio_pin_set_adapter */
extern int FUN_0007c058(int);            /* send_touch_click_event */

unsigned int FUN_00016854(unsigned int param_1, int param_2)
{
  volatile int *pp = (volatile int*)0x200069fcUL;
  int base = *pp;
  volatile unsigned short *flags = (volatile unsigned short*)(base + 0x105c);
  if (param_1 == 0) {
    *flags = *flags & ~(unsigned short)param_2;
    if (*(volatile char*)(base+1) == 0) return 0;
    if (param_2 == 0x80) return FUN_0007c108(0);
  } else {
    *flags = *flags | (unsigned short)param_2;
    if (*(volatile char*)(base+1) == 0) return param_1;
    if (param_2 == 0x80) return FUN_00019308(param_1);
  }
  if (param_2 > 0x80) {
    if (param_2 == 0x400) {
      if (param_1 == 0) return FUN_000179f8(0);
      return FUN_00017a04(param_1);
    }
    if (param_2 == 0x800) {
      if (param_1 == 0) return FUN_000167f4(1);
      return param_1;
    }
    if (param_2 == 0x100) {
      int crit = FUN_00032ee4(param_1);
      if (crit != 0) return crit;
      if (param_1 == 0) return FUN_0002bd7c(base);
      return FUN_0002bdf0(base);
    }
    return param_1;
  }
  if (param_2 == 0x20) {
    if (*(volatile char*)base == 1) return FUN_00016834(param_1);
    return FUN_0007c038(0x32);
  }
  if (param_2 == 0x40) {
    if (param_1 == 1) return FUN_0007c058(0xb);
    if (param_1 == 2) return FUN_0007c058(0xa);
    return FUN_0007c058(0xc);
  }
  if (param_2 == 1) {
    if (param_1 == 0) return FUN_00017a1c(0);
    return FUN_00017a10(param_1);
  }
  return param_1;
}
