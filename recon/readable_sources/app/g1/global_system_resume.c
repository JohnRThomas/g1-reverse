#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016854 @ 0x00016854
 * public-name: global_system_resume
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enable_ship_mode                         <= FUN_000167f4 @ 0x000167f4
 *   imu_apply_normalized_mode                <= FUN_00016834 @ 0x00016834
 *   global_system_resume                     <= FUN_00016854 @ 0x00016854
 *   subsystem_enable_gpio_pin_set_adapter    <= FUN_000179f8 @ 0x000179f8
 *   gpio_set_fixed_output_889f0              <= FUN_00017a04 @ 0x00017a04
 *   gpio_set_pin1_dt_wrapper                 <= FUN_00017a10 @ 0x00017a10
 *   gpio_set_fixed_pin_dt                    <= FUN_00017a1c @ 0x00017a1c
 *   bt_start                                 <= FUN_00019308 @ 0x00019308
 *   global_system_suspend                    <= FUN_0002bd7c @ 0x0002bd7c
 *   active_mode_shutdown                     <= FUN_0002bdf0 @ 0x0002bdf0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   send_touch_click_event                   <= FUN_0007c058 @ 0x0007c058
 *   device_resume_state_advance              <= FUN_0007c108 @ 0x0007c108
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed FUN_00016854 @ 0x16854  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_start(int,...);
extern int global_system_suspend(int,...);
extern int is_battery_critical(int,...);
extern int app_msleep_thunk_a(int,...);
extern int device_resume_state_advance(int,...);
extern int enable_ship_mode(int,...);
extern int active_mode_shutdown(int,...);
extern int imu_apply_normalized_mode(int,...);
extern int gpio_set_pin1_dt_wrapper(int,...);
extern int gpio_set_fixed_pin_dt(int,...);
extern int gpio_set_fixed_output_889f0(int,...);
extern int subsystem_enable_gpio_pin_set_adapter(int,...);
extern int send_touch_click_event(int,...);
unsigned int global_system_resume(unsigned int param_1, int param_2)
{
  volatile int *pp = (volatile int*)((unsigned long)&device_info) /*=0x200069fc*/;
  int base = *pp;
  volatile unsigned short *flags = (volatile unsigned short*)(base + 0x105c);
  if (param_1 == 0) {
    *flags = *flags & ~(unsigned short)param_2;
    if (*(volatile char*)(base+1) == 0) return 0;
    if (param_2 == 0x80) return device_resume_state_advance(0);
  } else {
    *flags = *flags | (unsigned short)param_2;
    if (*(volatile char*)(base+1) == 0) return param_1;
    if (param_2 == 0x80) return bt_start(0);
  }
  if (param_2 > 0x80) {
    if (param_2 == 0x400) { if (param_1==0) return subsystem_enable_gpio_pin_set_adapter(0); return gpio_set_fixed_output_889f0(0); }
    if (param_2 == 0x800) { if (param_1==0) return enable_ship_mode(1); return param_1; }
    if (param_2 == 0x100) {
      if (is_battery_critical(0) != 0) return param_1;
      if (param_1 == 0) return global_system_suspend(0);
      return active_mode_shutdown(0);
    }
    return param_1;
  }
  if (param_2 == 0x20) {
    if (*(volatile char*)base == 1) return imu_apply_normalized_mode(0);
    return app_msleep_thunk_a(0x32);
  }
  if (param_2 == 0x40) {
    if (param_1==1) return send_touch_click_event(0xb);
    if (param_1==2) return send_touch_click_event(0xa);
    return send_touch_click_event(0xc);
  }
  if (param_2 == 1) {
    if (param_1==0) return gpio_set_fixed_pin_dt(0);
    return gpio_set_pin1_dt_wrapper(0);
  }
  return param_1;
}
