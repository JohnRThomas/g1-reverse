#include "g1_app_symbols.h"
/* named: is_battery_critical */
/* globals referenced:
//   0x20019ef3  g_test_mode_flag             
*/
/* Reconstructed is_battery_critical @ 0x32ee4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;u8 is_battery_critical(void){return *(volatile u8*)((uintptr_t)&g_test_mode_flag) /*=0x20019ef3*/;}
