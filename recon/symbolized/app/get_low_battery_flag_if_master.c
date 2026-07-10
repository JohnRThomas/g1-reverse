#include "g1_app_symbols.h"
/* named: get_low_battery_flag_if_master */
/* globals referenced:
//   0x2000302f  g_low_battery_sync_flag      
*/
/* Reconstructed get_low_battery_flag_if_master @ 0x2efa8  (parity: 300/300 trials, PROVEN) */

extern unsigned char *get_device_info(void);

unsigned char get_low_battery_flag_if_master(void)
{
    unsigned char *pcVar2 = get_device_info();
    unsigned char uVar1;
    if (*pcVar2 == 1) {
        uVar1 = *(volatile unsigned char*)((uintptr_t)&g_low_battery_sync_flag) /*=0x2000302f*/;
    } else {
        uVar1 = 0;
    }
    return uVar1;
}

