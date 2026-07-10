#include "g1_app_symbols.h"
/* named: imu_set_enabled */
/* globals referenced:
//   0x000a24dc  aImuOn                       
//   0x000a24e4  aImuOff                      
*/
/* Reconstructed imu_set_enabled @ 0x2bd4c  (parity: 300/300 trials, PROVEN) */

extern int update_imu_trigger_status(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int trigger_screen_state_change(unsigned int a, unsigned int b, unsigned int c);

unsigned int imu_set_enabled(unsigned int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_3 != 0) {
    update_imu_trigger_status(param_1, param_2, 1, param_4);
    uVar1 = "imu-on" /*=0xa24e4*/;
  } else {
    update_imu_trigger_status(param_1, param_2, 0, param_4);
    uVar1 = "imu-off" /*=0xa24dc*/;
  }
  trigger_screen_state_change(uVar1, param_2, param_3 != 0);
  return 0;
}

