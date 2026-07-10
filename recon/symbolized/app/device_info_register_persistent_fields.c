#include "g1_app_symbols.h"
/* named: device_info_register_persistent_fields */
/* Reconstructed device_info_register_persistent_fields @ 0x23230  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned (*fp)(unsigned,unsigned,unsigned,unsigned,unsigned);
unsigned device_info_register_persistent_fields(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  (*(volatile fp*)(param_1+0x1040))("dashboard_ts" /*=0x9e1de*/,*(uint32_t*)(param_1+0xfec),0x6a,*(uint32_t*)(param_1+0x1040),param_4);
  (*(volatile fp*)(param_1+0x1040))("countdown_ts" /*=0x9e201*/,*(uint32_t*)(param_1+0xff0),7,0,0);
  (*(volatile fp*)(param_1+0x1040))("brightness_level" /*=0x9e21f*/,param_1+0xed5,1,0,0);
  (*(volatile fp*)(param_1+0x1040))("3dof_enable" /*=0x9e230*/,param_1+0xf60,1,0,0);
  (*(volatile fp*)(param_1+0x1040))("display_mode" /*=0x9e23c*/,param_1+0xfea,1,0,0);
  (*(volatile fp*)(param_1+0x1040))("wakeup_angle" /*=0x9e259*/,param_1+0xef4,1,0,0);
  (*(volatile fp*)(param_1+0x1040))("first_enter_flag" /*=0x9e20e*/,param_1+0x1050,4,0,0);
  return 0;
}

