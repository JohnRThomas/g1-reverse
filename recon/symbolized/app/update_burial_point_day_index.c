#include "g1_app_symbols.h"
/* named: update_burial_point_day_index */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_burial_point_day_index @ 0x4a5b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...); extern int debug_print(int,...);
extern int unix_timestamp_to_datetime(int,...); extern int get_system_unix_time(int,...);

undefined4 update_burial_point_day_index(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)
{
  undefined4 uVar2; uint local_24, local_20, local_1c;
  local_24 = param_2; local_20 = param_3; local_1c = param_4;
  uVar2 = get_system_unix_time(0);
  local_24 = 0; local_20 = 0; local_1c = 0;
  unix_timestamp_to_datetime(uVar2,(int)&local_24);
  if ((local_24 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/) < 0x7e9) {
    if ((((local_24 >> 16) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/) | (local_20 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/)) < 2) {
      if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): burial point date was not init!\n" /*=0xf0310*/,"update_burial_point_day_index" /*=0xf04c1*/,local_20 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/,0,param_1);
        else debug_print(0);
      }
      return 0xffffffff;
    }
  }
  (void)local_1c;
  return 0;
}

